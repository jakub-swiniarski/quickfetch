#include <stdio.h>
#include "config.h"

int main(){
    //get data
    /*char data[HEIGHT][10];

    FILE *fptr;
    fptr=fopen(BATTERY,"r");
    */

    //print ascii logo and data
    for(int i=0; i<HEIGHT; i++){
        //logo
        printf(ASCII_COLOR"%s", ASCII[i]);
        
        //data
        printf(" ");
        printf("%s",LABELS[i]);
        printf(TEXT_COLOR);
        printf("\n");
    }

    return 0;
}
