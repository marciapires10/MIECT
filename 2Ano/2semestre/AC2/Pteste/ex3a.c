#include <detpic32.h>
#include "delay.c"

int i = 0;
char key;
int play = 0;

int main(void){

    static const char seg[] = {0x6D, 0x5B, 0x66, 0x06, 0x7D, 0x4F};

    TRISB = (TRISB & 0x00FF);
    TRISDbits.TRISD5 = 0;

    LATDbits.LATD5 = 1;

    while(1){

        key = inkey();
        if(key == 'l'){
            play = 1;
        }
        else if(key == 'p'){
            play = 0;
        }
        if(play){
            LATB = (LATB & 0x00FF) | (seg[i] << 8);
            delay(125);
            i++;
            if(i == 6){
                i = 0;
            }
        }
        else{
            LATB = (LATB & 0x00FF) | (seg[i] << 8);
        }
       
    }

    return 0;
}