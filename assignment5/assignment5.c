/**
 * CS 3305A
 * December 4th 2020
 * Sonia Spence
 * 250 970 384
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h> 
#include <pthread.h>

int num_words = 0;

//struct for an account
struct bankAccount{
        int bank_number;
        int balance;
        };

//function to read input and count the number of words
void countWords (FILE * countFile){
	char word[12];
	while(fscanf(countFile, "%11s", word)==1){
		num_words++;
	}
};

//function to put the words in an array
void putWords (FILE * putFile, char input[][13]){
	char put[12];
	int i = 0;
	while(fscanf(putFile, "%11s", put)==1){
		strcpy(input[1], put);
		i++;
	}
}


struct bankAccount bank_accounts [50];
int account = 0;

//function to create an account and put it in an array of accounts
void create (char input[][13], struct bankAccount bank_accounts[]){
	for(int i = 0; i < num_words; i++){
		if(strcmp(input[i], "b") == 0){
			bank_accounts[account].bank_number = account + 1;
			bank_accounts[account].balance = atoi(input[i + 1]);
			account = account + 1;
		}
		else{
			return;
		}
	}
}
			
//function to deposit money in account
void deposit(int bank_number, int amount){
	bank_accounts[bank_number].balance = bank_accounts[bank_number].balance + amount;

}

//function to withdraw money from account
void withdraw(int bank_number, int amount){
	if(bank_accounts[bank_number].balance > amount){
		bank_accounts[bank_number].balance -= amount;
	}
	else{
		return;
	}
}

//function to transfer money from one account to another
void transfer(int bank_number1, int bank_number2, int amount){
	if(bank_accounts[bank_number1].balance > amount){
		bank_accounts[bank_number1].balance -= amount;
		bank_accounts[bank_number2].balance += amount;
	}
	else{
		return;
	}
}

//function to read input from array and do tasks accordingly
void performOperations(char input[][13]){
    pthread_mutex_t lock;
	pthread_mutex_init(&lock, NULL);
	for(int i = 0; i < num_words; i++){
		pthread_mutex_lock(&lock);
                if(strcmp(input[i], "d") == 0){
			int amount = atoi(input[i+2]);
			int bank_number = atoi(input[i+1]) - 1;
			deposit(bank_number, amount);
			printf("a%d b %d", input[i+1], bank_accounts[bank_number].balance); 
		}
		else if(strcmp(input[i], "w") == 0){
			int amount = atoi(input[i + 2]);
			int bank_number = atoi(input[i+1]);
			bank_number -= 1;
			withdraw(bank_number, amount);
			printf("a%d b %d", input[i+1], bank_accounts[bank_number].balance);

		}
		else if(strcmp(input[i], "t") == 0){
			int amount = atoi(input[i+3]);
			int bank_number1 = atoi(input[i+1]);
			int bank_number2 = atoi(input[i+2]);
			transfer(bank_number1, bank_number2, amount);
			printf("a%d b %d", input[i+1], bank_accounts[bank_number1].balance);
			printf("a%d b %d", input[i+2], bank_accounts[bank_number2].balance);
		}
		else{
			return;
		}
		pthread_mutex_unlock(&lock);
	}
	pthread_mutex_destroy(&lock);
}



int main(int args, char* argv[]){
	int index = 0;
	FILE* fileptr;
	//reading file
	fileptr = fopen(argv[1], "r");
	
	//checking if there is an input file
	if(args != 2){
		printf("Please enter a text file.");
		exit(0);
	}
	
	//if the file is empty fails to open
	fileptr = fopen(argv[1], "r");
	if(fileptr == NULL){
		printf("Error: file failed to open");
		exit(1);
	}
	
	countWords(fileptr);
	char input[num_words][13];
	fclose(fileptr);

	struct bankAccount bank_accounts[num_words];
	
	create(input, bank_accounts);
	performOperations(input);
}

