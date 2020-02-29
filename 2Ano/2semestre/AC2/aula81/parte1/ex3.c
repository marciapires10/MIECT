# include <detpic32.h>
# include "delay.c"

void putc(char byte2send){
    while(U1STAbits.UTXBF == 1);

    U1TXREG = byte2send;
}

void puts(char *str){
    //use putc() function to send each character ('\0' should not be sent)
    while(*str != '\0'){
        putc(*str++);
    }
}

int configureUART1(void){
    //Configure UART1:

    //1 - Configure BaudRate Generator
    U1BRG = ((PBCLK + 8*115200)/(16*115200))-1;
    U1MODEbits.BRGH = 0; //fator de divisão é  16

    //2 - Configure number of data bits, parity and number of stop bits
    U1MODEbits.PDSEL = 00;
    U1MODEbits.STSEL = 0; // 1 stop bit

    //3 - Enable the transmitter and receiver modules
    U1STAbits.UTXEN = 1; //transmission module
    U1STAbits.URXEN = 1; //reception module

    //4 - Enable UART1
    U1MODEbits.ON = 1;
}

int main(void){
    //Configure UART1 (115200, N, 8, 1)
    configureUART1();

    while(1){
        puts("String de teste\n");
        //wait 1s
        delay(1000);
    }

    return 0;
    
}