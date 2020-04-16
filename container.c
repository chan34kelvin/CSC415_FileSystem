#include "Container.h"
#include "FileSystemInfo.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <math.h>
#define CONTAINERSIZE 512;
#define FILESIZE 500000000;
#define DIRECTORYENTRYSIZE 500000000;
#define WL_BLOCK 2500;
typedef struct Container{
	int size;
	DirectoryEntry arr[10000];
	struct FileSystemInfo info; 
}Container,* ContainerP;

volatile DirectoryEntryP dir=  NULL;
volatile int dirCount= 0;
int maxDirCount=0;

int freeIndex[10000];
int freeArrSize;

void creatingFile();
int main(int argc,char *argv[]){
	Container C1;

	int userChoice;

	printf("Initializing file system\n");
	initializeFileSystem(&C1);
	printFileSystemInfo(&C1);

	printf("Welcome to our file system\n");
	printf("Press 1 for terminating the file system\n Press 2 to create a file\n User Choice: ");
	scanf("%d",&userChoice);

	do{
		switch(userChoice){
			case 1:
				printf("Terminating file system, BYE!\n");
				return 0;
			case 2:
				printf("Creating a file....\n");
				creatingFile();
				add(&C1);
				break;
			case 3: 
				printf("Deleting a file....\n");
				del(&C1);
				break;
			case 4:
				break;
			case 5:
				break;
			default:
				printf("Now printing every directoryEntry in the file system..\n");
				printAll(&C1);
		}
			printf("\nPress 1 for terminating the file system\n Press 2 to create a file\n Press 3 to delete the file\n Press 4 to move a file\n Press any number for printing file system\n User Choice: ");
			scanf("%d",&userChoice);
	}while(1);

	return 0;
}
void creatingFile(){
	if(dirCount>=maxDirCount){
		maxDirCount+=WL_BLOCK;
	}
	if(dir==NULL){
		dir=malloc(sizeof(DirectoryEntry)*maxDirCount);
	}else{
		DirectoryEntryP reallocD= realloc(dir, sizeof(DirectoryEntry)*maxDirCount);
		dir=reallocD;
	}
	printf("size: %ld\n",dir[dirCount].size);
}
void add(ContainerP C1){
	char input[128];

	int addInd= C1->size;
	if(freeArrSize>0){
		printf("%d\n",freeIndex[freeArrSize]);
		addInd=freeIndex[freeArrSize];
		freeArrSize-=1;
	}
	if(addInd!=C1->size){
		C1->arr[C1->size]=dir[dirCount];
	}

	printf("Enter the name for this new file :");
	scanf("%s",input);
	if(!(dirCount==0||C1->size==0)){
		int check=findFilePos(C1,input);
		if(check>=0){
			char temp[10];
			C1->arr[check].repeat+=1;
			int repeat= C1->arr[check].repeat;
			strcat(input,"_");
			sprintf(temp,"%d",repeat);
			strcat(input,temp);
		}
	}

	C1->arr[addInd].fileName= strdup(input);

	printf("The filename entered: %s\n", C1->arr[addInd].fileName);

	dirCount+=1;
	if(addInd==C1->size){
		C1->size+=1;
	}
}

void del(ContainerP C1){
	char input[128];
	char *cmp;

	printf("Enter the name of the file :");
	scanf("%s",input);
	cmp= input;

	//check where the file is
	
	for(int i=0;i<C1->size;i++){
		int res=-10000;
		res= strcmp(cmp,C1->arr[i].fileName);
		if(res==0){
			freeIndex[freeArrSize++]=i;
			C1->arr[i].fileName="";
			printf("File deleted successfully\n");
			return;
		}
	}
	
	printf("Sorry, file Not Found\n");
}
	
int findFilePos(ContainerP C1,char *input){
	for(int i=0;i<C1->size;i++){
		if(strcmp(C1->arr[i].fileName,input)==0){
			printf("File already existed\n");
			return i;
		}
	}
	return -1;
}
			
void printAll(ContainerP C1){
	for(int i=0;i<C1->size;i++){
		if(strcmp(C1->arr[i].fileName,"")!=0){
			printf("Container C1 -> arr[%d]'s filename is %s\n",i,C1->arr[i].fileName);
		}
	}
}	 	
void printFileSystemInfo(ContainerP container){
	printf("%ld\n",container->info.space);
	printf("%ld\n",container->info.freeSpace);
	printf("%ld\n",container->info.usedSpace);
	printf("%s\n",container->info.name);
}
	
void initializeFileSystem(ContainerP container){
	long int fileSize= FILESIZE;
	container->info.space= fileSize;
	container->info.freeSpace= 0;
	container->info.usedSpace= 0;
	container->info.name="C Drive";
}
