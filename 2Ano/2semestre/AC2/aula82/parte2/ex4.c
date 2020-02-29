# include <detpic32.h>
# include "send2displays.c"

volatile int voltage = 0; 
volatile int voltMin = 40;
volatile int voltMax = 0;
int i;

volatile int value2display;

void setPWM(unsigned int dutyCycle){

    if(dutyCycle < 0 || dutyCycle > 100){
        dutyCycle = 50;
    }
    
    OC1RS = ((12499 + 1) * dutyCycle)/100;
}

void configureUART1(unsigned int baud, char parity, unsigned int stopbits) {

    if(baud < 600 || baud > 115200){
        baud = 115200;
    }

    U1BRG = ((PBCLK + 8 * baud) / (16 * baud)) - 1;

    U1MODEbits.BRGH = 0;

    if(parity == 'E'){
        U1MODEbits.PDSEL = 01;
    }
    else if(parity == 'O'){
        U1MODEbits.PDSEL = 10;
    }
    else{
        U1MODEbits.PDSEL = 00;
    }

    if(stopbits == 2){
        U1MODEbits.STSEL = 1;
    }
    else if(stopbits == 1){
        U1MODEbits.STSEL = 0;
    }

    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;

    U1STAbits.URXISEL = 00;

    IEC0bits.U1RXIE = 1;
  

    IFS0bits.U1RXIF = 0;
    IFS0bits.U1EIF = 0;

    IPC6bits.U1IP = 2;

    U1MODEbits.ON = 1;

}

void putc(char byte2send){
    while(U1STAbits.UTXBF == 1);

    U1TXREG = byte2send;
}


void _int_(24) isr_uart1(void){

    if(IFS0bits.U1EIF == 1){
        if(U1STAbits.OERR == 1){
            U1STAbits.OERR = 0;
        }
        else{
            char dummy = U1RXREG;
        }

        IFS0bits.U1EIF = 0;
    }

    if(U1RXREG == 'L'){
        putc((voltMin/10) + 0x30);
        putc(' ');
        putc((voltMax/10) + 0x30);

        voltMin = 40;
        voltMax = 0;
    }


    //putc(U1RXREG);

    IFS0bits.U1RXIF = 0;
}

int main(void){

        int dutyCycle;

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

        //duty-cycle
        OC1CONbits.OCM = 6;
        OC1CONbits.OCTSEL = 1;
        OC1CONbits.ON = 1;

        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;

        TRISB = TRISB & 0x00FF;
        TRISD = TRISD & 0xFF9F;

        configureUART1(115200,'N',1);

        EnableInterrupts();

        while(1){
            char portVal = PORTB & 0x0003;

            switch (portVal)
            {
            case 0:
                IEC0bits.T1IE = 1;
                setPWM(0);
                break;
            case 1:
                IEC0bits.T1IE = 0;
                setPWM(100);
                break;
            default:
                IEC0bits.T1IE = 1;
                dutyCycle = voltage * 3;
                setPWM(dutyCycle);
                break;
            }
        }

        return 0;
}

void _int_(4) isr_T1(void){
    AD1CON1bits.ASAM = 1;

    IFS0bits.T1IF = 0;
}

void _int_(12) isr_T3(void){
    static int counter = 0;

    send2displays(value2display);

    if(++counter == 100){
        counter = 0;
        putc((voltage/10)+0x30);
    }

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

    int wp = voltage / 10;
    int dp = voltage % 10;


    value2display = (wp & 0x000F) << 4 | (dp & 0x000F);

    if(voltage < voltMin){
        voltMin = voltage;
    }

    if(voltage > voltMax){
        voltMax = voltage;
    }

    IFS1bits.AD1IF = 0; // reset AD1IF flag
}