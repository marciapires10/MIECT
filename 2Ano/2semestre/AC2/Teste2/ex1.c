# include <detpic32.h>

volatile int voltage;

# define sample 8

void send2displays(unsigned int value){
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0;

    TRISB = (TRISB & 0x00FF);
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    char dl = value & 0x0F;
    char dh = value >> 4;

    if(displayFlag == 0){
        LATB = (LATB & 0x00FF) | display7Scodes[dl] << 8;
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
    }
    else if(displayFlag == 1){
        LATB = (LATB & 0x00FF) | display7Scodes[dh] << 8;
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
    }

    displayFlag = !displayFlag;

}

int toBCD(int value){
    return ((value/10) << 4) + (value%10);
}

void configUART(void){
    U1BRG = ((PBCLK + 8*38400) / (16*38400)) - 1;
    U1MODEbits.BRGH = 0;

    U1MODEbits.PDSEL = 10;
    U1MODEbits.STSEL = 0;

    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;

    U1MODEbits.ON = 1;

    //interrupções

    U1STAbits.URXISEL = 00;

    IEC0bits.U1RXIE = 1;
    IPC6bits.U1IP = 1;

    IFS0bits.U1RXIF = 0;
}

void configADC(void){

    TRISBbits.TRISB4 = 1; // RBx digital output disconnected
    AD1PCFGbits.PCFG4= 0; // RBx configured as analog input (AN4)
    AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
    // mode an internal counter ends sampling and
    // starts conversion
    AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
    // interrupt is generated. At the same time,
    // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = sample-1; // Interrupt is generated after XX samples
    // (replace XX by the desired number of
    // consecutive samples)
    AD1CHSbits.CH0SA = 4; // replace x by the desired input
    // analog channel (0 to 15)
    AD1CON1bits.ON = 1; // Enable A/D converter
    // This must the last command of the A/D
    // configuration sequence 

    //interrupções

    IPC6bits.AD1IP = 2;
    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;
}

void _int_(27) isr_adc(void){
    int i;
    int VAL_AD;
    int *p = (int *)(&ADC1BUF0);

    for(i=0; i < sample; i++){
        VAL_AD += p[i*4];
    }

    VAL_AD = VAL_AD/sample;

    voltage = (VAL_AD*99+511)/1023;

    IFS1bits.AD1IF = 0;
}

void configT4(void){
    T4CONbits.TCKPS = 2; // 1:32 prescaler (i.e Fout_presc = 625 KHz)
    PR4 = 34482; // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR4 = 0; // Reset timer T2 count register
    T4CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence) 

    //interrupções
    IPC4bits.T4IP = 2;
    IEC0bits.T4IE = 1;
    IFS0bits.T4IF = 0;
}

void _int_(16) isr_T4(void){

    send2displays(toBCD(voltage));
    IFS0bits.T4IF = 0;

}

void configT3(void){
    T3CONbits.TCKPS = 2; // 1:32 prescaler (i.e Fout_presc = 625 KHz)
    PR3 = 49999; // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR3 = 0; // Reset timer T2 count register
    T3CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence)
    OC1CONbits.OCM = 6; // PWM mode on OCx; fault pin disabled
    OC1CONbits.OCTSEL = 1;// Use timer T2 as the time base for PWM generation
    OC1CONbits.ON = 1; // Enable OC1 module 

    //interrupções
    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;
}

void _int_(12) isr_T3(void){
    IFS0bits.T3IF = 0;
}

void setPWM(int dutyCycle){
    OC1RS = ((49999+1) * dutyCycle)/100;
}

void putc(char byte2send){
    while(U1STAbits.UTXBF == 1);

    U1TXREG = byte2send;
}

void _int_(24) isr_uart1(void){

    char tmp = U1RXREG;

    if(tmp == 'A'){
        putc('A');
        AD1CON1bits.ASAM = 1;
    }
    else if(tmp == 'D'){
        putc('D');
        configT4();
    }
    else if(tmp == 'E'){
        putc('E');
        putc(' ');
        putc('0' + voltage/10);
        putc('0' + voltage%10);
        putc(' ');
    }
    else if(tmp == 'P'){
        putc('P');
        setPWM(voltage);
    }


    IFS0bits.U1RXIF = 0;
}

int main(void){

    configUART();
    configADC();
    configT3();
    EnableInterrupts();

    while(1);

    return 1;
}