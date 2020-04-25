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

//creating a directory
void creatingDir(char *parent, char* name){

	//vars used
	char userInput[100];

	//check if you created too many directories
	int subIndex= overflowDirectories();

	if(subIndex==-1){
		printf("you've reach the maximum number of sub directories use\n");
		return;
	}

	int index= checkDirectoryCanCreate();

	if(index==-1){
		printf("Unable to make directory\n");
		return;
	}
	
	//check user input and outside input
	if(strlen(name)<1||strlen(name)>49){
		printf("Please enter the directory name\n");
		scanf("%s",userInput);
	}else{
		strcpy(userInput,name);
	}

	//check user input
	if(strlen(userInput)>49){
		printf("User input too long\n");
		return;
	}

	if(containsName(userInput,2)>0){
		printf("\nThis name already exist in the current directory\n");
		return;
	}

	strcpy(dirEntries[index].parentDir, strdup(parent));
	dirEntries[index].date = 0;
	strcpy(dirEntries[index].dirName, strdup(userInput));
	dirEntries[index].id= 1;

	if(numOfDirsRAM>0){
		dirEntries[cdLoc].subDirs[subIndex]=strdup(userInput);
	}

	if(index==numOfDirsRAM){
		numOfDirsRAM+=1;
	}

}

//creating a file
void creatingFile(char *name){

	//vars used
	char userInput1[100];
	
	//check if you created too many files
	int subIndex= overflowFiles();

	if(subIndex==-1){
		printf("You've reached the maximum number of sub files use\n");
		return;
	}

	int fileIndex= checkFileCanCreate();

	if(fileIndex==-1){
		printf("Unable to make a file\n");
		return;
	}

	//check user input and outside input
	if(strlen(name)<1||strlen(name)>49){
		printf("Please enter the file name\n");
		scanf("%s",userInput1);
	}else{
		strcpy(userInput1,name);
	}

	if(strlen(userInput1)>49){
		printf("User input too long\n");
		return;
	}

	if(containsName(userInput1,2)>0){
		printf("\nThis name already exist in the current directory\n");
		return;
	}

	strcpy(fileEntries[fileIndex].fileName, strdup(userInput1));
	strcpy(fileEntries[fileIndex].content, " ");
	fileEntries[fileIndex].id= cdLoc;
	fileEntries[fileIndex].date= numOfFilesRAM;

	if(numOfDirsRAM>0){
		dirEntries[cdLoc].subFiles[subIndex]= strdup(userInput1);
	}
	
	if(fileIndex==numOfFilesRAM){
		numOfFilesRAM+=1;
	}

}








