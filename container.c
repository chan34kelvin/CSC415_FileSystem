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
	DirectoryEntry arr[10000];
	struct FileSystemInfo info; 
}container1,* containerP;
int main(){
	container1 C1;
	print(&C1);
	return 0;
}
void add(DirectoryEntryP* file){
	
}
/*void move(char *,int);
void remove(char *,int);
int contain(char *,int);*/
//container
void print(container1* C1){
	printf("%d",C1->size);
}
