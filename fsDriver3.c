#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "fsLow.h"
#include "FileSystemInfo.h"
#include "initializeFileSystem.c"
#include "closeFileSystem.c"
#include "FileSystemControl.c"
#include "checkFunctionsP1.c"
#include "driverFunctionP1.c"
#include "checkFunctions.c"
#include "driverFunctionP2.c"
#include "driverFunctionP3.c"

int main(int argc, char *argv[]){
	//vars inside main and initialize
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

























