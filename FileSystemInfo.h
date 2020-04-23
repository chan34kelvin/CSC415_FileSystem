#include <stdio.h>

//maximum for directories
#define MAXNUMSOFDIRS 2000
#define MAXDIRNAMEBYTES 50
#define MAXNUMOFSUBFILES 50
#define MAXNUMOFSUBDIRS 10

//maximum for files
#define MAXNUMSOFFILES 500
#define MAXFILENAMEBYTES 50
#define MAXCONTENTBYTES 500

typedef struct DirectoryEntry{
	//only limited to 50 bytes per dirName
	char dirName[MAXDIRNAMEBYTES];
	char parentDir[MAXDIRNAMEBYTES];

	//initialize id
	uint32_t id;

	//initialize the total number of bytes this file used
	uint32_t numOfBytes;

	//initialize the date it was used
	uint32_t date;

	//The subDir are limited to only 30
	char * subDirs[MAXNUMOFSUBDIRS];

}DirectoryEntry, *DirectoryEntry_P;

typedef struct FileEntry{
	//only limited to 30 bytes
	char fileName[MAXNUMSOFFILES];
	
	//only limited to 500 bytes
	char content[MAXCONTENTBYTES];

	uint32_t date;

	uint32_t id;

}FileEntry, *FileEntry_P;

typedef struct System{
	//File
	uint32_t numOfFiles;

	//filename
	uint32_t blockCountFileNames;
	uint32_t posFileNames;

	//content
	uint32_t blockCountFileContents;
	uint32_t posFileContents;

	//date
	uint32_t blockCountFileDates;
	uint32_t posFileDates;

	//id
	uint32_t blockCountFileIds;
	uint32_t posFileIds;

	//Directory
	uint32_t numOfDirs;

	//dirname
	uint32_t blockCountDirNames;
	uint32_t posDirNames;

	//parent dirname
	uint32_t blockCountParent;
	uint32_t posParent;

	//id
	uint32_t blockCountDirIds;
	uint32_t posDirIds;

	//date
	uint32_t blockCountDirDates;
	uint32_t posDirDates;

	//sub dirs
	uint32_t blockCountSubDirs;
	uint32_t posSubDirs;

	//Free entries
	uint32_t blockCountFreeFiles;
	uint32_t posFreeFiles;

	uint32_t blockCountFreeDirs;
	uint32_t posFreeDirs;	

}System, *System_P;

//For file system use RAM

//delimeters
char *delim1st="|";
char *delim2nd=";";

//make directory entries only a max of 200 directories could be created
DirectoryEntry dirEntries[MAXNUMSOFDIRS];
DirectoryEntry dirEntries1[MAXNUMSOFDIRS];
//track dir entries
uint32_t numOfDirsRAM=0;
uint32_t numOfDirs1RAM=0;

//make file entries only a max of 500 files could be created
FileEntry fileEntries[MAXNUMSOFFILES];
//track file entries
uint32_t numOfFilesRAM=0;

//system
System_P memory;
System_P memEnd;

//free entries arrays
uint32_t freeEntriesFile[MAXNUMSOFFILES];
uint32_t freeEntriesDir[MAXNUMSOFDIRS];

//track LBA position
uint32_t LBApos=1;

//methods

void freeMemory();

void initializeFileSystem(uint64_t);

void initializeFiles(uint64_t);

void initializeDirectories(uint64_t);

void initializeFree(uint64_t);

void closingFileSystem(uint64_t);

int findStoringPos(uint32_t,uint64_t,uint32_t);

void writingFiles(uint64_t);

void writingDir(uint64_t);

void writingFree(uint64_t);










	










	




