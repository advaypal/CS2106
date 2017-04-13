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
	unsigned long len = fread(buffer, sizeof(char), fs->blockSize, fp);

	initFS("part.dsk", av[2]);	
	int fileOpen = openFile(MODE_APPEND, av[1]);
	if(fileOpen != -1) {
		printf("DUPLICATE FILE ERROR\n");
		closeFile(fileOpen);
		closeFS();
		exit(-1);
	}
	fileOpen = openFile(MODE_CREATE, av[1]);
	writeFile(fileOpen, buffer, sizeof(char), (int)(len / sizeof(char)));
	closeFile(fileOpen);	
	closeFS();
	return 0;
}