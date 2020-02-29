# include <detpic32.h>

void putc(char byte2send){

    while(U1STAbits.UTXBF == 1);

    U1TXREG = byte2send;
}

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();

        while(readCoreTimer() < 20000);
    }
}

int main(void){

    //Configure UART1:

    //1-Configure baudrate
    U1BRG = ((PBCLK + 8 * 115200) / (16 * 115200)) - 1;
    U1MODEbits.BRGH = 0;

    //2-Configure number of data bits, parity and number of stop bits
    U1MODEbits.PDSEL = 00;
    U1MODEbits.STSEL = 0;

    //3-Enable the transmitter and receiver modules
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;

    //4-Enable UART1
    U1MODEbits.ON = 1;

    while(1){
        putc('+');
        delay(1000);
    }

    return 0;

}
