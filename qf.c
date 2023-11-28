#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <sys/utsname.h>
#include "config.h"

int main(){
    char data[LOGO_HEIGHT][MAX];
    for(us i=0; i<LOGO_HEIGHT; i++)
        sprintf(data[i]," ");

    FILE *fptr;
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
        ui uptime=atoi(data[1]);
        uptime=uptime/60;
        if(uptime<60){
            sprintf(data[1],"%u",uptime);
            strcat(data[1]," mins");
        }
        else{
            ui hours=uptime/60;
            ui mins=uptime-hours*60;
            sprintf(data[1],"%u",hours);
            strcat(data[1]," hours ");
            char mins_string[3];
            sprintf(mins_string,"%u",mins);
            strcat(data[1],mins_string);
            strcat(data[1]," mins");
        }
            
        fclose(fptr);
    }

    //cpu temp
    fptr=fopen(CPU_TEMP,"r");
    if(fptr==NULL)
        strcpy(data[2],"ERROR");
    else{
        fgets(data[2], MAX, fptr);
        int temp=atoi(data[2]);
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
    ul disk_total=buffer_statvfs.f_blocks*buffer_statvfs.f_bsize;
    ul disk_available=buffer_statvfs.f_bavail*buffer_statvfs.f_frsize;
    sprintf(data[4],"%lu",100*(disk_total-disk_available)/disk_total);
    strcat(data[4],"% used");   

    //battery
    fptr=fopen(BATTERY,"r");
    if(fptr==NULL)
        strcpy(data[5],"ERROR");
    else{
        fgets(data[5],MAX,fptr); 
        fclose(fptr);
        for(us i=0; i<MAX; i++){
            if(data[5][i]=='\n'){
                data[5][i]='%';
                break;
            }
        }
    }

    //quickfetch version
    strcpy(data[6],VERSION);

    for(us i=0; i<LOGO_HEIGHT; i++){
        //print logo
        printf(LOGO_COLOR"%s", LOGO[i]);
        
        //print data
        printf(" %s",LABELS[i]);
        printf(TEXT_COLOR);
        printf("%s\n",data[i]);
    }

    return 0;
}
