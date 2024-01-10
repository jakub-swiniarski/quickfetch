#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <sys/utsname.h>
#include <time.h>
#include "config.h"

int main(){
    char data[ROWS_MAX][DATA_LENGTH];
    FILE *fptr;

    //kernel
    struct utsname buffer_utsname;
    if(uname(&buffer_utsname)!=0)
        strcpy(data[0],"ERROR");
    else
        strcpy(data[0],buffer_utsname.release);

    //time
    time_t now=time(NULL);
    struct tm *now_tm=localtime(&now);
	sprintf(data[1],"%02d:%02d",now_tm->tm_hour,now_tm->tm_min);

    //uptime
    fptr=fopen(UPTIME,"r");
    if(fptr==NULL)
        strcpy(data[2],"ERROR");
    else{
        char ch;
        strcpy(data[2]," ");
        while((ch=fgetc(fptr))!=' ')
            strncat(data[2],&ch,1);
        int uptime=atoi(data[2]);
        uptime=uptime/60;
        if(uptime<60){
            sprintf(data[2],"%d",uptime);
            strcat(data[2]," min");
        }
        else{
            int hours=uptime/60;
            int mins=uptime-hours*60;
            sprintf(data[2],"%d",hours);
            strcat(data[2]," h ");
            char mins_string[12];
            sprintf(mins_string,"%d",mins);
            strcat(data[2],mins_string);
            strcat(data[2]," min");
        }
        fclose(fptr);
    }

    //cpu temp
    fptr=fopen(CPU_TEMP,"r");
    if(fptr==NULL)
        strcpy(data[3],"ERROR");
    else{
        fgets(data[3], DATA_LENGTH, fptr);
        int temp=atoi(data[3]);
        sprintf(data[3],"%d",temp/1000);
        fclose(fptr);
        strcat(data[3]," °C");
    }

    //memory
    fptr=fopen(MEMORY,"r");
    if(fptr==NULL)
        strcpy(data[4],"ERROR");
    else{
        int mem_total, mem_free, mem_available, mem_used; 
        fscanf(fptr,"MemTotal: %d kB MemFree: %d kB MemAvailable: %d kB",&mem_total,&mem_free,&mem_available); 
        fclose(fptr); 
        mem_used=mem_total-mem_available;
        char percentage_used[4];
        sprintf(percentage_used,"%d",100*mem_used/mem_total);
        mem_used=mem_used/1024;
        if(mem_used>1024){
            sprintf(data[4],"%.2f",(float)mem_used/1024);
            strcat(data[4]," GiB used ("); 
        } 
        else{
            sprintf(data[4],"%d",mem_used);
            strcat(data[4]," MiB used ("); 
        }
        strcat(data[4],percentage_used);
        strcat(data[4], "%)");
    }

    //disk
    struct statvfs buffer_statvfs;
    if(statvfs(DISK,&buffer_statvfs)!=0)
        strcpy(data[5],"ERROR");
    else{
        long long disk_total=buffer_statvfs.f_blocks*buffer_statvfs.f_bsize;
        long long disk_free=buffer_statvfs.f_bfree*buffer_statvfs.f_frsize;
        long long disk_used=disk_total-disk_free;
        char percentage_used[4];
        sprintf(percentage_used,"%lld",100*disk_used/disk_total);
        sprintf(data[5],"%lld",disk_used/(1024*1024*1024));
        strcat(data[5]," GiB used (");
        strcat(data[5],percentage_used);
        strcat(data[5],"%)");
    }

    //battery
    fptr=fopen(BATTERY,"r");
    if(fptr==NULL)
        strcpy(data[6],"ERROR");
    else{
        fgets(data[6],DATA_LENGTH,fptr); 
        fclose(fptr);
        for(int i=0; i<DATA_LENGTH; i++){
            if(data[6][i]=='\n'){
                data[6][i]='%';
                break;
            }
        }
    }

    for(int i=0; i<ROWS_MAX; i++){
        //print logo
        printf(LOGO_COLOR"%s", LOGO[i]);
        
        //print data
        printf("%s",LABELS[i]);
        printf(TEXT_COLOR"%s\n",data[i]);
    }

    return 0;
}
