#include <detpic32.h>
#include "delay.c"
#include "send2displays.c"


int main(void){

    TRISE = (TRISE & 0xFFF0);

    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 4-1; // 4 amostras

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
            for(i = 0; i < 16; i++){
                media += p[i*4];
            }

            media = media/4;
            v = (media*33 + 511)/1023;

            IFS1bits.AD1IF = 0; //reset AD1IF

        }

        

        send2displays((int)v);
        LATE = (LATE & 0xFFF0) | (int)v;
        delay(10);
    }

    return 0;


}

