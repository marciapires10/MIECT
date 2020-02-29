/* Escreva um programa que:
    -Configure a UART para comunicar com o pc com os seguintes parâmetros:
        38400bps, 8db, Odd parity, 1 stop bit
    -Quando receber a tecla:
        A-converte o valor à entrada da ADC e transforma-o num valor entre 0 e 99;
        D-coloca o valor obtido nos displays de 7 segmentos(freq de refrescamento de
            145Hz, por interrupção do timer 4);
        E-envio o valor para o ecrã, pela porta série (sem usar system calls)
        P-ajusta o valor do duty-cycle de um sinal PWM para corresponder ao valor 
            obtido da ADC(freq=100Hz, dc=valor).

*/

# include <detpic32.h>
# include "send2displays.c"

# define sample 8
volatile int voltage;

void configureUART1(void){

    U1BRG = ((PBCLK + 8 * 38400) / (16 * 38400)) - 1;
    U1MODEbits.BRGH = 0; // fator de divisão 16

    U1MODEbits.PDSEL = 10;
    U1MODEbits.STSEL = 1;

    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;

    U1MODEbits.ON = 1;

    U1STAbits.URXISEL = 00;

    IEC0bits.U1RXIE = 1;

    IPC6bits.U1IP = 2;
    
    IFS0bits.U1RXIF = 0;


}

void putc(char byte2send){

    while(U1STAbits.UTXBF == 1);

    U1TXREG = byte2send;
}

void _int_(27) isr_adc(void){

    int i;
    int VAL_AD;

    int *p = (int *)(&ADC1BUF0);
    for(i = 0; i < sample; i++){
        VAL_AD += p[i*4];
    }

    VAL_AD = VAL_AD / sample;

    voltage = (VAL_AD*99+511)/3069;

    IFS1bits.AD1IF = 0;
}

void configT4(void){
    T4CONbits.TCKPS = 2;
    PR4 = 34482;
    TMR4 = 0;
    T4CONbits.TON = 1;

    IPC4bits.T4IP = 2;
    IEC0bits.T4IE = 1;
    IFS0bits.T4IF = 0;
}

void _int_(16) isr_T4(void){

    char toBCD = ((voltage/10) << 4) + (voltage%10);

    send2displays(toBCD);

    IFS0bits.T4IF = 0;
}

void configT3(void){
    T3CONbits.TCKPS = 2;
    PR3 = 49999;
    TMR3 = 0;
    T3CONbits.TON = 1;

    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;
}

void _int_(12)  isr_T3(void){
    IFS0bits.T3IF = 0;
}

void setPWM(int dutycycle){

    OC1RS = ((49999+1) * dutycycle)/100;

}


void _int_(24) isr_uart1(void){

    if(U1RXREG == 'A'){
        putc('A');
        AD1CON1bits.ASAM = 1;

    }
    else if(U1RXREG == 'D'){
        putc('D');
        configT4();
    }
    else if(U1RXREG == 'E'){
        putc('E');
        putc('\n');
        putc('0'+(voltage/10));
        putc('0'+(voltage%10));
        putc('\n');
    }
    else if(U1RXREG == 'P'){
        putc('P');
        setPWM(voltage);
    }

    IFS0bits.U1RXIF = 0;
}


int main(void){

    configureUART1();
    configT3();
    

    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = sample - 1;

    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    IPC6bits.AD1IP = 2;
    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;

    OC1CONbits.OCM = 6;
    OC1CONbits.OCTSEL = 1;
    OC1CONbits.ON = 1;

    EnableInterrupts();

    while(1);

    return 0;
}