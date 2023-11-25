#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include "config.h"

int main(){
    char data[HEIGHT][MAX];
    for(unsigned short i=0; i<HEIGHT; i++)
        sprintf(data[i]," ");

    FILE *fptr;
    int temp; //temporary
    char ch;

    //kernel
    struct utsname buffer;
    if(uname(&buffer)!=0){
        perror("uname");
        exit(EXIT_FAILURE);
    }
    strcpy(data[0],buffer.release);

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

    //memory
    int mem_total, mem_free, mem_available;
    fptr=fopen(MEMORY,"r");
    fscanf(fptr,"MemTotal: %d kB MemFree: %d kB MemAvailable: %d kB",&mem_total,&mem_free,&mem_available); 
    sprintf(data[3],"%d",100*(mem_total-mem_available)/mem_total);
    fclose(fptr);
    strcat(data[3],"% used");

    //battery
    fptr=fopen(BATTERY,"r");
    fgets(data[5],MAX,fptr); 
    fclose(fptr);
    for(unsigned short i=0; i<MAX; i++){
        if(data[5][i]=='\n'){
            data[5][i]='%';
            break;
        }
    }

    //quickfetch version
    strcpy(data[6],VERSION);

    for(unsigned short i=0; i<HEIGHT; i++){
        //print logo
        printf(ASCII_COLOR"%s", ASCII[i]);
        
        //print data
        printf(" %s",LABELS[i]);
        printf(TEXT_COLOR);
        printf("%s\n",data[i]);
    }

    return 0;
}
