#include <stdio.h>
#include <string.h>
#include "config.h"

int main(){
    //get data
    char data[HEIGHT][MAX];
    for(unsigned short i=0; i<HEIGHT; i++)
        sprintf(data[i], "ERROR");

    FILE *fptr;
    fptr=fopen(BATTERY,"r");
    fgets(data[6],MAX,fptr); 

    //print ascii logo and data
    for(unsigned short i=0; i<HEIGHT; i++){
        //logo
        printf(ASCII_COLOR"%s", ASCII[i]);
        
        //data
        printf(" %s",LABELS[i]);
        printf(TEXT_COLOR);
        printf("%s\n",data[i]);
    }

    return 0;
}
