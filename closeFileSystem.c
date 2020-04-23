#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "fsLow.h"

//end file system
void closingFileSystem(uint64_t blockSize){
	//make a memory pointer to system
	memEnd= malloc(blockSize *2);

	//writing files
	writingFiles(blockSize);

	//writing directories
	writingDir(blockSize);

	//writing free Entries
	writingFree(blockSize);

	//writing memory
	LBAwrite(memEnd,1,0);
	
}

//find actual block size needed  helper method  finished
int findStoringPos( uint32_t length, uint64_t blockSize, uint32_t bytes){
	uint32_t actualBlockSize = ((length*bytes)/blockSize)+1;
	return actualBlockSize;
}

//writing files into LBA  finished
void writingFiles(uint64_t blockSize){
	//vars used inside
	

	//store file count
	memEnd->numOfFiles= numOfFilesRAM;

	//check if there's any file entries to store
	if(numOfFilesRAM==0){
		return;
	}

	//LBAwrite file names
	char *fileNamesEnd= malloc((MAXNUMSOFFILES*MAXFILENAMEBYTES)+1);
	
	//NULL is ""
	for(uint32_t i=0;i<numOfFilesRAM;i++){
		if(strcmp(fileEntries[i].fileName,"")!=0){
			strcat(fileNamesEnd,fileEntries[i].fileName);
		}else{
			strcat(fileNamesEnd," ");
		}
		strcat(fileNamesEnd,delim1st);
	}

	uint32_t blockCountFileName= findStoringPos(strlen(fileNamesEnd),blockSize,sizeof(char));
	memEnd->blockCountFileNames= blockCountFileName;
	memEnd-> posFileNames= LBApos;

	//printf("file names %d\n", LBApos);
	LBAwrite(fileNamesEnd,blockCountFileName,LBApos);

	//inc 
	LBApos+=blockCountFileName;

	//LBAwrite contents
	char *contentsEnd= malloc((MAXCONTENTBYTES*MAXNUMSOFFILES)+1);
	
	//NULL is ""
	for(uint32_t i=0;i<numOfFilesRAM;i++){
		if(strcmp(fileEntries[i].content,"")!=0){
			strcat(contentsEnd,fileEntries[i].content);
		}else{
			strcat(contentsEnd," ");
		}
		strcat(contentsEnd,delim1st);
	}

	uint32_t blockCountFileContent= findStoringPos(strlen(contentsEnd),blockSize,sizeof(char));
	memEnd->blockCountFileContents= blockCountFileContent;
	memEnd->posFileContents= LBApos;

	//printf("file content %d\n", LBApos);
	LBAwrite(contentsEnd,blockCountFileContent,LBApos);

	//inc
	LBApos+=blockCountFileContent;

	//LBAwrite date
	uint32_t fileDatesEnd[numOfFilesRAM];
	
	for(uint32_t i=0;i<numOfFilesRAM;i++){
		fileDatesEnd[i]=fileEntries[i].date;
	}

	uint32_t blockCountFileDate= findStoringPos(numOfFilesRAM,blockSize,sizeof(uint32_t));
	memEnd-> blockCountFileDates= blockCountFileDate;
	memEnd-> posFileDates= LBApos;

	//printf("file dates %d\n", LBApos);
	LBAwrite(fileDatesEnd,blockCountFileDate,LBApos);

	//inc 
	LBApos+=blockCountFileDate;
	
	//LBAwrite file id
	uint32_t fileIdsEnd[numOfFilesRAM];

	for(uint32_t i=0;i<numOfFilesRAM;i++){
		fileIdsEnd[i]=fileEntries[i].id;
	}

	uint32_t blockCountFileId= findStoringPos(numOfFilesRAM,blockSize,sizeof(uint32_t));
	memEnd-> blockCountFileIds= blockCountFileId;
	memEnd-> posFileIds= LBApos;

	//printf("file ids %d\n",LBApos);
	LBAwrite(fileIdsEnd,blockCountFileId,LBApos);

	//inc 
	LBApos+=blockCountFileId;

	//free
	memset(fileNamesEnd,0,(MAXNUMSOFFILES*MAXFILENAMEBYTES)+1);
	memset(contentsEnd,0,(MAXCONTENTBYTES*MAXNUMSOFFILES)+1);
	free(fileNamesEnd);
	free(contentsEnd);
	
}

