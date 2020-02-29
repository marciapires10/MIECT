#include <detpic32.h>
#include "delay.c"
#include "send2displays.c"

unsigned char toBcd(unsigned char value){
    return ((value / 10) <<4) + (value % 10);
}

volatile unsigned char voltage = 0; 
int i;

int main(void){

        unsigned int cnt = 0;

        TRISBbits.TRISB4 = 1;
        AD1PCFGbits.PCFG4 = 0;
        AD1CON1bits.SSRC = 7;

        AD1CON1bits.CLRASAM = 1;

        AD1CON3bits.SAMC = 16;
        AD1CON2bits.SMPI = 8-1;

        AD1CHSbits.CH0SA = 4;
        AD1CON1bits.ON = 1;

        IPC6bits.AD1IP = 2;

        IFS1bits.AD1IF = 0;

        IEC1bits.AD1IE = 1;


        EnableInterrupts();

        //AD1CON1bits.ASAM = 1;

        while(1){
            if(cnt % 25 == 0){
                AD1CON1bits.ASAM = 1;
            }
            send2displays(toBcd(voltage));
            cnt++;
            delay(10);
        }

        return 0;
}

void _int_(27) isr_adc(void){

    int *p = (int *)(&ADC1BUF0);
    int VAL_AD = 0;

    for(i = 0; i < 8; i++){
        VAL_AD += p[i*4];
    }

    VAL_AD = VAL_AD / 8;
    voltage = (VAL_AD*33+511)/1023;

    IFS1bits.AD1IF = 0; // reset AD1IF flag
}

