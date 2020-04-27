#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "fsLow.h"

//contains

//helper method
int findPositionOfDirectory(char *name){

	for(uint32_t i=0; i<numOfDirsRAM;i++){
		if(strcmp(dirEntries[i].dirName,name)==0){
			if(strcmp(dirEntries[i].parentDir,cd)==0){
				return i;
			}
		}
	}

	return -1;

}

//helper method
int findPositionOfFile(char *name){
	
	for(uint32_t i=0; i<numOfFilesRAM;i++){
		if(strcmp(fileEntries[i].fileName,name)==0){
			if(cdLoc==fileEntries[i].id){
				return i;
			}
		}
	}

	return -1;

}

int containsName(char *name, uint32_t function){

	if(cdLoc<0){
		printf("Not a valid current directory location\n");
		return -1;
	}

	if(function>0&&function!=3){
		if(numOfDirsRAM==0){
			return -1;
		}
		//checking directories have this name
		for(uint32_t i=0;i<MAXNUMOFSUBDIRS;i++){
			char *dirname= dirEntries[cdLoc].subDirs[i];
			if(dirname!=NULL&&strcmp(dirname,name)==0){
				int returnAdr= findPositionOfDirectory(name);
				return returnAdr;
			}
		}
	}
	if(function>1){
		if(numOfFilesRAM==0){
			return -1;
		}
		//checking files have this name
		for(uint32_t i=0;i<MAXNUMOFSUBFILES;i++){
			char *filename= dirEntries[cdLoc].subFiles[i];
			if(filename!=NULL&&strcmp(filename,name)==0){
				int returnAdr= findPositionOfFile(name);
				return returnAdr;
			}
		}
	}

	return -1;
		
}

//checking if you can create a directory

int checkDirectoryCanCreate(){

	printf("Number of free entries atm %d\n",numOfFreeDirs);

	if(numOfFreeDirs>0){
		int ret= freeEntriesDir[numOfFreeDirs];
		printf("the free entry: %d\n",ret);
		numOfFreeDirs-=1;
		return ret;
	}

	if(numOfDirsRAM>MAXNUMSOFDIRS-1){
		printf("You've created too many directories\n");
		return -1;
	}

	return numOfDirsRAM;

}

int checkFileCanCreate(){

	if(numOfFreeFiles>0){
		int ret= freeEntriesFile[numOfFreeFiles];
		printf("test free: %d\n",ret);
		numOfFreeFiles-=1;
		return ret;
	}

	if(numOfFilesRAM>MAXNUMSOFFILES-1){
		printf("You've created too many files\n");
		return -1;
	}

	return numOfFilesRAM;

}

//check overflows

int overflowDirectories(){
	
	if(numOfDirsRAM==0){
		return 0;
	}

	for(uint32_t i=0;i<MAXNUMOFSUBDIRS;i++){
		printf("test %d : %s\n", i, dirEntries[cdLoc].subDirs[i]);
		if(dirEntries[cdLoc].subDirs[i]==NULL||strcmp(dirEntries[cdLoc].subDirs[i]," ")==0||strcmp(dirEntries[cdLoc].subDirs[i],"")==0){
			return i;
		}
	}

	return -1;
}

int overflowFiles(){

	for(uint32_t i=0;i<MAXNUMOFSUBFILES;i++){
		if(dirEntries[cdLoc].subFiles[i]==NULL||strcmp(dirEntries[cdLoc].subFiles[i]," ")==0||strcmp(dirEntries[cdLoc].subFiles[i],"")==0){
			return i;
		}
	}

	return -1;

}

	
//find Directory






























	
	

	


