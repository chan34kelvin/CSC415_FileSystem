


typedef struct FileSystemInfo {
	long space; //how much total space we initial start
	long freeSpace; //how much space we have. Do we have to communicate between FreeSpace? 
	long usedSpace; //how much space we have used
	char name[128]; 
	char id[128];
	char type[128];

	struct files; 

} FileSystemInfo;

typedef struct DirectoryEntry {
	long ID; //id of the file/number
	long size; //size of the file
	long startBlock;
	char fileName[128]; //filename
	char fileType[128]; //ext of the file
	char date[128]; //time stamp of the file creation
	int userAccess; //access of the file or directory general user lvl
	int adminAccess; //access of the file or directory admin lvl
	int read; 
	int write;

} DirectoryEntry, *DirectoryEntryP;

typedef struct FreeSpace {
	long long sig1; 
	long long sig2;
	int countFreeBlocks; //could we get the number of free spaces from the vector? 

} FreeSpace;



