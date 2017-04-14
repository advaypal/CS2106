#include "libefs.h"

// FS Descriptor
TFileSystemStruct *_fs;

// Open File Table
TOpenFile *_oft;
	
// Open file table counter
int _oftCount=0;

// Mounts a paritition given in fsPartitionName. Must be called before all
// other functions
void initFS(const char *fsPartitionName, const char *fsPassword)
{
	mountFS(fsPartitionName, fsPassword);
	_fs = getFSInfo();
	_oft = (TOpenFile *) calloc(sizeof(TOpenFile), _fs->maxFiles);
}

// Opens a file in the partition. Depending on mode, a new file may be created
// if it doesn't exist, or we may get FS_FILE_NOT_FOUND in _result. See the enum above for valid modes.
// Return -1 if file open fails for some reason. E.g. file not found when mode is MODE_NORMAL, or
// disk is full when mode is MODE_CREATE, etc.

int openFile(const char *filename, unsigned char mode)
{
 	unsigned int inode = findFile(filename), readPtr, writePtr, filePtr, index;
	unsigned long block;
	unsigned long *inodeBuffer = makeInodeBuffer();
	char *dataBuffer = makeDataBuffer();
	if (inode  == FS_FILE_NOT_FOUND) {
		//Create file	
		if (mode != MODE_CREATE) {
			delete inodeBuffer;
			delete dataBuffer;
			return -1;
		}
		inode = makeDirectoryEntry(filename, 0, 0);
		if (inode == FS_DIR_FULL) {
			return -1;
		}
		block = findFreeBlock();
		if (block == FS_FULL) {
			return -1;
		}
		markBlockBusy(block);
		setBlockNumInInode(inodeBuffer, 0, block);
		saveInode(inodeBuffer, inode);
		updateFreeList();
		readPtr = writePtr = filePtr = 0;
	//FS constraints		
	} else {
		loadInode(inodeBuffer, inode);
		if (mode != MODE_READ_APPEND) {
			block = returnBlockNumFromInode(inodeBuffer, 0);
			readPtr = writePtr = filePtr = 0;		
			readBlock(dataBuffer, block);
		} else { 	
			block = returnBlockNumFromInode(inodeBuffer, filePtr - 1);
			readPtr =  0;
			filePtr = getFileLength(filename);
			writePtr = filePtr % (_fs->blockSize);
			readBlock(dataBuffer, block);
		}
	}
		
	//Create OFT entry
	TOpenFile *newOFT = new TOpenFile();
	newOFT->openMode = mode;
	newOFT->blockSize = _fs->blockSize;
	newOFT->inode = inode;
	newOFT->inodeBuffer = inodeBuffer;
	newOFT->buffer = dataBuffer;
	newOFT->readPtr = readPtr;
	newOFT->writePtr = writePtr;
	newOFT->filePtr = filePtr;
	newOFT->fileName = filename;
	newOFT->DELETED = false;
	/*
	newOFT.next = *(_oft);
	*(_oft).prev = newOFT;
	newOFT.prev = null;
	newOFT.id = _oftCount;
	_oft = &newOFT;
	*/
	updateDirectory();
	_oft[_oftCount++] = *newOFT;
	return _oftCount - 1;

	//Limit on number of files?
	/**
	for (index = 0; index < _oftCount; index++) {
		if (_oft[index] = ) {
			break;
		}
	}
	_oft[index] = newOFT;
	_oftCount++;
	return index;
	**/
}



// Write data to the file. File must be opened in MODE_NORMAL or MODE_CREATE modes. Does nothing
// if file is opened in MODE_READ_ONLY mode.
void writeFile(int fp, void *buffer, unsigned int dataSize, unsigned int dataCount)
{
	/*
	TOpenFile currentFile= *(_oft);
	while (currentFile.id != fp) {
		currentFile = currentFile.next;
		if (currentFile == null) {
			return;
		}
	}
	**/
	TOpenFile *currentFile = &_oft[fp];
	if (currentFile == NULL) {
		return;
	}
	if (currentFile->openMode == MODE_READ_ONLY) {
		return;		
	}

	unsigned int dataToWriteSize = dataSize * dataCount;
	int count = 0;
	unsigned int writePtr = currentFile->writePtr;
	char* fileBuffer = currentFile->buffer;
	char *mybuffer = (char *) buffer;
	unsigned int filePtr = currentFile->filePtr;
	unsigned long block = returnBlockNumFromInode(currentFile->inodeBuffer, filePtr);
	while (count < dataToWriteSize) {
		if (writePtr == (_fs->blockSize - 1)) {
			//Write it to disk
			writeBlock(fileBuffer, block); 
			block = findFreeBlock();
			if (block == FS_FULL) {
				return;
			}
			markBlockBusy(block);
			updateFreeList();
			setBlockNumInInode(currentFile->inodeBuffer, filePtr, block);
			saveInode(currentFile->inodeBuffer, currentFile->inode);
			//Empty the buffer
			strcpy(fileBuffer, "");
			//count += _fs->blockSize;
			writePtr = 0;
		}
		fileBuffer[writePtr] = mybuffer[count];
		writePtr ++;
		count++;
		filePtr ++;
	}
	currentFile->filePtr = filePtr;
	currentFile->writePtr = writePtr;


	flushFile(fp);	
}

