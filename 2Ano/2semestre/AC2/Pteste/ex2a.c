#include <detpic32.h>
#include "delay.c"

int i = 0;

int main(void){

    //static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static const char seg[] = {0x01, 0x02, 0x40, 0x10, 0x08, 0x04, 0x40, 0x20};

    // outputs
    TRISB = (TRISB & 0x00FF);
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;


    while(1){
        for(i = 0; i < 8; i++){
            LATB = (LATB & 0x80FF) | seg[i] << 8;

            delay(50);
        }
    }


}