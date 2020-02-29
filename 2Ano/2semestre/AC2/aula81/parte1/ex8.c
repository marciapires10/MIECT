#include <detpic32.h>

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

int main(void){
    configureUART1(57600, 'N', 1); //default pterm parameters (8 data bits)
    //config RB6 as output
    TRISBbits.TRISB6 = 0;

    while (1)
    {
        // Wait until TRMT == 1
        //while (U1STAbits.TRMT == 1);
        
        // Set RB6
        LATBbits.LATB6 = 1;

        puts("12345");

        //Reset RB6
        LATBbits.LATB6 = 0;
    }

    return 0;
    
}