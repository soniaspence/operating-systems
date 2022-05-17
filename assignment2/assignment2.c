/**
 * CS 3305A
 * October 8th 2020
 * Sonia Spence
 * 250 970 384
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// Reading and writing end of the pipe
#define READ_END 0
#define WRITE_END 1

int main(int argc, char **argv)
{

char *x, *y, *z, *concat;															//variable declarations
int fd[2];
pid_t pid;
char parentstr[100];

	if (argc != 4)
	{
		printf("Invalid arguments\n");
		exit(0);
	}

	else{
		if(pipe(fd) < 0){														//creating pipe and printing error and quiting if it fails
			printf("Failed to create pipe.");
			exit(0);
		}
		

			printf("A pipe is created for communication between parent (PID %d) and child\n", getpid());				
			pid = fork();														//Fork to create child

			if(pid < 0){
				printf("Failed to create child.");										//If the fork process fails print error and quit
			}

			if(pid > 0){														//If in the parent
				printf("parent (PID %d) created a child (PID %d)\n", getpid(), pid);						
				x = argv[1];													
				printf("parent (PID %d) receives X = \"%s\" from the user\n", getpid(), x);
				wait(NULL);													//Moving to child keeping parent on wait
				read(fd[0], parentstr, 100);											//Reading from pipe
				close(fd[0]);
				printf("parent (PID %d) reads Y' from the pipe (Y' = \"%s\")\n", getpid(), parentstr);
				concat = strcat(x, parentstr);											//Concatenating string from pipe and x
				printf("parent (PID %d) concatenates X and Y' to generate the string: %s\n", getpid(), concat);
			}

			if(pid == 0){														//If in the child
				y = argv[2];
				z = argv[3];
				printf("child (PID %d) receives Y = \"%s\" and Z = \"%s\" from the user\n", getpid(), y, z);
				concat = strcat(y,z);												//Concatenating x and y
				printf("child (PID %d) concatenates Y and Z to generate Y'= %s\n", getpid(), concat);
				write(fd[1], y, strlen(y) +1);											//Writing to pipe
				close(fd[1]);
				printf("child (PID %d) writes Y' into the pipe\n", getpid());

			}
		}
	
return 0;
}
