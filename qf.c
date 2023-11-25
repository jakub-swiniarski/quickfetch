#include <stdio.h>
#include "config.h"

int main(){
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            printf("%c",ASCII[i][j]);
        }
        printf("\n");
    }

    return 0;
}
