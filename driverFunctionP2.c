/**************************************************************
* Class: CSC-415-0# Spring 2020
* Group Name: teamOne
* Name: Kelvin Ching Kiu Chan
* Student ID: 918171155
* Name: Brian Nguyen 
* Student ID: 915430040
* Name: Edmund John Cruz
* Student ID: 918363633
* Name: Kamelia Shaharova
* Student ID: 917591069
*
* Project: CSC 415 Assignment 3 – File System
*
* File: driverFunctionP2.c
*
* Description: functions that provide deleting a directory and going to a current directory
*
**************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "FileSystemInfo.h"

void deletingDir(char *name){

	//vars used
	char userInput2[100];
	int subIndex=0;
	int subIndex1=0;

	if(numOfDirsRAM<1||numOfFilesRAM==0){
		printf("There is nothing to delete\n");
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

	//check directory first
	uint32_t tempcdLoc=cdLoc;
	char *tempCd= strdup(cd);
	int retVal= containsName(userInput2, 1);
	int directoryIndex= retVal;
	int fileIndex=-1;

	//printf("yo %s\n", userInput2);

	if(retVal==-1){

		//check files
		retVal= containsName(userInput2,3);
		if(retVal==-1){
			printf("This name never existed in this directory\n");
			return;
		}

		fileIndex= retVal;

	}

	printf("index: %d\n",directoryIndex);

	if(fileIndex==-1){
		//now removing directory
		
		//find the subIndex in the parent directory
		subIndex= subIndexOfDir(userInput2);
	
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
			//printf("test dump %s\n",temp);
			if(temp!=NULL&&strcmp(temp," ")!=0&&strcmp(temp,"")!=0){
				//printf("N1 %s\n", temp);
				cd= strdup(dirEntries[directoryIndex].dirName);
				cdLoc= directoryIndex;
				deletingDir(temp);
				dirEntries[directoryIndex].subDirs[i]=strdup(" ");
			}else{
				dirEntries[directoryIndex].subDirs[i]=strdup(" ");
			}
			cdLoc=tempcdLoc;
			cd= strdup(tempCd);
		}

		//remove the sub files
		for(uint32_t i=0;i<MAXNUMOFSUBFILES;i++){
			//printf("test N %s\n",dirEntries[directoryIndex].subFiles[i]);
			char *temp1= dirEntries[directoryIndex].subFiles[i];
			if(temp1!=NULL&&strcmp(temp1," ")!=0&&strcmp(temp1,"")!=0){
				//printf("test N1 %s\n", temp1);
				cdLoc= directoryIndex;
				deletingDir(strdup(temp1));
				dirEntries[directoryIndex].subFiles[i]=strdup(" ");
			}else{
				dirEntries[directoryIndex].subFiles[i]=strdup(" ");
			}
			cdLoc= tempcdLoc;
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
		subIndex1= subIndexOfFile(userInput2);

		if(subIndex1==-1){
			printf("unexpected error happened\n");
			return;
		}

		//remove the name from parent directory first
		dirEntries[cdLoc].subFiles[subIndex1]= strdup(" ");

		//remove the metadata
		strcpy(fileEntries[fileIndex].fileName, strdup(" "));
		strcpy(fileEntries[fileIndex].content, strdup(" "));
		fileEntries[fileIndex].id=0;
		fileEntries[fileIndex].date=0;

		printf("test index: %d\n",fileIndex);
		numOfFreeFiles+=1;
		freeEntriesFile[numOfFreeFiles]=fileIndex;
		return;
	}

	return;

}

int currentDir(char *name){

	//var used
	char userInput[100];

	if(strlen(name)<1||strlen(name)>49){
		//printf("Please enter the name\n");
		scanf("%s",userInput);
	}else{
		strcpy(userInput,name);
	}

	//check user input
	if(strlen(userInput)>49){
		printf("User input too long\n");
		return -1;
	}

	//parent directory
	if(strcmp(userInput,"..")==0){
		if(cdCount>0){
			cdLoc= cdArr[--cdCount];
		}
		cd= strdup(dirEntries[cdLoc].dirName);
		return 1;
	}
				

	int retVal= containsName(userInput,2);

	if(retVal==-1){
		printf("This name doesn't exist in the directory\n");
		return -1;
	}

	printf("test cdLoc: %d\n", retVal);

	cdArr[cdCount++]=cdLoc;
	cdLoc= retVal;
	cd= strdup(dirEntries[cdLoc].dirName);
	return 1;
}
	
	




























