# include <detpic32.h>
# include "send2displays.c"

volatile int numSamples = 8;

volatile unsigned char voltage = 0;

int main(void){

    //TRISB = ((TRISB & 0xFFFC) | 0x0003);
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0; 

    // LATDbits.LATD5 = 0;
    // LATDbits.LATD6 = 1;

    TRISB = TRISB & 0x00FF;
    //TRISD = TRISD & 0xFF9F;

    //Configure port RB4 as analog input
    TRISBbits.TRISB4 = 1; //RB4 digit output disconnected
    AD1PCFGbits.PCFG4 = 0; //RB4 configured as analog input (AN4)

    //Configure ADCC
    AD1CHSbits.CH0SA = 4;
    AD1CON2bits.SMPI = numSamples - 1;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON1bits.ON = 1;

    //Interrupt system for the ADC
    IPC6bits.AD1IP = 1;
    IEC1bits.AD1IE = 1;
    IFS1bits.AD1IF = 0;

    //Configure Timer 1
    T1CONbits.TCKPS = 3;
    PR1 = 19530;
    TMR1 = 0;
    T1CONbits.TON = 1;

    //Configure Timer 3
    T3CONbits.TCKPS = 2;
    PR3 = 49999;
    TMR3 = 0;
    T3CONbits.TON = 1;

    //Configure Timer 1 interrupts
    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;

    //Configure Timer 3 interrupts
    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;

    EnableInterrupts();

    while(1){
        if((PORTB & 0x0003) == 1){
            IEC0bits.T1IE = 0; // disable TIMER 1
        }
        else{
            IEC0bits.T1IE = 1; //enable TIMER 1
        }
    }
}

void _int_(4) isr_T1(void){

    //start A/D conversion
    AD1CON1bits.ASAM = 1;

    IFS0bits.T1IF = 0; //reset T1 interrupt flag
}

void _int_(12) isr_T3(void){
    send2displays(voltage);

    IFS0bits.T3IF = 0;
}

void _int_(27) isr_adc(void){

    int VAL_AD = 0;
    int i = 0;
    int *p = (int *)(&ADC1BUF0);

    for(i = 0; i < numSamples; i++){
        int value = p[i*4];
        VAL_AD += value;
    }

    VAL_AD = VAL_AD / numSamples;

    voltage = (VAL_AD*33 + 511)/1023;

    IFS1bits.AD1IF = 0;
}

