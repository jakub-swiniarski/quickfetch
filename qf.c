#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <sys/utsname.h>
#include <time.h>

#include "config.h"

static void get_all(void);
static void get_battery(void);
static void get_disk(void);
static void get_kernel(void);
static void get_memory(void);
static void get_temp(void);
static void get_time(void);
static void get_uptime(void);
static void print_all(void);

static char data[N_ROWS][LEN_DATA];
static int row;

void get_all(void) {
    row = 0;
    /* put these in the same order as their labels */
    get_kernel();
    get_time();
    get_uptime();
    get_temp();
    get_memory();
    get_disk();
    get_battery();
}

void get_battery(void) {
    FILE *fptr = fopen(battery, "r");
    if (fptr == NULL)
        strcpy(data[row], "ERROR");
    else {
        fgets(data[row], LEN_DATA, fptr); 
        fclose(fptr);
        for (int i = 0; i < LEN_DATA; i++) {
            if (data[row][i] == '\n'){
                data[row][i] = '%';
                break;
            }
        }
    }
    row++;
}

void get_disk(void) {
    struct statvfs buffer_statvfs;
    if (statvfs(disk, &buffer_statvfs) != 0)
        strcpy(data[row], "ERROR");
    else {
        unsigned long long disk_total = buffer_statvfs.f_blocks * buffer_statvfs.f_bsize;
        unsigned long long disk_free = buffer_statvfs.f_bfree * buffer_statvfs.f_frsize;
        unsigned long long disk_used = disk_total - disk_free;
        unsigned int disk_used_gib = disk_used / (1024 * 1024 * 1024);
        unsigned int percentage_used = 100 * disk_used / disk_total;
        sprintf(data[row], "%u GiB used (%u%%)", disk_used_gib, percentage_used);
    }
    row++;
}

void get_kernel(void) {
    struct utsname buffer_utsname;
    if (uname(&buffer_utsname) != 0)
        strcpy(data[row], "ERROR");
    else
        strcpy(data[row], buffer_utsname.release);
    row++;
}

void get_memory(void) {
    FILE *fptr = fopen(memory, "r");
    if (fptr == NULL)
        strcpy(data[row], "ERROR");
    else {
        unsigned int mem_total, mem_free, mem_available, mem_used; 
        fscanf(fptr, "MemTotal: %u kB MemFree: %u kB MemAvailable: %u kB", &mem_total, &mem_free, &mem_available); 
        fclose(fptr); 
        mem_used = mem_total - mem_available;
        unsigned int percentage_used = 100 * mem_used / mem_total;
        mem_used = mem_used / 1024;
        if (mem_used > 1024)
            sprintf(data[row], "%.2f GiB used (%u%%)", (float)mem_used / 1024, percentage_used);
        else
            sprintf(data[row], "%u MiB used (%u%%)", mem_used, percentage_used);
    }
    row++;
}

void get_temp(void) {
    FILE *fptr = fopen(cpu_temp, "r");
    if (fptr == NULL)
        strcpy(data[row], "ERROR");
    else {
        fgets(data[row], LEN_DATA, fptr);
        int temp = atoi(data[row]);
        sprintf(data[row], "%d °C", temp / 1000);
        fclose(fptr);
    }
    row++;
}

void get_time(void) {
    time_t now = time(NULL);
    struct tm *now_tm = localtime(&now);
    if (now_tm == NULL)
        strcpy(data[row], "ERROR");
    else
	    sprintf(data[row], "%02d:%02d", now_tm->tm_hour, now_tm->tm_min);
    row++;
}

void get_uptime(void) {
    FILE *fptr = fopen(uptime, "r");
    if (fptr == NULL)
        strcpy(data[row], "ERROR");
    else {
        char ch;
        strcpy(data[row], " ");
        while ((ch = fgetc(fptr)) != ' ')
            strncat(data[row], &ch, 1);
        unsigned int uptime = atoi(data[row]);
        uptime = uptime / 60;
        if (uptime < 60)
            sprintf(data[row], "%u min", uptime);
        else {
            unsigned int hours = uptime / 60;
            unsigned int mins = uptime - hours * 60;
            sprintf(data[row], "%u h %u min", hours, mins);
        }
        fclose(fptr);
    }
    row++;
}

void print_all(void) {
    for (int i = 0; i < N_ROWS; i++) {
        printf(COL_LOGO "%s ", logo[i]);
        printf("%s", labels[i]);
        printf(COL_TEXT "%s\n", data[i]);
    }
}

int main(void) {
    get_all();
    print_all();

    return 0;
}
