#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

int main(){
    //get data
    char data[HEIGHT][MAX];
    for(unsigned short i=0; i<HEIGHT; i++)
        sprintf(data[i]," ");

    FILE *fptr;
    int temp; //temporary
    char ch;

    //uptime
    fptr=fopen(UPTIME,"r");
    while((ch=fgetc(fptr))!=' ')
        strncat(data[1],&ch,1);
    temp=atoi(data[1]);
    sprintf(data[1],"%d",temp/60);
    fclose(fptr);
    strcat(data[1]," mins");

    //cpu temp
    fptr=fopen(CPU_TEMP,"r");
    fgets(data[2], MAX, fptr);
    temp=atoi(data[2]);
    sprintf(data[2],"%d",temp/1000);
    fclose(fptr);
    strcat(data[2]," °C");

    //battery
    fptr=fopen(BATTERY,"r");
    fgets(data[6],MAX,fptr); 
    fclose(fptr);
    for(unsigned short i=0; i<MAX; i++){
        if(data[6][i]=='\n'){
            data[6][i]='%';
            break;
        }
    }

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
