#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "fsLow.h"

//copy
void cpFunction( char *name, char *name1){
	
	//check
	char userInput[100];
	char userInput1[100];

	if(strlen(name)<1||strlen(name)>49){
		scanf("%s",userInput);
	}else{
		strcpy(userInput,name);
	}

	if(strlen(name1)<1||strlen(name1)>49){
		scanf("%s",userInput1);
	}else{
		strcpy(userInput1,name1);
	}

	//check if the file exist
	
	if(containsName(userInput,3)==-1){
		printf("\nThis name either isn't a file or doesn't exist in the current directory\n");
		return;
	}

	if(containsName(userInput1,2)==-1){
		printf("\nThis name doesn't exist in the current directory\n");
		return;
	}	

	//
	int fileIndex=-1;
	//check files
	int retVal=0;
	retVal= containsName(userInput,3);
	if(retVal==-1){
		printf("copy function failed\n");
		return;
	}

	fileIndex= retVal;

	//
	int retVal1= containsName(userInput1, 1);
	int directoryIndex1= retVal1;
	int fileIndex1=-1;

	if(retVal1==-1){

		//check files
		retVal1= containsName(userInput1,3);
		if(retVal1==-1){
			printf("copy function failed\n");
			return;
		}

		fileIndex1= retVal1;

	}

	if(fileIndex>-1 &&fileIndex1==-1){
		currentDir(userInput1);
		int ret1= creatingFile(fileEntries[fileIndex].fileName, fileEntries[fileIndex].content, 2);
		if(ret1==-1){
			printf("copy function failed\n");
		}
		currentDir("..");
		return;
	}else{
		strcpy(fileEntries[fileIndex1].content,strdup(fileEntries[fileIndex].content));
		return;
	}

	printf("copy function failed\n");
	return;
}

//move
void moveFunction( char *name, char *name1){
	
	//check
	char userInput2[100];
	char userInput3[100];

	if(strlen(name)<1||strlen(name)>49){
		scanf("%s",userInput2);
	}else{
		strcpy(userInput2,name);
	}

	if(strlen(name1)<1||strlen(name1)>49){
		scanf("%s",userInput3);
	}else{
		strcpy(userInput3,name1);
	}

	//check if the file exist
	
	if(containsName(userInput2,2)==-1){
		printf("\nThis name doesn't exist in the current directory\n");
		return;
	}

	if(containsName(userInput3,2)==-1){
		printf("\nThis name doesn't exist in the current directory\n");
		return;
	}	

	//
	int retVal= containsName(userInput2, 1);
	int directoryIndex= retVal;
	int fileIndex=-1;

	if(retVal==-1){

		//check files
		retVal= containsName(userInput2,3);
		if(retVal==-1){
			return;
		}

		fileIndex= retVal;

	}

	//
	int retVal1= containsName(userInput3, 1);
	int directoryIndex1= retVal1;
	int fileIndex1=-1;

	if(retVal1==-1){

		//check files
		retVal1= containsName(userInput3,3);
		if(retVal1==-1){
			return;
		}

		fileIndex1= retVal1;

	}

	if(fileIndex==-1&&fileIndex1==-1){
		char arg1[100];
		currentDir(userInput3);
		int ret= containsName(dirEntries[directoryIndex].dirName,2);
		if(ret>0){
			printf("a similar name file already exist, move function failed\n");
			return;
		}
		int subIndex= overflowDirectories();
		if(subIndex==-1){
			printf("move function failed\n");
			return;
		}
		dirEntries[cdLoc].subDirs[subIndex]= strdup(userInput2);
		strcpy(dirEntries[directoryIndex].parentDir, strdup(userInput3));
		dirEntries[directoryIndex].id= cdLoc;
		currentDir("..");
		for(int i=0;i<MAXNUMOFSUBDIRS;i++){
			char *temp3= dirEntries[cdLoc].subDirs[i];
			if(temp3!=NULL&&strcmp(temp3,userInput2)==0){
				dirEntries[cdLoc].subDirs[i]=strdup(" ");
				return;
			}
		}
		printf("Error cleaning up...\n");
		return;
	}else if(fileIndex>-1 &&fileIndex1==-1){
		currentDir(userInput3);
		int ret1= creatingFile(fileEntries[fileIndex].fileName, fileEntries[fileIndex].content, 2);
		if(ret1==-1){
			printf("move function failed\n");
			return;
		}
		currentDir("..");
		deletingDir(userInput2);
		return;
	}else{
		if(strcmp(userInput2,userInput3)==0){
			strcpy(fileEntries[fileIndex1].content, strdup(fileEntries[fileIndex].content));
			strcpy(fileEntries[fileIndex1].fileName,strdup(fileEntries[fileIndex].fileName));
			deletingDir(userInput2);
		}else{
			strcpy(fileEntries[fileIndex].fileName, strdup(userInput3));
		}
		return;
	}

	printf("move function failed\n");
	return;
}
		
