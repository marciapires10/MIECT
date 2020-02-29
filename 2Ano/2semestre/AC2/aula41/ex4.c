#include <detpic32.h>
#include "delay.c"

int main(void){

    unsigned char seg;

    //atribuição de valor inicial
    LATB = (LATB & 0x00FF);
    LATDbits.LATD5 = 1; // display low
    LATDbits.LATD6 = 0;

    //outputs
    TRISB = (TRISB & 0x00FF);
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    while(1){

        LATDbits.LATD5 = !LATDbits.LATD5;
        LATDbits.LATD6 = !LATDbits.LATD6;

        seg = 1;
        int i;

        for(i=0; i < 7; i++){


            LATB = (LATB & 0x00FF) | seg << 8; //avança para os últimos 8 bits ("pula os primeiros 8")
            delay(500);
            seg = seg << 1; //acrescenta um zero à direita

        }
    }

    return 0;


}