// Flush the file data to the disk. Writes all data buffers, updates directory,
// free list and inode for this file.
void flushFile(int fp)
{
	TOpenFile *currentFile = &_oft[fp];
	unsigned int filePtr = currentFile->filePtr;
	unsigned long block = returnBlockNumFromInode(currentFile->inodeBuffer, filePtr);
	char* fileBuffer = currentFile->buffer;
	writeBlock(fileBuffer, block);
	updateDirectoryFileLength(currentFile->fileName, filePtr);
	updateDirectory();
 
}


char *makeNewDataBuffer() {
	return makeDataBuffer();
}
// Read data from the file.
void readFile(int fp, void *buffer, unsigned int dataSize, unsigned int dataCount)
{
	/**
	TOpenFile currentFile= *(_oft);
	while (currentFile.id != fp) {
		currentFile = currentFile.next;
		if (currentFile == null) {
			return;
		}
	}
	**/
	TOpenFile *currentFile = &_oft[fp];
	if (currentFile == NULL) {
		return;
	}
	//Allow read in append?
	if (currentFile->openMode == MODE_READ_APPEND) {
		return;		
	}

	char *mybuffer = (char *)buffer;
	unsigned int dataToReadSize = dataSize * dataCount;
	int count = 0;
	unsigned int readPtr = currentFile->readPtr, filePtr = currentFile->filePtr;
	char* fileBuffer = currentFile->buffer;
	unsigned long block = returnBlockNumFromInode(currentFile->inodeBuffer, filePtr);
	while (count < dataToReadSize) {
		if (readPtr == (_fs->blockSize - 1)) {
			//Empty the buffer
			strcpy(fileBuffer, "");
			//count += _fs->blockSize;
			readPtr = 0;
			block = returnBlockNumFromInode(currentFile->inodeBuffer, filePtr);
			readBlock(fileBuffer, block);
		}
		mybuffer[count] = fileBuffer[readPtr];
		count++;
		readPtr++;
		filePtr ++;
	}
}

int getAttribute(char* fileName) {
	int code = getattr(fileName);
	if (code != FS_FILE_NOT_FOUND) {
		return code;
	} else {
		return 0;
	}
 }

int setAttribute(char* fileName, int mode) {
	unsigned int isFilePresent = findFile(fileName);
	if (isFilePresent != FS_FILE_NOT_FOUND) {
		setattr(fileName, mode);
		return 1;
	} else {
		return 0;
	}
}

// Delete the file. Read-only flag (bit 2 of the attr field) in directory listing must not be set. 
// See TDirectory structure.
void delFile(const char *filename) 
{
	//Check if file exists, return -1 if not
	int attr = getattr(filename);
	if ((attr & 0b100) == 4) {
		printf("CANNOT DELETE READ-ONLY FILE");
		return;
	}
	unsigned int inode = delDirectoryEntry(filename);
	if (inode == FS_FILE_NOT_FOUND) {
		printf("FILE DOES NOT EXIST");
		return;
	}	

	TOpenFile *current = NULL;
	for (int i = 0; i < _oftCount; i++) {
		current = &_oft[i];
		if ((current->DELETED)) {
			continue;
		}
		if (strcmp(filename, current->fileName) == 0) {
			current = &_oft[i];
			break;
		}
	}
	if (current == NULL || (current -> DELETED)) {
		return;
	}
	//free blockSize
	unsigned int i;
	for (i = 0; i < current->filePtr; i += _fs->blockSize) {

		markBlockFree(returnBlockNumFromInode(current->inodeBuffer,i));	
	}

}

unsigned long getFileSize(char *fileName) {
	return getFileLength(fileName);
}

// Close a file. Flushes all data buffers, updates inode, directory, etc.
void closeFile(int fp)
{
	flushFile(fp);
	TOpenFile *currentFile = &_oft[fp];
	//free all resources
	delete [] currentFile->buffer;
	delete [] currentFile->inodeBuffer;
	currentFile->DELETED = true;
}
// Unmount file system.
void closeFS()
{
	delete _oft;
	unmountFS();
}

int fileExists(char *filename) {
	unsigned int ndx = findFile(filename);
	if (ndx != FS_FILE_NOT_FOUND) {
		return 0;
	} else {
		return 1;
	}
}

