#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "fsLow.h"

void readingFileFromReal(char *name){

	//vars used
	FILE * file;
	char userInput1[100];
	char content[MAXCONTENTBYTES];
	
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

	if(containsName(userInput1,2)>-1){
		printf("\nThis name already exist in the current directory\n");
		return;
	}

	printf("name: %s\n",userInput1);
	//special function
	file = fopen(userInput1,"r");
	if(file==NULL){
		printf("File Not Found\n");
		return;
	}
	fgets(content,MAXCONTENTBYTES,file);
	fclose(file);
	
	if(strlen(content)==0){
		strcpy(content, " ");
	}

	strcpy(fileEntries[fileIndex].fileName, strdup(userInput1));
	strcpy(fileEntries[fileIndex].content, strdup(content));
	fileEntries[fileIndex].id= cdLoc;
	fileEntries[fileIndex].date= 30000+numOfFilesRAM;

	dirEntries[cdLoc].subFiles[subIndex]= strdup(userInput1);
	
	if(fileIndex==numOfFilesRAM){
		numOfFilesRAM+=1;
	}

}

void writingFileToReal(char *name){

	//vars 
	char userInput2[100];
	FILE *file;

	if(numOfDirsRAM<1||numOfFilesRAM==0){
		printf("There is nothing to read from\n");
		return;
	}

	//check valid input
	if(strlen(name)<1||strlen(name)>49){
		printf("Please enter the name\n");
		scanf("%s",userInput2);
	}else{
		strcpy(userInput2,name);
	}

	//check user input
	if(strlen(userInput2)>49){
		printf("User input too long\n");
		return;
	}

	int retVal= containsName(userInput2,3);
	if(retVal==-1){
		printf("This name never existed in this directory\n");
		return;
	}

	int fileIndex= retVal;

	file= fopen(userInput2, "w");
	fprintf(file, fileEntries[fileIndex].content);
	fclose(file);

	printf("File transfered success\n");
	return;
}
	
















