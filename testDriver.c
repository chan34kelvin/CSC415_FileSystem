#include "FileSystemInfo.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    uint32_t dirCount;
    DirectoryEntry_P name[10000];

/*Tried setting up directory names to test*/
    dirCount += 1;
    DirectoryEntry C;
    C.dirName[MAXDIRNAMEBYTES] = "C";
    C.id = dirCount;
    printf("%d", C.id);
    DirectoryEntry D;
    D.dirName[MAXDIRNAMEBYTES] = "D";
    dirCount +=1;
    D.id = dirCount;
	return 0;
}

/*Function Definitions*/

void addDirectory(DirectoryEntry testDir, uint32_t dirCount){
    char input[128]; //users input

    /*Do a check on if there is any more space to create a new file*/
    if(dirCount != MAXNUMSOFDIRS){
        printf("Sorry, theres no space for another directory.");
        return;
    }

    printf("What is the name of this subdirectory? ");

    /*Keep user applying new names until name isnt taken*/
    while (!(testDir.dirName == input)){
            scanf("%s", input);
            printf("Name has already been used. Please try again.");
    }

    dirCount += 1; //gets incremented, and becomes the id for the added Directory
    /*Create a New Directory with the new name*/
    
    dirCount += 1; //directory count increases and get used as an id
    testDir.id = dirCount;

    
}
