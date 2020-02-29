#include <detpic32.h>
#include "delay.c"


int main(void){

    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char trigger;

    // displays como outputs
    TRISB = (TRISB & 0x00FF);
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    //leds como outputs
    TRISE = (TRISE & 0xFFF0);

    //configurar o módulo A/D
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 4-1; //4 amostras

    AD1CHSbits.CH0SA = 4;

    AD1CON1bits.ON = 1;


    int t = 0;
    int i = 0;
    double v = 0;

    while(1){
        if(t++ % 25 == 0){
            AD1CON1bits.ASAM = 1; //start conversion

            while(IFS1bits.AD1IF == 0); //wait while conversion not done
            
            int *p = (int *)(&ADC1BUF0);
            int media = 0;

            for(i=0; i < 16; i++){
                media += p[i*4];
            }

            media = media/4;
            v = (media*70)/1023;

            IFS1bits.AD1IF = 0;

        }

        char display_high = (int)v >> 4;
        char display_low = (int)v & 0x0F;

        if(trigger == 0){
            LATB = (LATB & 0x00FF) | (display7Scodes[display_low] << 8);
            LATDbits.LATD5 = 1;
            LATDbits.LATD6 = 0;
        }
        else{
            LATB = (LATB & 0x00FF) | (display7Scodes[display_high] << 8);
            LATDbits.LATD5 = 0;
            LATDbits.LATD6 = 1;
        }

        trigger = !trigger;

        LATE = (LATE & 0x0000) | (int)v;

        delay(10);
    }

    return 0;


}