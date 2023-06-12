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
* File: fsdriver3.c
*
* Description: Ties all the files together to create the filesystem
*
**************************************************************/

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <string.h>

#include <errno.h>

#include "fsLow.h"

#include <stdint.h>

#include <math.h>

#include "FileSystemInfo.h"





int main(int argc, char *argv[]){

	//vars inside main and initialize

	cd= "ROOT";

	delim1st= "¥";

	delim2nd= "|";

	numOfDirsRAM=0;

	cdLoc=0;

	cdParent=0;

	numOfFilesRAM=0;

	numOfFreeFiles=0;

	numOfFreeDirs=0;

	cdCount=0;

	LBApos=1;

	nullVal=" ";

	char *filename= (argc>0)? argv[1]:"";

	uint64_t volumeSize= (argc>1)? atoll(argv[2]):0;

	uint64_t blockSize= (argc>2)? atoll(argv[3]):0;



	//start partition 

	startPartitionSystem (filename, &volumeSize, &blockSize);



	//initialize all variables use in RAM

	initializeFileSystem(blockSize);



	/*for(int i=1;i<=10;i++){

		printf("at index %d :%d|",i,freeEntriesDir[i]);

	}*/

	printf("Number of free entries atm1 %d\n",numOfFreeDirs);

	//make a ROOT directory

	if(numOfDirsRAM==0){

		cdLoc=numOfDirsRAM;

		creatingDir(nullVal,"ROOT",nullArrDirs,nullArrFiles,0);

	}



	//call control center

	controlCenter(blockSize,volumeSize,filename);



	//close file system

	closingFileSystem(blockSize);



	//close partition

	freeMemory();

	closePartitionSystem();

	return 0;

}



//free all malloc

void freeMemory(){

	free(memory);

	free(memEnd);

}






























