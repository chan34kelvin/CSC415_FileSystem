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



		
		









