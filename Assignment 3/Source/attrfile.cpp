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
	switch (av[2]){
		case 'R' : ;
		case 'r' : code = 1; break;
		case 'W' : ;
		case 'w' : code = 2; break;
		default  : code = 0;
	}
	closeFS();
	return 0;
}