void listDir(){

	if(numOfFilesRAM==0||numOfDirsRAM==0){
		return;
	}

  	for(uint32_t i=0;i<MAXNUMOFSUBDIRS;i++){
		char *userInput2;
		userInput2=dirEntries[cdLoc].subDirs[i];
		if(userInput2!=NULL&&strcmp(userInput2,"")!=0&&strcmp(userInput2," ")!=0){
			int retVal= containsName(userInput2, 1);
			printf("Folder %d: %s date:%d \n",i+1,dirEntries[retVal].dirName,dirEntries[retVal].date);
				//printf("Folder %d: %s\n",i,dirEntries[retVal].dirName);
		}
    	}
	for(uint32_t i=0;i<MAXNUMOFSUBFILES;i++){
		char *userInput3;
		userInput3=dirEntries[cdLoc].subFiles[i];
		if(userInput3!=NULL&&strcmp(userInput3,"")!=0&&strcmp(userInput3," ")!=0){
			int retVal1= containsName(userInput3, 3);
			printf("File %d: %s date:%d \n",i+1,fileEntries[retVal1].fileName,fileEntries[retVal1].date);
				//printf("File %d: %s\n",i,fileEntries[retVal1].fileName);
		}
	}
}

void changeMetaData(char *name){

	//check
	char userInput1[100];

	if(strlen(name)<1||strlen(name)>49){
		scanf("%s",userInput1);
	}else{
		strcpy(userInput1,name);
	}

	//check if the file exist
	
	if(containsName(userInput1,2)==-1){
		printf("\nThis name doesn't exist in the current directory\n");
		return;
	}

	int retVal1= containsName(userInput1, 1);
	int directoryIndex1= retVal1;
	int fileIndex1=-1;

	if(retVal1==-1){

		//check files
		retVal1= containsName(userInput1,3);
		if(retVal1==-1){
			printf("copy function failed\n");
			return;
		}

		fileIndex1= retVal1;

	}

	if(fileIndex1==-1){
		//You're now changing a directory's name
		char userInput[100];
		printf("Please type the name you want to change to: ");
		scanf("%s",userInput);
		if(strlen(userInput)>50){
			printf("Sorry, the name you typed is too long\n");
			return;
		}
		int ret= containsName(userInput, 2);
		if(ret==-1){
			currentDir(dirEntries[directoryIndex1].dirName);
			printf("test1: %d\n", cdLoc);
			for(int i=0;i<MAXNUMOFSUBDIRS;i++){
				if(dirEntries[cdLoc].subDirs[i]!=NULL){
					int ret= containsName(dirEntries[cdLoc].subDirs[i],2);
					if(ret>0){
						strcpy(dirEntries[ret].parentDir, strdup(userInput));
					}
				}
			}
			currentDir("..");
			char *temp= strdup(dirEntries[directoryIndex1].dirName);
			strcpy(dirEntries[directoryIndex1].dirName,strdup(userInput));
			printf("test: %d\n", cdLoc);
			for(int i=0;i<MAXNUMOFSUBDIRS;i++){
				if(dirEntries[cdLoc].subDirs[i]!=NULL&&strcmp(dirEntries[cdLoc].subDirs[i],temp)==0){
					dirEntries[cdLoc].subDirs[i]=strdup(userInput);
				}
			}
			//currentDir(userInput);		
			printf("Your new directory name: %s\n",userInput);
		}else{
			printf("This name already existed\n");
		}
		dirEntries[directoryIndex1].date= 30000+numOfDirsRAM;
	}else{
		char userInput1[100];
		printf("Please choose a type you want to change, name or content: ");
		scanf("%s",userInput1);
		if(strcmp(userInput1,"name")==0){
			printf("Enter the name you wanted to change to: ");
			char * temp2= strdup(fileEntries[fileIndex1].fileName);
			scanf("%s",userInput1);
			for(int i=0;i<MAXNUMOFSUBFILES;i++){
				if(dirEntries[cdLoc].subFiles[i]!=NULL&&strcmp(dirEntries[cdLoc].subFiles[i],temp2)==0){
					dirEntries[cdLoc].subFiles[i]=strdup(userInput1);
				}
			}
			strcpy(fileEntries[fileIndex1].fileName, strdup(userInput1));
			fileEntries[fileIndex1].date= 40000+ numOfFilesRAM;
			printf("Your new file name: %s\n", fileEntries[fileIndex1].fileName);
			return;
		}else{
			printf("Enter the content you want to change to: ");
			char content[MAXCONTENTBYTES];
			fgetc(stdin);
			fgets(content,MAXCONTENTBYTES,stdin);
			if(strlen(content)>500){
				printf("content is too big\n");
				return;
			}
			strcpy(fileEntries[fileIndex1].content,strdup(content));
			printf("content successfully changed\n");
			return;
		}
			
		
	}
}
























