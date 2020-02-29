# include <detpic32.h>

int main(void){
    //Configure UART1:

    //1 - Configure BaudRate Generator
    U1BRG = ((PBCLK + 8*115200)/(16*115200)-1;
    U1MODEbits.BRGH = 0; //fator de divisão é  16

    //2 - Configure number of data bits, parity and number of stop bits
    U1MODEbits.PDSEL = 00;
    U1MODEbits.STSEL = 0; // 1 stop bit

    //3 - Enable the transmitter and receiver modules
    U1STAbits.UT1EN = 1; //transmission module
    U1STAbits.UR1EN = 1; //reception module

    //4 - Enable UART1
    U1MODEbits.ON = 1; 

    while(1);

    return 0;
}