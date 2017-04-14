#include "libefs.h"

int main(int ac, char **av)
{
	if(ac != 3)
	{
		printf("\nUsage: %s <file to check set attrbute> <attribute>\n", av[0]);
		printf("Attribute: 'R' = Read only, 'W' = Read/Write\n\n");
		return -1;
	}

	initFS("part.dsk", "randompassword");
    int code; 
	if (strcmp(av[2],"r") == 0 || strcmp(av[2], "R") == 0) {
		code = 0b101;
	} else if (strcmp(av[2],"w") == 0 || strcmp(av[2], "W") == 0) {
		code = 0b001;
	} else {
		printf("%s\n", "Invalid code");
		closeFS();
		return -1;
	}
	int result = setAttribute(av[1], code);
	if(result == 0) {
		printf("File not found ERROR");
	}

	closeFS();
	return 0;
}
