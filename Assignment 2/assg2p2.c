#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define NUMELTS 16384

// IMPORTANT: Compile using "gcc assg2p2.c -lm -o assg2p2".
// The "-lm" is important as it brings in the Math library.

// Implement the naive primality test.
// Returns TRUE if n is a prime number

int prime(int n) {

    int ret = 1, i;

    for (i = 2; i <= (int) sqrt(n) && ret; i++)
		ret = (n % i);

    return ret;
}

int main() {
    int data[NUMELTS];
    int fd[2];
    
    pipe(fd);
    // Declare other variables here.
    // Create the random number list.
    
    srand(time(NULL));

    for(int i=0; i<NUMELTS; i++)
		data[i] = (int)  (((double) rand () /  (double) RAND_MAX) * 10000);
	
    if(fork()) {
		int count = 0;
		int input;
		
		for(int j = 0; j < 8192; j ++) {
	        if(prime(data[j]))
				count ++;
	}
	    
	close(fd[1]);
	read(fd[0], &input, sizeof(input)); 
	printf("Number of primes: %d", input + count);
	

    } else {
		int count_child = 0;
		
		for(int j = 8192; j < 16384; j++) {
		    if(prime(data[j])) 
				count_child ++;
	    }	

		close(fd[0]);
		write(fd[1], &count_child, sizeof(count_child));
    
    } 

    return 0;
}









