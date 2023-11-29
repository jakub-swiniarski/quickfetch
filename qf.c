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
            strcat(data[1]," min");
        }
        else{
            ui hours=uptime/60;
            ui mins=uptime-hours*60;
            sprintf(data[1],"%u",hours);
            strcat(data[1]," h ");
            char mins_string[3];
            sprintf(mins_string,"%u",mins);
            strcat(data[1],mins_string);
            strcat(data[1]," min");
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
        ui mem_total, mem_free, mem_available, mem_used; 
        fscanf(fptr,"MemTotal: %u kB MemFree: %u kB MemAvailable: %u kB",&mem_total,&mem_free,&mem_available); 
        fclose(fptr); 
        mem_used=mem_total-mem_available;
        char percentage_used[4];
        sprintf(percentage_used,"%u",100*mem_used/mem_total);
        mem_used=mem_used/1024;
        if(mem_used>1024){
            sprintf(data[3],"%.2f",(float)mem_used/1024);
            strcat(data[3]," GiB used ("); 
        } 
        else{
            sprintf(data[3],"%u",mem_used);
            strcat(data[3]," MiB used ("); 
        }
        strcat(data[3],percentage_used);
        strcat(data[3], "%)");
    }

    //disk
    struct statvfs buffer_statvfs;
    if(statvfs(DISK,&buffer_statvfs)!=0)
        strcpy(data[4],"ERROR");
    else{
        ul disk_total=buffer_statvfs.f_blocks*buffer_statvfs.f_bsize;
        ul disk_free=buffer_statvfs.f_bfree*buffer_statvfs.f_frsize;
        ul disk_used=disk_total-disk_free;
        char percentage_used[4];
        sprintf(percentage_used,"%lu",100*disk_used/disk_total);
        sprintf(data[4],"%lu",disk_used/(1024*1024*1024));
        strcat(data[4]," GiB used (");
        strcat(data[4],percentage_used);
        strcat(data[4],"%)");
    }

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
