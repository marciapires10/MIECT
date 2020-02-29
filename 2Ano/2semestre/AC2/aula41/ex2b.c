#include <detpic32.h>
#include "send2displays.c"
#include "delay.c"

int main(void){

    char count = 0;
    int i;

    while(1){
        i = 0;
        
        do{
            delay(10);
            send2displays(count);
            
        } while(++i < 50);
        count++;
    }

    return 0;

}