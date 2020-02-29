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

volatile int dutyCycle = 50;

# include <detpic32.h>
# include "send2displays.c"

volatile int putC = 1;

void configureUART1(void){

    U1BRG = ((PBCLK + 8 * 19200) / (16 * 19200)) - 1;
    U1MODEbits.BRGH = 0; //fator de divisão = 16

    U1MODEbits.PDSEL = 01;
    U1MODEbits.STSEL = 1;

    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;

    U1MODEbits.ON = 1;

    // interrupções

    U1STAbits.URXISEL = 00;
    IEC0bits.U1RXIE = 1;
    IPC6bits.U1IP = 2;
    IFS0bits.U1RXIF = 0;

}

void configureT3(void){

    T3CONbits.TCKPS = 2;
    PR3 = 49999;
    TMR3 = 0;
    T3CONbits.TON = 1;

    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;
}

void configureT1(void){

    T1CONbits.TCKPS = 3;
    PR1 = 39062;
    TMR1 = 0;
    T1CONbits.TON = 1;

    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;

}

void setPWM(){
    OC1RS = ((49999+1) * dutyCycle) / 100;
}

void putc(char byte2send){
    while(U1STAbits.UTXBF == 1);

    U1TXREG = byte2send;
}

void puts(char *s){
    while(*s != '\0'){
        putc(*s);
        s++;
    }
}

void _int_(24) isr_uart1(void){

    if(U1RXREG == '+'){
        putc('+');
        dutyCycle += 5;
        if(dutyCycle > 95){
            puts("\nO duty-cycle tem que ser menor que 95%.\n");
            dutyCycle = 95;
        }
        //setPWM();
    }
    else if(U1RXREG == '-'){
        putc('-');
        dutyCycle -= 5;
        if(dutyCycle < 5){
            puts("\nO duty-cycle tem que ser maior que 5%.\n");
            dutyCycle = 5;
        }
        //setPWM();
    }
    setPWM();

    IFS0bits.U1RXIF = 0;
}

void _int_(12) isr_T3(void){

    char toBCD = ((dutyCycle/10) << 4) + (dutyCycle%10);
    send2displays(toBCD);

    IFS0bits.T3IF = 0;
}

void _int_(4) isr_T1(void){

    if(putC){
        puts("O valor atual do duty-cycle é ");
        putc('0'+dutyCycle/10);
        putc('0'+dutyCycle%10);
    }

    putC = !putC;

    IFS0bits.T1IF = 0;

}

int main(void){

    OC1CONbits.OCM = 6;
    setPWM();
    OC1CONbits.OCTSEL = 1;
    OC1CONbits.ON = 1;

    configureUART1();
    configureT1();
    configureT3();
    EnableInterrupts();

    while(1);

    return 0;
}