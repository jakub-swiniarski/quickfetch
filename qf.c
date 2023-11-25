#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

int main(){
    //get data
    char data[HEIGHT][MAX];
    for(unsigned short i=0; i<HEIGHT; i++)
        sprintf(data[i], "ERROR");

    FILE *fptr;

    //uptime


    //cpu temp
    fptr=fopen(CPU_TEMP,"r");
    fgets(data[2], MAX, fptr);
    int temp=atof(data[2]);
    sprintf(data[2],"%d",temp/1000);
    fclose(fptr);

    //battery
    fptr=fopen(BATTERY,"r");
    fgets(data[6],MAX,fptr); 
    fclose(fptr);

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
