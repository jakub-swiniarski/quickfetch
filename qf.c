#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <sys/utsname.h>
#include <time.h>

#include "config.h"

/* function declarations */
static void get_all(void);
static void get_battery(int *y);
static void get_disk(int *y);
static void get_kernel(int *y);
static void get_memory(int *y);
static void print_all(void);
static void get_temp(int *y);
static void get_time(int *y);
static void get_uptime(int *y);

/* variables */
static char data[N_ROWS][LEN_DATA];

/* function implementations */
void get_all(void) {
    int y = 0;
    /* put these in the same order as their labels */
    get_kernel(&y);
    get_time(&y);
    get_uptime(&y);
    get_temp(&y);
    get_memory(&y);
    get_disk(&y);
    get_battery(&y);
}

void get_battery(int *y) {
    FILE *fptr = fopen(BATTERY,"r");
    if (fptr == NULL)
        strcpy(data[*y], "ERROR");
    else {
        fgets(data[*y], LEN_DATA, fptr); 
        fclose(fptr);
        for(int i = 0; i < LEN_DATA; i++){
            if(data[*y][i] == '\n'){
                data[*y][i] = '%';
                break;
            }
        }
    }
    ++*y;
}

void get_disk(int *y) {
    struct statvfs buffer_statvfs;
    if (statvfs(DISK, &buffer_statvfs) != 0)
        strcpy(data[*y], "ERROR");
    else {
        long long disk_total = buffer_statvfs.f_blocks * buffer_statvfs.f_bsize;
        long long disk_free = buffer_statvfs.f_bfree * buffer_statvfs.f_frsize;
        long long disk_used = disk_total - disk_free;
        int disk_used_gib = disk_used / (1024*1024*1024);
        int percentage_used = 100 * disk_used / disk_total;
        sprintf(data[*y], "%d GiB used (%d%%)", disk_used_gib, percentage_used);
    }
    ++*y;
}

void get_kernel(int *y) {
    struct utsname buffer_utsname;
    if (uname(&buffer_utsname) != 0)
        strcpy(data[*y], "ERROR");
    else
        strcpy(data[*y], buffer_utsname.release);
    ++*y;
}

void get_memory(int *y) {
    FILE *fptr = fopen(MEMORY, "r");
    if (fptr == NULL)
        strcpy(data[*y], "ERROR");
    else {
        int mem_total, mem_free, mem_available, mem_used; 
        fscanf(fptr, "MemTotal: %d kB MemFree: %d kB MemAvailable: %d kB", &mem_total, &mem_free, &mem_available); 
        fclose(fptr); 
        mem_used = mem_total - mem_available;
        int percentage_used = 100 * mem_used / mem_total;
        mem_used = mem_used / 1024;
        if (mem_used > 1024)
            sprintf(data[*y], "%.2f GiB used (%d%%)", (float)mem_used / 1024, percentage_used);
        else
            sprintf(data[*y], "%d MiB used (%d%%)", mem_used, percentage_used);
    }
    ++*y;
}

void print_all(void) {
    for(int i = 0; i < N_ROWS; i++){
        printf(COL_LOGO "%s", LOGO[i]);
        printf("%s", LABELS[i]);
        printf(COL_TEXT "%s\n", data[i]);
    }
}

void get_temp(int *y) {
    FILE *fptr = fopen(CPU_TEMP, "r");
    if (fptr == NULL)
        strcpy(data[*y], "ERROR");
    else {
        fgets(data[*y], LEN_DATA, fptr);
        int temp = atoi(data[*y]);
        sprintf(data[*y], "%d °C", temp / 1000);
        fclose(fptr);
    }
    ++*y;
}

void get_time(int *y) {
    time_t now = time(NULL);
    struct tm *now_tm = localtime(&now);
    if (now_tm == NULL)
        strcpy(data[*y], "ERROR");
    else
	    sprintf(data[*y], "%02d:%02d", now_tm->tm_hour, now_tm->tm_min);
    ++*y;
}

void get_uptime(int *y) {
    FILE *fptr = fopen(UPTIME, "r");
    if(fptr == NULL)
        strcpy(data[*y], "ERROR");
    else {
        char ch;
        strcpy(data[*y], " ");
        while ((ch = fgetc(fptr)) != ' ')
            strncat(data[*y], &ch, 1);
        int uptime = atoi(data[*y]);
        uptime = uptime / 60;
        if (uptime < 60)
            sprintf(data[*y], "%d min", uptime);
        else {
            int hours = uptime / 60;
            int mins = uptime - hours * 60;
            sprintf(data[*y], "%d h %d min", hours, mins);
        }
        fclose(fptr);
    }
    ++*y;
}

int main(void) {
    get_all();
    print_all();

    return 0;
}
