# include <detpic32.h>
# include "delay.c"

void putc(char byte2send){

    //wait while UTXBF == 1
    while(U1STAbits.UTXBF == 1);

    //copy byte2send to the UXTXREG register
    U1TXREG = byte2send;

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

    configureUART1();

    while(1){
        putc('+');
        delay(1000);
    }

    return 0;
}