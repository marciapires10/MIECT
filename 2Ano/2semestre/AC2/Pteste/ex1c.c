#include <detpic32.h>
#include "delay.c"


volatile unsigned char v = 0;
int i=0;

int main(void){

    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char trigger;

    TRISB = (TRISB & 0x00FF);
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

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

    //adicional do interrupt

    IPC6bits.AD1IP = 2;

    IFS1bits.AD1IF = 0;

    IEC1bits.AD1IE = 1;

    EnableInterrupts();

    int t = 0;

    while(1){

        if(t++ % 25 == 0){
            AD1CON1bits.ASAM = 1; // start conversion
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

void _int_(27) isr_adc(void){

    int *p = (int *)(&ADC1BUF0);
    int media = 0;

    for(i=0; i < 4; i++){
        media += p[i*4];
        printInt(p[i*4], 10 | 4 << 16);
        putChar(' ');
    }

    media = media/4;
    v = (media*50)/1023;

    IFS1bits.AD1IF = 0;

}
