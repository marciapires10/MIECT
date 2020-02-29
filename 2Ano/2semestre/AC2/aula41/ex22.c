#include <detpic32.h>
#include "send2displays.c"
#include "delay.c"

int main(void){

    char count = 0;

    while(1){

        send2displays(count);
        delay(200);
        count++;
    }

    return 1;
}

