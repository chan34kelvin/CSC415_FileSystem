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
typedef struct Container{
	int size;
	DirectoryEntryP arr[10000];
	struct FileSystemInfo info; 
}Container,* containerP;
int main(){
	/*Container C1;
	DirectoryEntry entry1;
	DirectoryEntry entry2;
	char name[128]="brian";
	entry1.fileName= name;
	entry2.fileName= "oooo";
	add(&C1,&entry1);
	printf("from filename1: %s\n",C1.arr[0]->fileName);
	add(&C1,&entry2);
	printf("from filename2: %s\n",C1.arr[1]->fileName);
	delete(&C1,0);
	delete(&C1,1);
	printAll(&C1);*/
	//create a container and invoke initialize for filesysteminfo or a function call to initialize the info and set all values to default
	//when user access, they can just add to the switch
	do{
		//create move delete terminate
		int userChoice;
		switch(userChoice){
			case 1: //function
				//create file
			break;
			case 2:
				//move file
			break;
			case 3:
				//delete file
			break;
			case 4:
				//terminate main return 0
			break;
			default:
				//print all
		}
	}while(1);
	return 0;
}
void add(Container* container,DirectoryEntryP file){
	container->arr[container->size]= file;
	printf("from add method filename position[%d]: %s\n",container->size,container->arr[container->size]->fileName);
	container->size+=1;
}
void delete(Container *container,int position){
	printf("from delete method filename position[%d]: %s\n",position,container->arr[position]->fileName);
	container->arr[position]=0;
	container->size-=1;
	printf("size of container:%d\n",container->size);
}
void printAll(Container* container){
	for(int i=0;i<container->size;i+=1)
		printf("from printAll method: %s\n",container->arr[i]->fileName);
}
/*void move(char *,int);
void remove(char *,int);
int contain(char *,int);*/
//container
void print(Container* C1){
	printf("%d",C1->size);
}
