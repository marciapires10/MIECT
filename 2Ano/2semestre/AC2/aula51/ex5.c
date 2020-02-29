#include <detpic32.h>
#include "delay.c"
#include "send2displays.c"

unsigned char toBcd(unsigned char value){
    return ((value / 10) <<4) + (value % 10);
}

int main(void){

    // Configure the A/D module and port RB4 as analog input
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 4-1;

    AD1CHSbits.CH0SA = 4;

    AD1CON1bits.ON = 1;

    int i = 0;
    int t = 0;
    double v = 0;

    while(1){

        if(t++ % 25 == 0){
            AD1CON1bits.ASAM = 1; //start conversion

            while(IFS1bits.AD1IF == 0); //wait while conversion not done

            int *p = (int *)(&ADC1BUF0);
            int VAL_AD = 0;
            for(i = 0; i < 16; i++){
                VAL_AD += p[i*4];
                //printInt(p[i*4], 10 | 4 << 16);
                //putChar(' ');
            }

            VAL_AD = VAL_AD / 4;
            v = (VAL_AD*33 + 511)/1023;

            IFS1bits.AD1IF = 0;
            
            printf("\nAmplitude da tensão: %f", v);
        }

        send2displays(toBcd((char)v));
        delay(10);

    }

    return 0;

}




