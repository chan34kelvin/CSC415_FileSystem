#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "fsLow.h"

void copyDir(char *parent, char *name){
    char userInput[100];
    char userInputCpyVer[100];

    /*checking if theres too many directories*/
    int subIndex = overflowDirectories();

    if(subIndex = -1) {
        printf("There are too many directories in order to copy.");
        return;
    }


    int index = checkDirectoryCanCreate();

    if(index==-1){
        printf("Unable to make directory\n");
        return;
    }

    /*Checking if theres something to copy*/
    if(numOfDirsRAM<2 || numOfFilesRAM==0){
        print("Nothing can be copied.\n")
    }

    /*Checking if there is an input to be copied*/
    if(strlen(name)<1)||strlen(name)>49{
        printf("Enter the name of which to copy: \n");
        scanf("%s",userInput);
    } else{
        strcpy(userInput,name);
    }

    if(strlen(userInput)>49){
        printf("The input is too long\n");
        return;
    }

    /*Creating and checking copy name*/
    printf("What is the copy's name?: \n");

    if(strlen(name)<1)||strlen(name)>49{
        printf("Enter the name of which to copy: \n");
        scanf("%s",userInput);
    } else{
        strcpy(userInputCpyVer,name);
    }

    if(strlen(userInputCpyVer)>49){
        printf("The input is too long\n");
        return;
    }

    if(containsName(userInput,2)>0){
        printf("\nThis name already exists in current directory.\n");
        return;
    }

    if(strcmp(userInput,userInputCpyVer)==0){
        printf("\nYou cannot use the same name as original version. Please try again.\n");
        return;
    }


}