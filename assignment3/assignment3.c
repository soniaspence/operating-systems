/**
 * CS 3305A
 * October 20th 2020
 * Sonia Spence
 * 250 970 384
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

int x, y, z; 
int errno;

void *sum(){
	z=y+x;
	return NULL;
}

int main(){
	pid_t child;
	pthread_t thread;

    // Initializing the global variables
	x=10, y=20, z=0;
	errno = 0;

	// create child process
	child = fork();
	// check for child creation error
	if (child < 0){
		printf("main function: errno number is %d\n", errno);
	}
	// in parent:
	if (child > 0){
		// wait for child, and print value of z
		wait(NULL);
		printf("Using a fork(), the value of z in the parent process is: %d\n", z);
		// create thread, wait for it to complete, then print value of z

		errno = pthread_create(&thread, NULL, *sum, NULL);
		pthread_join(thread, NULL);
		
		if (errno != 0){
			printf("main function: errno number is %d\n", errno);
		}
		else{
			printf("Using a thread, the value of z is: %d\n", z);
		}
	}
	// in child:
	else{
		// sum x and y and store it in z
		z = x + y;
		// print value of z
		printf("Using a fork(), the value of z in the child process is: %d\n", z); 
	}

	return 0;
}
