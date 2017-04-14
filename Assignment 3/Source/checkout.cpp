#include "libefs.h"

int main(int ac, char **av)
{
	if(ac != 3)
	{
		printf("\nUsage: %s <file to check out> <password>\n\n", av[0]);
		exit(-1);
	}
	initFS("part.dsk", av[2]);
	//create a buffer
	char *buffer = makeNewDataBuffer();
	int fileOpen = openFile(av[1], MODE_READ_ONLY);
	if (fileOpen == -1) {
		printf("FILE NOT FOUND");
		closeFS();
		exit(-1);
	}
	//define len
	//are they both the same?
	unsigned long size = getFileSize(av[1]);
	readFile(fileOpen, buffer, sizeof(char), size);

	FILE *fp = fopen(av[1], "w");

	// Write the data
	fwrite(buffer, sizeof(char), size, fp);

	// Close the file
	fclose(fp);
	closeFS();
	return 0;
}
