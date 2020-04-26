#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "fsLow.h"

void controlCenter(uint64_t blockSize, uint64_t volumeSize, char* filename){

	char userInput[100];

	//command tell user what to do
	printf("File System is now loaded, Welcome! \n");

	do{
		printf("The system allow commands like : touch, mkdir, cd, ls, cp, mv, rm, and quit\n");
		printf("%s ~system: %s : please type the command you want to use: ", filename, cd);
		scanf("%s", userInput);
		if(strcmp(userInput, "touch")==0){
			//user wants to create a file
			creatingFile("");
		}else if(strcmp(userInput, "mkdir")==0){
			//user wants to create a directory
			//cdLoc=1;
			creatingDir(cd,"");
		}else if(strcmp(userInput, "ls")==0){
			listDirs();
			//user wants to see the list of files and directories
		}else if(strcmp(userInput, "cp")==0){
			//user wants to copy a file or directory into another directory
		}else if(strcmp(userInput, "mv")==0){
			//user wants to move a file or directory into another directory
		}else if(strcmp(userInput, "quit")==0){
			//user wants to end the file system
			return;
		}else if(strcmp(userInput, "cd")==0){
			//user wants to change directory
		}else if(strcmp(userInput, "rm")==0){
			deletingDir("");
			//user wants to delete a file or directory
		}else{
			//user types something invalid
			printf("Command not found\n");
		}
	}while(1);

}
