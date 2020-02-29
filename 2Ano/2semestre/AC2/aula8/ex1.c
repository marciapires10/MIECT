#include <detpic32.h>

void delay(int);
void putc(char);

int baudrate = 115200;

int main(void)
 {
    //division value 16
    // se fosse fator de divisão 4, era igual a 1
    U1MODEbits.BRGH = 0;

 // Configure UART1:
 // 1 - Configure BaudRate Generator
    U1BRG = ((PBCLK + 8*baudrate) / (16*baudrate)) - 1;
    
 // 2 – Configure number of data bits, parity and number of stop bits
 // (see U1MODE register)
    U1MODEbits.PDSEL = 01;
    U1MODEbits.STSEL = 0;
 // 3 – Enable the trasmitter and receiver modules (see register U1STA)
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
 // 4 – Enable UART1 (see register U1MODE)
    U1MODEbits.ON = 1;

    while(1){
        putc('U');
        delay(1000);
    }

    return 0;
 }

 void putc(char byte2send){

     while(U1STAbits.UTXBF == 1);

     U1TXREG = byte2send;
 }

 void delay(int ms) 
 {
 	while (ms > 0)
 	{
 		resetCoreTimer();
 		while (readCoreTimer() < 20000);
 		ms--;
 	}
 }
