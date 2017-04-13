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
	int fileOpen = openFile(MODE_READ_ONLY, av[1]);
	if (fileOpen == -1) {
		printf("FILE NOT FOUND");
		closeFS()
		exit(-1);
	}
	//define len
	//are they both the same?
	readFile(fileOpen, buffer, sizeof(char), len);

	FILE *fp = fopen(av[1], "w");

	// Write the data
	fwrite(buffer, sizeof(char), len, fp);

	// Close the file
	fclose(fp);
	closeFS();
	return 0;
}
