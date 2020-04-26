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

void deletingDir(char *name){

	//vars used
	char userInput[100];
	int subIndex=0;
	int subIndex1=0;

	if(numOfDirsRAM<2||numOfFilesRAM==0){
		printf("There is nothing to delete\n");
		return;
	}

	//check valid input
	if(strlen(name)<1||strlen(name)>49){
		printf("Please enter the name\n");
		scanf("%s",userInput);
	}else{
		strcpy(userInput,name);
	}

	//check user input
	if(strlen(userInput)>49){
		printf("User input too long\n");
		return;
	}

	//check directory first
	uint32_t tempcdLoc=cdLoc;
	char *tempCd= strdup(cd);
	int retVal= containsName(userInput, 1);
	int directoryIndex= retVal;
	int fileIndex=-1;

	if(retVal==-1){

		//check files
		retVal= containsName(userInput,3);
		if(retVal==-1){
			printf("This name never existed in this directory\n");
			return;
		}

		fileIndex= retVal;

	}

	if(fileIndex==-1){
		//now removing directory
		
		//find the subIndex in the parent directory
		subIndex= subIndexOfDir(userInput);
	
		if(subIndex==-1){
			printf("unexpected error happened\n");
			return;
		}

		//remove the name from parent directory first
		dirEntries[cdLoc].subDirs[subIndex]= strdup(" ");
		
		//test

		//remove the sub directories
		for(uint32_t i=0;i<MAXNUMOFSUBDIRS;i++){
			char *temp= dirEntries[directoryIndex].subDirs[i];
			if(temp!=NULL&&strcmp(temp," ")!=0&&strcmp(temp,"")!=0){
				cdLoc= directoryIndex;
				deletingDir(strdup(temp));
				dirEntries[directoryIndex].subDirs[i]=strdup(" ");
			}else{
				dirEntries[directoryIndex].subDirs[i]=strdup(" ");
			}
			cdLoc=tempcdLoc;
		}

		//remove the sub files
		for(uint32_t i=0;i<MAXNUMOFSUBFILES;i++){
				dirEntries[directoryIndex].subFiles[i]=strdup(" ");
		}

		//remove the metadata
		strcpy(dirEntries[directoryIndex].dirName," ");
		dirEntries[directoryIndex].date=0;
		dirEntries[directoryIndex].id=0;
		strcpy(dirEntries[directoryIndex].parentDir," ");
		printf("cd Loc5 %d\n",directoryIndex);

		//store into free index
		numOfFreeDirs+=1;
		freeEntriesDir[numOfFreeDirs]=directoryIndex;
		printf("cd Loc6 %d\n",numOfFreeDirs);
		return;
	}else{
		//now removing files

		//find the subIndex
		subIndex1= subIndexOfFile(userInput);

		if(subIndex1==-1){
			printf("unexpected error happened\n");
			return;
		}

		//remove the name from parent directory first
		dirEntries[cdLoc].subFiles[subIndex1]= strdup(" ");

		//remove the metadata
		strcpy(fileEntries[fileIndex].fileName, " ");
		strcpy(fileEntries[fileIndex].content, " ");
		fileEntries[fileIndex].id=0;
		fileEntries[fileIndex].date=0;

		printf("test index: %d\n",fileIndex);
		numOfFreeFiles+=1;
		freeEntriesFile[numOfFreeFiles]=fileIndex;
		return;
	}

	return;
}
