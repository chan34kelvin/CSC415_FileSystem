#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "FileSystemInfo.h"

//creating a directory
int creatingDir(char *parent, char* name, char *arr1[MAXNUMOFSUBDIRS], char *arr2[MAXNUMOFSUBFILES], int function){

	//vars used
	char userInput[100];

	//check if you created too many directories
	int subIndex= overflowDirectories();

	if(subIndex==-1){
		printf("you've reach the maximum number of sub directories use\n");
		return -1;
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
		return -1;
	}

	if(containsName(userInput,2)>-1){
		printf("\nThis name already exist in the current directory\n");
		return -1;
	}

	int index= checkDirectoryCanCreate();

	if(index==-1){
		printf("Unable to make directory\n");
		return -1;
	}

	//for move and copy
	if(function ==2){
		for(int i=0;i<MAXNUMOFSUBDIRS;i++){
			strcpy(dirEntries[index].subDirs,arr1);
		}
		for(int i=0;i<MAXNUMOFSUBFILES;i++){
			strcpy(dirEntries[index].subFiles,arr2);
		}
	}

	strcpy(dirEntries[index].parentDir, strdup(parent));
	printf("parent : %s\n", dirEntries[index].parentDir);
	dirEntries[index].date = 10000+numOfDirsRAM;
	strcpy(dirEntries[index].dirName, strdup(userInput));
	dirEntries[index].id= cdLoc;

	dirEntries[cdLoc].subDirs[subIndex]=strdup(userInput);

	if(index==numOfDirsRAM){
		numOfDirsRAM+=1;
	}

	return index;

}

//creating a file
int creatingFile(char *name, char* content, int function){

	//vars used
	char userInput1[100];
	
	//check if you created too many files
	int subIndex= overflowFiles();

	if(subIndex==-1){
		printf("You've reached the maximum number of sub files use\n");
		return -1;
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
		return -1;
	}

	if(containsName(userInput1,2)>-1){
		printf("\nThis name already exist in the current directory\n");
		return -1;
	}

	int fileIndex= checkFileCanCreate();

	if(fileIndex==-1){
		printf("Unable to make a file\n");
		return -1;
	}

	if(function !=2){
		content= " ";
	}

	strcpy(fileEntries[fileIndex].fileName, strdup(userInput1));
	strcpy(fileEntries[fileIndex].content, strdup(content));
	fileEntries[fileIndex].id= cdLoc;
	fileEntries[fileIndex].date= 30000+numOfFilesRAM;

	dirEntries[cdLoc].subFiles[subIndex]= strdup(userInput1);
	
	if(fileIndex==numOfFilesRAM){
		numOfFilesRAM+=1;
	}

	return fileIndex;

}








