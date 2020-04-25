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

//initialize file system RAM variables
void initializeFileSystem(uint64_t blockSize){
	//vars used inside
	//get items from memory
	//allocate some memory
	memory= malloc(blockSize *2);

	//LBAread
	LBAread(memory, 1,0);

	//Now load data into the variables
	//Files
	initializeFiles(blockSize);

	//Directories
	initializeDirectories(blockSize);

	//initializeFree
	initializeFree(blockSize);
	
}

//initialize all data in files  finished
void initializeFiles(uint64_t blockSize){
	//vars used inside
	numOfFilesRAM= memory->numOfFiles;

	//if theres no files then no need to read
	if(numOfFilesRAM==0){
		return;
	}

	//LBAread filenames
	char *fileNames= malloc(memory->blockCountFileNames*(blockSize*2));

	LBAread(fileNames, memory->blockCountFileNames, memory->posFileNames);

	//parse into file entries
	if(numOfFilesRAM>0){
		strcpy(fileEntries[0].fileName,strtok(fileNames,delim1st));
	}

	for(uint32_t i=1;i<numOfFilesRAM;i++){
		if(fileEntries[i-1].fileName!=NULL){
			strcpy(fileEntries[i].fileName,strtok(NULL,delim1st));
		}else{
			strcpy(fileEntries[i].fileName," ");
		}
	}

	//LBAread content
	char *contents= malloc(memory->blockCountFileContents*(blockSize*2));
	LBAread(contents, memory->blockCountFileContents, memory->posFileContents);

	//parse into file entries
	if(numOfFilesRAM>0){
		strcpy(fileEntries[0].content,strtok(contents,delim1st));
	}

	for(uint32_t i=1;i<numOfFilesRAM;i++){
		if(fileEntries[i-1].content!=NULL){
			strcpy(fileEntries[i].content,strtok(NULL,delim1st));
		}else{
			strcpy(fileEntries[i].content," ");
		}
	}

	//LBAread dates
	uint32_t fileDates[MAXNUMSOFFILES];
	LBAread(fileDates,memory->blockCountFileDates,memory->posFileDates);

	for(int i=0;i<numOfFilesRAM;i++){
		fileEntries[i].date= fileDates[i];
	}

	//LBAread ids
	uint32_t fileIds[MAXNUMSOFFILES];
	LBAread(fileIds,memory->blockCountFileIds,memory->posFileIds);

	for(int i=0;i<numOfFilesRAM;i++){
		fileEntries[i].id= fileIds[i];
	}
	
	//free
	free(fileNames);
	free(contents);

}

