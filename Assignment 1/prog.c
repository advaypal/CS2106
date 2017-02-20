/*

Student Name: S. Ram Janarthana Raja
Student NO: A0147620L

Student Name: Advay Pal
Student NO: A0144939R


*/
 
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], const char **envp) {
	char** env = envp;
	char* shell_path = NULL;
	char* path = NULL;
	for ( ; *env != 0; env++) {
		char *thisEnv = *env;
		if (shell_path == NULL) {
			shell_path = strstr(thisEnv, "SHELL_PATH");
			if(shell_path != NULL) {
				path = strstr(shell_path, "=");
				path++;
			}
	
		} 
		printf("%s\n", thisEnv);
	}
	if (path == NULL) {	
		printf("\nSHELL_PATH value is UNKNOWN\n");
	} else {
		printf("\nSHELL_PATH value is %s", path);
	}

	return(0);

}

