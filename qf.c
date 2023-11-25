#include <stdio.h>
#include "config.h"

#define MAX 15

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
        printf(" ");
        printf("%s",LABELS[i]);
        printf(TEXT_COLOR);
        printf("%s",data[i]);
        printf("\n");
    }

    return 0;
}
