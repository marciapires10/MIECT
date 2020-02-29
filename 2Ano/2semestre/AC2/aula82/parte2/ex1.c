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

    U1STAbits.URXISEL = 00;

    IEC0bits.U1RXIE = 1;
    IEC0bits.U1TXIE = 1;

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

    putc(U1RXREG);

    IFS0bits.U1RXIF = 0;
}

int main(void){

    configureUART1(115200,'N', 1);

    EnableInterrupts();

    while(1);

    return 0;
}