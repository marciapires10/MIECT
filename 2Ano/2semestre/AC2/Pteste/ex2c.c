#include <detpic32.h>
#include "delay.c"

volatile unsigned char voltage;
int i = 0;
int t = 0;
int main(void){

    static const char seg[] = {0x01, 0x02, 0x40, 0x10, 0x08, 0x04, 0x40, 0x20};

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

    //adicional do interrupt

    IPC6bits.AD1IP = 2;

    IFS1bits.AD1IF = 0;

    IEC1bits.AD1IE = 1;

    EnableInterrupts();

    while(1){

        AD1CON1bits.ASAM = 1; // start conversion

        for(i = 0; i < 8; i++){
            LATB = (LATB & 0x80FF) | seg[i] << 8;
            delay(voltage);
        }

    }

    return 0;

}


void _int_(27) isr_adc(void){
    int *p = (int *)(&ADC1BUF0);
    int media = 0;

    for(t=0; t<16; t++){
        media += p[t*4];
    }

    media = media/4;

    voltage = (media*33 + 511)/1023;

    IFS1bits.AD1IF = 0;
}