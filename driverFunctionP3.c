#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "fsLow.h"

void cpFunction( char *name, char *name1){
	
	//check
	char userInput[100];
	char userInput1[100];

	if(strlen(name)<1||strlen(name)>49){
		scanf("%s",userInput);
	}else{
		strcpy(userInput,name);
	}

	if(strlen(name1)<1||strlen(name1)>49){
		scanf("%s",userInput1);
	}else{
		strcpy(userInput,name1);
	}

	//check if the file exist
	
	if(containsName(userInput,2)==-1){
		printf("\nThis name doesn't exist in the current directory\n");
		return;
	}

	if(containsName(userInput1,2)==-1){
		printf("\nThis name doesn't exist in the current directory\n");
		return;
	}	

	//
	int retVal= containsName(userInput, 1);
	int directoryIndex= retVal;
	int fileIndex=-1;

	if(retVal==-1){

		//check files
		retVal= containsName(userInput,3);
		if(retVal==-1){
			return;
		}

		fileIndex= retVal;

	}

	//
	int retVal1= containsName(userInput1, 1);
	int directoryIndex1= retVal1;
	int fileIndex1=-1;

	if(retVal1==-1){

		//check files
		retVal1= containsName(userInput1,3);
		if(retVal1==-1){
			return;
		}

		fileIndex1= retVal1;

	}

	if(fileIndex==-1&&fileIndex1==-1){
		printf("XXX\n");
		char arg1[100];
		strcpy(arg1, dirEntries[directoryIndex].dirName);
		currentDir(userInput1);
		int ret= creatingDir(cd, arg1, dirEntries[directoryIndex].subDirs, dirEntries[directoryIndex].subFiles, 2);
		if(ret==-1){
			printf("copy function failed\n");
		}
		currentDir("..");
		return;
	}else if(fileIndex>-1 &&fileIndex1==-1){
		currentDir(userInput1);
		int ret1= creatingFile(fileEntries[fileIndex].fileName, fileEntries[fileIndex].content, 2);
		if(ret1==-1){
			printf("copy function failed\n");
		}
		currentDir("..");
		return;
	}else{
		strcpy(fileEntries[fileIndex1].content, strdup(fileEntries[fileIndex].content));
		return;
	}

	printf("copy function failed\n");
	return;
}
		






























