# include <detpic32.h>
# include "delay.c"

char getc(void){
    //If OERR == 1 then reset OERR
    if(U1STAbits.OERR == 1){
        U1STAbits.OERR = 0;
    }
    //Wait while URXDA == 0
    while(U1STAbits.URXDA == 0);

    //If FERR or PERR then
    if((U1STAbits.FERR == 1) || (U1STAbits.PERR == 1)){
        char temp = U1RXREG;    // read UxRXREG (to discard the character) and return 0
        return 0;
    }
    //else
    else{
        return U1RXREG;
    }
    //Return U1RXREG
}

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

int configureUART1(unsigned int baud, char parity, unsigned int stopbits){
    //Configure UART1:

    //1 - Configure BaudRate Generator
    if(baud < 600 || baud > 115200){
        baud = 115200;
    }
    U1BRG = ((PBCLK + 8*baud)/(16*baud))-1;
    U1MODEbits.BRGH = 0; //fator de divisão é  16

    //2 - Configure number of data bits, parity and number of stop bits
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
        U1MODEbits.STSEL = 1; // 2 stop bit
    }
    else{
        U1MODEbits.STSEL = 0; // 1 stop bit
    }

    //3 - Enable the transmitter and receiver modules
    U1STAbits.UTXEN = 1; //transmission module
    U1STAbits.URXEN = 1; //reception module

    //4 - Enable UART1
    U1MODEbits.ON = 1;
}

int main(void){
    
    configureUART1(115200,'N',1);
    while (1)
    {
        putc( getc() );

    }

    return 0;
    
}