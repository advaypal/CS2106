#include "libefs.h"

int main(int ac, char **av)
{
	if(ac != 3)
	{
		printf("\nUsage: %s <file to check in> <password>\n\n", av[0]);
		return -1;
	}

	FILE *fp = fopen(av[1], "r");

	if(fp == NULL)
	{
		printf("\nUnable to open source file %s\n\n", av[1]);
		exit(-1);
	}

	//create buffer
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	rewind(fp);
	char *buffer = makeNewDataBuffer();
	unsigned long len = fread(buffer, sizeof(char), size , fp);

	initFS("part.dsk", av[2]);	
	//check if file exists
	int isFile = fileExists(av[1]);
	if(isFile == 0){
		printf("DUPLICATE FILE ERROR");
		return -1;
	}
	int fileOpen = openFile(av[1], MODE_CREATE);
	writeFile(fileOpen, buffer, sizeof(char), (int)(len / sizeof(char)));
	delete buffer;
	closeFile(fileOpen);	
	closeFS();
	return 0;
}
