/*

Student Name: S. Ram Janarthana Raja
Student NO: A0147620L

Student Name: Advay Pal
Student NO: A0144939R

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	char str[100];
	while (1) {
		printf("\n> ");
		char str[1024];
		gets(str);
		int pid = fork();
		if (pid > 0) {
			int status;
			while(wait(&status) != pid) {
			}				
		} else if (pid == 0) {
			printf("Loading new process with id  %d\n", getpid());
			printf("Parent pid: %d\n", getppid());
			fflush(stdout);
			char* arg[64];
			int i = 0;
			for (char *p = strtok(str, " "); p != NULL; p = strtok(NULL, " ")) {
				arg[i++] = p;
			}
			arg[i] = NULL;
			int result = execvp(arg[0], arg);
			if (result < 0) {
				perror("Shell error");
				exit(1);
			} 
		} else {
			perror("Fork failed");
			exit(1);
		}			
	}
}
			
