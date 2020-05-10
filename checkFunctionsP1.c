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
* File: checkFunctionsP1.c
*
* Description: functions that check subdirectories and files
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

//check for remove

int subIndexOfDir(char *name){

	for(uint32_t i=0;i<MAXNUMOFSUBDIRS;i++){
		if(dirEntries[cdLoc].subDirs[i]!=NULL&&strcmp(dirEntries[cdLoc].subDirs[i],name)==0){
			return i;
		}
	}

	return -1;
}
	
int subIndexOfFile(char *name){
	
	for(uint32_t i=0;i<MAXNUMOFSUBFILES;i++){
		if(dirEntries[cdLoc].subFiles[i]!=NULL&&strcmp(dirEntries[cdLoc].subFiles[i],name)==0){
			return i;
		}
	}

	return -1;
}



		
		











