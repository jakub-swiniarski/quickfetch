#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <sys/utsname.h>
#include <time.h>

#include "config.h"

/* function declarations */
static void get_all(void);
static void get_battery(void);
static void get_disk(void);
static void get_kernel(void);
static void get_memory(void);
static void print_all(void);
static void get_temp(void);
static void get_time(void);
static void get_uptime(void);

/* variables */
static char data[N_ROWS][DATA_LENGTH];

/* function implementations */
void get_all(void) {
    get_kernel();
    get_time();
    get_uptime();
    get_temp();
    get_memory();
    get_disk();
    get_battery();
}

void get_battery(void) {
    FILE *fptr = fopen(BATTERY,"r");
    if (fptr == NULL)
        strcpy(data[6], "ERROR");
    else {
        fgets(data[6], DATA_LENGTH, fptr); 
        fclose(fptr);
        for(int i = 0; i < DATA_LENGTH; i++){
            if(data[6][i] == '\n'){
                data[6][i] = '%';
                break;
            }
        }
    }
}

void get_disk(void) {
    struct statvfs buffer_statvfs;
    if (statvfs(DISK, &buffer_statvfs) != 0)
        strcpy(data[5], "ERROR");
    else {
        long long disk_total = buffer_statvfs.f_blocks * buffer_statvfs.f_bsize;
        long long disk_free = buffer_statvfs.f_bfree * buffer_statvfs.f_frsize;
        long long disk_used = disk_total - disk_free;
        int disk_used_gib = disk_used / (1024*1024*1024);
        int percentage_used = 100 * disk_used / disk_total;
        sprintf(data[5], "%d GiB used (%d%%)", disk_used_gib, percentage_used);
    }
}

void get_kernel(void) {
    struct utsname buffer_utsname;
    if (uname(&buffer_utsname) != 0)
        strcpy(data[0], "ERROR");
    else
        strcpy(data[0], buffer_utsname.release);
}

void get_memory(void) {
    FILE *fptr = fopen(MEMORY, "r");
    if (fptr == NULL)
        strcpy(data[4], "ERROR");
    else {
        int mem_total, mem_free, mem_available, mem_used; 
        fscanf(fptr, "MemTotal: %d kB MemFree: %d kB MemAvailable: %d kB", &mem_total, &mem_free, &mem_available); 
        fclose(fptr); 
        mem_used = mem_total - mem_available;
        int percentage_used = 100 * mem_used / mem_total;
        mem_used = mem_used / 1024;
        if (mem_used > 1024)
            sprintf(data[4], "%.2f GiB used (%u%%)", (float)mem_used / 1024, percentage_used);
        else
            sprintf(data[4], "%u MiB used (%u%%)", mem_used, percentage_used);
    }

}

void print_all(void) {
    for(int i = 0; i < N_ROWS; i++){
        printf(LOGO_COLOR"%s", LOGO[i]);

        printf("%s", LABELS[i]);
        printf(TEXT_COLOR"%s\n", data[i]);
    }
}

void get_temp(void) {
    FILE *fptr = fopen(CPU_TEMP, "r");
    if (fptr == NULL)
        strcpy(data[3], "ERROR");
    else {
        fgets(data[3], DATA_LENGTH, fptr);
        int temp = atoi(data[3]);
        sprintf(data[3], "%d °C", temp/1000);
        fclose(fptr);
    }
}

void get_time(void) {
    time_t now = time(NULL);
    struct tm *now_tm = localtime(&now);
	sprintf(data[1], "%02d:%02d", now_tm->tm_hour, now_tm->tm_min);
}

void get_uptime(void) {
    FILE *fptr = fopen(UPTIME, "r");
    if(fptr == NULL)
        strcpy(data[2], "ERROR");
    else {
        char ch;
        strcpy(data[2], " ");
        while ((ch = fgetc(fptr)) != ' ')
            strncat(data[2], &ch, 1);
        int uptime = atoi(data[2]);
        uptime = uptime / 60;
        if (uptime < 60)
            sprintf(data[2], "%u min", uptime);
        else {
            int hours = uptime / 60;
            int mins = uptime - hours * 60;
            sprintf(data[2], "%u h %u min", hours, mins);
        }
        fclose(fptr);
    }
}

int main(void) {
    get_all();
    print_all();

    return 0;
}
