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
	char *buffer = makeNewDataBuffer();
	unsigned long len = fread(buffer, sizeof(char), 8192, fp);

	initFS("part.dsk", av[2]);	
	int fileOpen = openFile(av[1], MODE_READ_APPEND);
	if(fileOpen != -1) {
		printf("DUPLICATE FILE ERROR\n");
		closeFile(fileOpen);
		closeFS();
		exit(-1);
	}
	fileOpen = openFile(av[1], MODE_CREATE);
	writeFile(fileOpen, buffer, sizeof(char), (int)(len / sizeof(char)));
	closeFile(fileOpen);	
	closeFS();
	return 0;
}
