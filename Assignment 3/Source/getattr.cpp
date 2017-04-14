#include "libefs.h"

int main(int ac, char **av)
{
	if(ac != 2)
	{
		printf("\nUsage: %s <file to check>\n", av[0]);
		printf("Prints: 'R' = Read only, 'W' = Read/Write\n\n");
		return -1;
	}
	initFS("part.dsk", "randompassword");
	int result = getAttribute(av[1]);
	if (result == 0) {
		printf("File not found ERROR");
	} else {
		if ((result & 0b100) == 4) {
			printf("R"); 
		} else {
			printf("W"); 
		}
	}

	closeFS();
	return 0;
}
