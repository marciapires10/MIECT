#include <detpic32.h>
#include "delay.c"

int main(void){

    static const char seg[] = {0x01, 0x02, 0x40, 0x10, 0x08, 0x04, 0x40, 0x20};

    // outputs
    TRISB = (TRISB & 0x00FF);
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    LATDbits.LATD5 = 1;

    //configurar o módulo A/D
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 4-1; //4 amostras

    AD1CHSbits.CH0SA = 4;

    AD1CON1bits.ON = 1;

    int i = 0;
    double v = 0;

    while(1){

        AD1CON1bits.ASAM = 1; // start conversion

        while(IFS1bits.AD1IF == 0);

        int *p = (int *)(&ADC1BUF0);
        int media = 0;        
        for(i=0; i < 16; i++){
            media += p[i*4];
        }

        media = media/4;
        v = (media*33 + 511)/1023;

        IFS1bits.AD1IF = 0;

        for(i = 0; i < 8; i++){
            LATB = (LATB & 0x80FF) | seg[i] << 8;
            delay(v);
        }
    }

    return 0;


}