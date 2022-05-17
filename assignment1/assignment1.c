/**
 * CS 3305A
 * September 28th 2020
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

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Invalid arguments\n");
		exit(0);
	}

	pid_t pid;
	pid_t parent;
	pid_t child1;

	pid = fork();

	if (pid <0){
		printf("Error: Fork process failed"); 											//catching error if it occurs
		exit(pid);
	}

	if (pid > 0){															//if in the parent
		printf("parent process (PID %d) created child_1 (PID %d) \n", getpid(), pid);
		printf("parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", getpid(), pid);
		parent = getpid();	
		wait(NULL); 														//waiting till processes terminate
		pid = fork();														//creating child_2

		if (pid == 0){														//if in child_2
		}
		wait(NULL);														//waiting till processes terminate
		
		
		if (parent == getpid()){												//if on parent pid 
		pid = fork();														//create child of child_2

			if(pid == 0){													//if in child_2
				pid = getpid();
				printf("parent (PID %d) created child_2 (PID %d)\n", getppid() , pid);
				printf("child_2 (PID %d) is calling an external program external_program.out and leaving child_2..\n", pid);
				execl("./B", "./B", (char*) NULL);									//execute external file
				return -1;												//return -1 if process fails
			}	
		}
	}

	else{
		pid = fork();														//create child_1.1
		if(pid == 0){														//if in child_1.1
			pid = getppid();
			printf("child_1 (PID %d) created child_1.1 (PID %d)\n", pid, getpid());						
			printf("child_1 (PID %d) is now complete\n", pid);
		}
	}


	return 0;

}
