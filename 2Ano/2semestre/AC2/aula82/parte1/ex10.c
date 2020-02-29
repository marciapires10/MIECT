# include <detpic32.h>

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

    U1MODEbits.ON = 1;

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

char getc(void){
    if(U1STAbits.OERR == 1){
        U1STAbits.OERR = 0;
    }

    while(U1STAbits.URXDA == 0);

    if(U1STAbits.FERR == 1 || U1STAbits.PERR == 1){
        char temp = U1RXREG;
        return 0;
    }
    else{
        return U1RXREG;
    }
}


int main(void){
    configureUART1(115200,'N', 1);

    while(1){
        putc(getc());
    }

    return 0;
}