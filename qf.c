#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <sys/utsname.h>
#include "config.h"

int main(){
    char data[LOGO_HEIGHT][MAX];
    for(unsigned short i=0; i<LOGO_HEIGHT; i++)
        sprintf(data[i]," ");

    FILE *fptr;
    int temp; //temporary
    char ch;

    //kernel
    struct utsname buffer_utsname;
    if(uname(&buffer_utsname)!=0)
        strcpy(data[0],"ERROR");
    else
        strcpy(data[0],buffer_utsname.release);

    //uptime
    fptr=fopen(UPTIME,"r");
    if(fptr==NULL)
        strcpy(data[1],"ERROR");
    else{
        while((ch=fgetc(fptr))!=' ')
            strncat(data[1],&ch,1);
        temp=atoi(data[1]);
        sprintf(data[1],"%d",temp/60);
        fclose(fptr);
        strcat(data[1]," mins");
    }

    //cpu temp
    fptr=fopen(CPU_TEMP,"r");
    if(fptr==NULL)
        strcpy(data[2],"ERROR");
    else{
        fgets(data[2], MAX, fptr);
        temp=atoi(data[2]);
        sprintf(data[2],"%d",temp/1000);
        fclose(fptr);
        strcat(data[2]," °C");
    }

    //memory
    fptr=fopen(MEMORY,"r");
    if(fptr==NULL)
        strcpy(data[3],"ERROR");
    else{
        int mem_total, mem_free, mem_available; 
        fscanf(fptr,"MemTotal: %d kB MemFree: %d kB MemAvailable: %d kB",&mem_total,&mem_free,&mem_available); 
        sprintf(data[3],"%d",100*(mem_total-mem_available)/mem_total);
        fclose(fptr);
        strcat(data[3],"% used");
    }

    //disk
    struct statvfs buffer_statvfs;
    statvfs(DISK,&buffer_statvfs); //check if no error (TODO)
    unsigned long disk_total=buffer_statvfs.f_blocks*buffer_statvfs.f_bsize;
    unsigned long disk_available=buffer_statvfs.f_bavail*buffer_statvfs.f_frsize;
    sprintf(data[4],"%lu",100*(disk_total-disk_available)/disk_total);
    strcat(data[4],"% used");   

    //battery
    fptr=fopen(BATTERY,"r");
    if(fptr==NULL)
        strcpy(data[5],"ERROR");
    else{
        fgets(data[5],MAX,fptr); 
        fclose(fptr);
        for(unsigned short i=0; i<MAX; i++){
            if(data[5][i]=='\n'){
                data[5][i]='%';
                break;
            }
        }
    }

    //quickfetch version
    strcpy(data[6],VERSION);

    for(unsigned short i=0; i<LOGO_HEIGHT; i++){
        //print logo
        printf(LOGO_COLOR"%s", LOGO[i]);
        
        //print data
        printf(" %s",LABELS[i]);
        printf(TEXT_COLOR);
        printf("%s\n",data[i]);
    }

    return 0;
}
