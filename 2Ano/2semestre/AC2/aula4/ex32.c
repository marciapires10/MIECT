# include <detpic32.h>
# include "send2displays.c"

void delay(int);

int main(void){

    char count = 0;

    while(1){
        int i = 0;
        do{
            delay(13);
            send2displays(count);
        }
        while(++i < 4);
        count++; 

    }

    return 1;
}


void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);
    }
}