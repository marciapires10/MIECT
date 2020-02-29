#include <detpic32.h>
#include "delay.c"
#include "send2displays.c"

unsigned char toBcd(unsigned char value){
    return ((value / 10) <<4) + (value % 10);
}

volatile unsigned char voltage = 0; 
int i;

int main(void){

        //Configure Timer T1
        T1CONbits.TCKPS = 3;
        PR1 = 19531;
        TMR1 = 0;
        T1CONbits.TON = 1;

        //Configure Timer T3
        T3CONbits.TCKPS = 4;
        PR3 = 12499;
        TMR3 = 0;
        T3CONbits.TON = 1;

        //Interrupts T1
        IPC1bits.T1IP = 2;
        IEC0bits.T1IE = 1;
        IFS0bits.T1IF = 0;

        //Interrupts T3
        IPC3bits.T3IP = 2;
        IEC0bits.T3IE = 1;
        IFS0bits.T3IF = 0;

        //unsigned int cnt = 0;

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

        IFS1bits.AD1IF = 0;

        EnableInterrupts();

        //AD1CON1bits.ASAM = 1;

        while(1);

        return 0;
}

void _int_(4) isr_T1(void){
    AD1CON1bits.ASAM = 1;

    IFS0bits.T1IF = 0;
}

void _int_(12) isr_T3(void){
    send2displays(voltage);

    IFS0bits.T3IF = 0;
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