//initialize all data in directories  finished
void initializeDirectories(uint64_t blockSize){
	//vars used inside
	numOfDirsRAM= memory->numOfDirs;

	//if theres no directories then no need to read
	if(numOfDirsRAM==0){
		return;
	}

	//LBAread dir names
	char *dirNames= malloc(memory->blockCountDirNames*blockSize);
	LBAread(dirNames,memory->blockCountDirNames,memory->posDirNames);

	//parse into dir entries
	if(numOfDirsRAM>0){
		strcpy(dirEntries[0].dirName,strtok(dirNames,delim1st));
	}

	for(uint32_t i=1;i<numOfDirsRAM;i++){
		if(dirEntries[i-1].dirName!=NULL){
			strcpy(dirEntries[i].dirName,strtok(NULL,delim1st));
		}else{
			strcpy(dirEntries[i].dirName," ");
		}
	}

	//LBAread parent
	char *parent= malloc(memory->blockCountParent*blockSize);
	LBAread(parent, memory->blockCountParent, memory->posParent);

	//parse into dir entries
	if(numOfDirsRAM>0){
		strcpy(dirEntries[0].parentDir, strtok(parent,delim1st));
	}
	
	for(uint32_t i=1;i<numOfDirsRAM;i++){
		if(dirEntries[i-1].parentDir!=NULL){
			strcpy(dirEntries[i].parentDir,strtok(NULL,delim1st));
		}else{
			strcpy(dirEntries[i].parentDir," ");
		}
	}

	//LBAread sub dir entries
	char subDirs[(memory->blockCountSubDirs*blockSize)];
	char * test[numOfDirsRAM];
	char *saveptr;
	LBAread(subDirs,memory->blockCountSubDirs,memory->posSubDirs);
	//printf("test4: %s\n",subDirs);

	if(numOfDirsRAM>0){
		test[0]=strtok(subDirs,delim1st);
	}

	for(uint32_t i=1;i<numOfDirsRAM;i++){
		if(subDirs!=NULL){
			test[i]=strtok(NULL,delim1st);
		}
	}

	//printf("test size: %d\n",numOfDirsRAM);
	for(int i=0;i<numOfDirsRAM;i++){
		//printf("This is test %d with %s\n",i,test[i]);
	}

	for(uint32_t i=0;i<numOfDirsRAM;i++){
		char *parsing1= malloc(blockSize);
		parsing1= strtok(test[i],delim2nd);
		dirEntries[i].subDirs[0]=strdup(parsing1);
		for(uint32_t j=1;j<MAXNUMOFSUBDIRS;j++){
			if(parsing1!=NULL){
				dirEntries[i].subDirs[j]=strtok(NULL,delim2nd);
			}else{
				printf("FAILED");
			}
		}
	}
	//printf("test1: %s\n",dirEntries[0].subDirs[1]);

	//LBAread sub files
	char subFile[(memory->blockCountSubFiles*blockSize)];
	char *parsing2;
	char *test1[numOfDirsRAM];
	LBAread(subFile,memory->blockCountSubFiles,memory->posSubFiles);

	if(numOfDirsRAM>0){
		test1[0]=strtok(subFile,delim1st);
	}

	for(uint32_t i=1;i<numOfDirsRAM;i++){
		if(subFile!=NULL){
			test1[i]=strtok(NULL,delim1st);
		}
	}

	for(uint32_t i=0;i<numOfDirsRAM;i++){
		char *parsing2= malloc(blockSize);
		parsing2= strtok(test1[i],delim2nd);
		dirEntries[i].subFiles[0]=strdup(parsing2);
		for(uint32_t j=1;j<MAXNUMOFSUBFILES;j++){
			if(parsing2!=NULL){
				dirEntries[i].subFiles[j]=strtok(NULL,delim2nd);
			}else{
				printf("FAILED");
			}
		}
	}

	//LBAread dates
	uint32_t dirDates[MAXNUMSOFDIRS];
	LBAread(dirDates, memory->blockCountDirDates, memory->posDirDates);


	for(uint32_t i=0;i<numOfDirsRAM;i++){
		dirEntries[i].date= dirDates[i];
	}

	//LBAread ids
	uint32_t dirIds[MAXNUMSOFDIRS];
	LBAread(dirIds,memory->blockCountDirIds,memory->posDirIds);

	for(int i=0;i<numOfDirsRAM;i++){
		dirEntries[i].id= dirIds[i];
	}

	//free
	free(dirNames);
	free(parent);

}

void initializeFree(uint64_t blockSize){
	
	numOfFreeFiles= memory->numOfFreeFilesLoad;
	numOfFreeDirs= memory->numOfFreeDirsLoad;

	printf("Number of free entries atm3 %d\n",numOfFreeDirs);

	if(numOfFreeFiles>0){
		//file entries
		uint32_t fileFreeEntries[MAXNUMSOFFILES+1];
		LBAread(fileFreeEntries, memory->blockCountFreeFiles, memory->posFreeFiles);

		for(uint32_t i=1;i<=numOfFreeFiles;i++){
			freeEntriesFile[i]=fileFreeEntries[i];
		}
	}

	if(numOfFreeDirs>0){
		//directory entries
		uint32_t dirFreeEntries[MAXNUMSOFDIRS+1];
		LBAread(dirFreeEntries, memory->blockCountFreeDirs, memory->posFreeDirs);

		for(uint32_t i=1;i<=numOfFreeDirs;i++){
			freeEntriesDir[i]=dirFreeEntries[i];
		}
	}
}


































