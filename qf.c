#include <stdio.h>
#include "config.h"

int main(){
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            printf(ASCII_COLOR"%c", ASCII[i][j]);
        }
        printf(TEXT_COLOR);
        printf("\n");
    }

    return 0;
}
