# include <detpic32.h>
# include <send2displays.c>

int main(void){

    char count = 0;

    while(1){
        send2displays(count);
        delay(200);
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