//writing Directories into LBA   finished
void writingDir(uint64_t blockSize){
	//vars used inside

	//store directory count
	memEnd-> numOfDirs= numOfDirsRAM;

	//check if there's any directories to store
	if(numOfDirsRAM==0){
		return;
	}

	//LBAwrite dir names
	char *dirNamesEnd= malloc((MAXNUMSOFDIRS*MAXDIRNAMEBYTES)+1);
	printf("test before: %s\n",dirNamesEnd);
	//NULL is ""
	for(uint32_t i=0;i<numOfDirsRAM;i++){
		if(strcmp(dirEntries[i].dirName,"")!=0){
			printf("test loop: %s\n", dirEntries[i].dirName);
			strcat(dirNamesEnd,dirEntries[i].dirName);
		}else{
			strcat(dirNamesEnd," ");
		}
		strcat(dirNamesEnd,delim1st);
	}

	printf("test: %s\n",dirNamesEnd);
	uint32_t blockCountDirName= findStoringPos(strlen(dirNamesEnd),blockSize,sizeof(char));
	memEnd->blockCountDirNames= blockCountDirName;
	memEnd-> posDirNames= LBApos;

	//printf("dir names %d\n",LBApos);
	LBAwrite(dirNamesEnd,blockCountDirName,LBApos);

	//inc 
	LBApos+=blockCountDirName;

	//LBAwrite dir parents
	char *dirParentsEnd= malloc((MAXNUMSOFDIRS*MAXDIRNAMEBYTES)+1);
	
	//NULL is ""
	for(uint32_t i=0;i<numOfDirsRAM;i++){
		if(strcmp(dirEntries[i].parentDir,"")!=0){
			strcat(dirParentsEnd,dirEntries[i].parentDir);
		}else{
			strcat(dirParentsEnd," ");
		}
		strcat(dirParentsEnd,delim1st);
	}

	uint32_t blockCountDirParents= findStoringPos(strlen(dirParentsEnd),blockSize,sizeof(char));
	memEnd->blockCountParent= blockCountDirParents;
	memEnd-> posParent= LBApos;

	//printf("directory parent %d\n",LBApos);
	LBAwrite(dirParentsEnd,blockCountDirParents,LBApos);

	//inc 
	LBApos+=blockCountDirParents;

	//LBAwrite sub directories
	char *dirChildEnd= malloc((MAXNUMSOFDIRS*MAXDIRNAMEBYTES)*MAXNUMOFSUBDIRS);

	for(uint32_t i=0;i<numOfDirsRAM;i++){
		for(uint32_t j=0;j<MAXNUMOFSUBDIRS;j++){
			char *y;
			y=dirEntries[i].subDirs[j];
			if(y!=NULL){
				strcat(dirChildEnd,y);
			}else if(y==NULL){
				strcat(dirChildEnd," ");
			}
			strcat(dirChildEnd,delim2nd);
		}
		strcat(dirChildEnd,delim1st);
	}

	uint32_t blockCountSubDir= findStoringPos(strlen(dirChildEnd),blockSize,sizeof(char));
	memEnd-> blockCountSubDirs= blockCountSubDir;
	memEnd-> posSubDirs= LBApos;

	//printf("directory sub dirs %d\n", LBApos);
	LBAwrite(dirChildEnd, blockCountSubDir, LBApos);

	//inc
	LBApos+=blockCountSubDir;

	//LBAwrite sub files
	char * dirFilesEnd= malloc((MAXNUMOFSUBFILES*MAXFILENAMEBYTES)*MAXNUMOFSUBFILES);
	for(uint32_t i=0;i<numOfDirsRAM;i++){
		for(uint32_t j=0;j<MAXNUMOFSUBFILES;j++){
			char *x;
			x=dirEntries[i].subFiles[j];
			if(x!=NULL){
				strcat(dirFilesEnd,x);
			}else if(x==NULL){
				strcat(dirFilesEnd," ");
			}
			strcat(dirFilesEnd,delim2nd);
		}
		strcat(dirFilesEnd,delim1st);
	}

	uint32_t blockCountSubFile= findStoringPos(strlen(dirFilesEnd),blockSize,sizeof(char));
	memEnd-> blockCountSubFiles= blockCountSubFile;
	memEnd-> posSubFiles= LBApos;

	LBAwrite(dirFilesEnd, blockCountSubFile, LBApos);

	//inc
	LBApos+=blockCountSubFile;

	//LBAwrite ids
	uint32_t dirIds[numOfDirsRAM];
	
	for(uint32_t i=0;i<numOfDirsRAM;i++){
		dirIds[i]=dirEntries[i].id;
	}

	uint32_t blockCountDirId= findStoringPos(numOfDirsRAM,blockSize,sizeof(uint32_t));
	memEnd-> blockCountDirIds= blockCountDirId;
	memEnd-> posDirIds= LBApos;

	//printf("directory ids: %d\n",LBApos);
	LBAwrite(dirIds, blockCountDirId, LBApos);

	//inc
	LBApos+=blockCountDirId;
	
	//LBAwrite dates
	uint32_t dirDates[numOfDirsRAM];
	
	for(uint32_t i=0;i<numOfDirsRAM;i++){
		dirDates[i]=dirEntries[i].date;
	}

	uint32_t blockCountDirDate= findStoringPos(numOfDirsRAM,blockSize,sizeof(uint32_t));
	memEnd-> blockCountDirDates= blockCountDirDate;
	memEnd-> posDirDates= LBApos;

	//printf("directory dates %d\n",LBApos);
	LBAwrite(dirDates, blockCountDirDate, LBApos);

	//inc
	LBApos+=blockCountDirDate; 

	//free
	memset(dirNamesEnd,0,(MAXNUMSOFDIRS*MAXDIRNAMEBYTES)+1);
	memset(dirParentsEnd,0, (MAXNUMSOFDIRS*MAXDIRNAMEBYTES)+1);
	memset(dirChildEnd,0, (MAXNUMSOFDIRS*MAXDIRNAMEBYTES)*MAXNUMOFSUBDIRS);
	memset(dirFilesEnd,0, (MAXNUMOFSUBFILES*MAXFILENAMEBYTES)*MAXNUMOFSUBFILES);
	free(dirNamesEnd);
	free(dirParentsEnd);
	free(dirChildEnd);
	free(dirFilesEnd);
	
}

void writingFree(uint64_t blockSize){

	//LBAwrite files
	uint32_t freeFiles[numOfFilesRAM];

	for(uint32_t i=0;i<numOfFilesRAM;i++){
		freeFiles[i]= freeEntriesFile[i];
	}

	uint32_t blockCountFreeFile= findStoringPos(numOfFilesRAM, blockSize, sizeof(uint32_t));
	memEnd-> blockCountFreeFiles= blockCountFreeFile;
	memEnd-> posFreeFiles= LBApos;

	LBAwrite(freeFiles, blockCountFreeFile, LBApos);

	//inc
	LBApos+=blockCountFreeFile;

	//LBAwrite directories
	uint32_t freeDirs[numOfDirsRAM];

	for(uint32_t i=0;i<numOfDirsRAM;i++){
		freeDirs[i]= freeEntriesDir[i];
	}

	uint32_t blockCountFreeDir= findStoringPos(numOfDirsRAM, blockSize, sizeof(uint32_t));
	memEnd-> blockCountFreeDirs= blockCountFreeDir;
	memEnd-> posFreeDirs= LBApos;

	LBAwrite(freeDirs, blockCountFreeDir, LBApos);

	//inc
	LBApos+=blockCountFreeDir;

}




































