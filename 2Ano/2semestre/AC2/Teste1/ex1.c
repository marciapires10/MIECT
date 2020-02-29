/* Escreva um programa que:
    
    a) Comece por configurar a UART1 com os seguintes parâmetros:
        19200 bps, 8 data bits, even parity, 2 stop bits

    b) Configure o módulo OC1 com um sinal com 100Hz de frequência e duty-cyle 50%.
        Observe o sinal no osciloscópio.

    c) Quando receber (por interrupção da UART) os caracteres '+' e '-' aumente ou diminua o valor do 
        duty-cycle em 5%.
        Mantenha o valor do duty-cycle entre os 5 e 95% e envie mensagens adequadas ao
        utilizador informando de tentativas fora da gama.

    d) Mostre a percentagem do duty-cycle nos displays de 7seg, com uma frequência de 100Hz.

    e) Sem usar system calls, a cada segundo envie para o ecrã uma string com a mensagem:
        "O valor atual do duty-cycle é xx%"

*/

# include <detpic32.h>

volatile int dutyCycle = 50;

void send2displays(unsigned char c){
    TRISB = (TRISB & 0x00FF);
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

    static char displayFlag = 0;

    char dh = c >> 4;
    char dl = c & 0x0F;

    if(displayFlag == 0){
        LATB = (LATB & 0x00FF) | (display7Scodes[dl] << 8);

        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;

    }
    else if(displayFlag == 1){
        LATB = (LATB & 0x00FF) | (display7Scodes[dh] << 8);
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
    }

    displayFlag = !displayFlag;
}

int toBCD(int value){
    return (((value/10) << 4) + value%10);
}

void configUART1(void){

    U1BRG = ((PBCLK + 8*19200) / (16*19200)) - 1;
    U1MODEbits.BRGH = 0;

    U1MODEbits.PDSEL = 01;
    U1MODEbits.STSEL = 1;

    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;

    U1MODEbits.ON = 1;

    // interrupções

    U1STAbits.URXISEL = 00;

    IEC0bits.U1RXIE = 1;

    IPC6bits.U1IP = 2;

    IFS0bits.U1RXIF = 1;

}

void setPWM(int dutycycle){

    OC1RS = ((49999 + 1) * dutycycle) / 100;

}

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();

        while(readCoreTimer() < 20000);
    }
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

void putc(char byte2send){

    while(U1STAbits.UTXBF == 1);

    U1TXREG = byte2send;
}

void puts(char *s){
    while(*s){
        putc(*s);
        s++;
    }
}

void _int_(24) isr_uart1(void){

    char tmp = U1RXREG;

    if(tmp == '+'){
        putc('+');
        dutyCycle += 5;
        if(dutyCycle > 95){
            puts("\nDuty-cycle tem que ser inferior a 95%\n");
            dutyCycle = 95;
        }
    }
    else if(tmp == '-'){
        putc('-');
        dutyCycle -= 5;
        if(dutyCycle < 5){
            puts("\nDuty-cycle tem que ser superior a 5%\n");
            dutyCycle = 5;
        }
    }

    setPWM(dutyCycle);


    IFS0bits.U1RXIF = 0;

}

void _int_(12) isr_T3(void){

    send2displays(toBCD(dutyCycle));

    IFS0bits.T3IF = 0;

}

int main(void){
    printStr("Marcia Pires, nºMEC 88747");

    configUART1();
    configT3();
    //setPWM(dutyCycle);

    EnableInterrupts();

    while(1){
        puts("\nO valor atual do duty-cycle é:");
        putc('0' + dutyCycle/10);
        putc('0' + dutyCycle%10);
        delay(1000);
    }
    
    return 1;
}