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

int main(int argc, char *argv[]){
	//vars inside main and initialize
	char *filename= (argc>0)? argv[1]:"";
	uint64_t volumeSize= (argc>1)? atoll(argv[2]):0;
	uint64_t blockSize= (argc>2)? atoll(argv[3]):0;

	//start partition 
	startPartitionSystem (filename, &volumeSize, &blockSize);

	//initialize all variables use in RAM
	initializeFileSystem(blockSize);	
	//printf("test: %d\n",fileEntries[2].id);
	//test
	/*for(int i=0;i<50;i++){
		char name[51]="test";
		//strcat(name,atoll(i));
		fileEntries[i].id=i;
		dirEntries[i].id=i;
		strcpy(fileEntries[i].fileName, name);
		strcpy(fileEntries[i].content, "OOOOOO");
		strcpy(dirEntries[i].dirName, name);
		strcpy(dirEntries[i].parentDir, "OOOOOO");
	}
	numOfDirsRAM=50;
	numOfFilesRAM=50;*/

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













