#include <detpic32.h>
#include "delay.c"

int main(void){

    volatile int aux;

    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 4-1;

    AD1CHSbits.CH0SA = 4;

    AD1CON1bits.ON = 1;

    TRISEbits.TRISE0 = 0;

    while(1){
        LATEbits.LATE0 = 1;

        AD1CON1bits.ASAM = 1;

        while(IFS1bits.AD1IF == 0);

        LATEbits.LATE0 = 0;

        aux = ADC1BUF0;

        IFS1bits.AD1IF = 0;
    }

    return 0;
}