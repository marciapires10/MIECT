#include <detpic32.h>
#include "delay.c"

int main(void){

    LATB = (LATB & 0x00FF);
    LATDbits.LATD5 = 1; // display low ativo
    LATDbits.LATD6 = 0;

    TRISB = (TRISB & 0x00FF);
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;


    while(1){
        delay(250);
        char c = getChar();

        LATB = (LATB & 0x00FF); //reset ao valor dos displays
        putChar(c);
        while(c != 'a' && c != 'b' && c != 'c' && c != 'd' && c != 'e' && c != 'f' && c != 'g' && c != '.'){
            c = getChar();
             putChar(c);
        }

        switch(c){
            case 'a': 
                LATBbits.LATB8 = 1;
                break;
            
            case 'b': 
                LATBbits.LATB9 = 1;
                break;
            
            case 'c': 
                LATBbits.LATB10 = 1;
                break;
            
            case 'd': 
                LATBbits.LATB11 = 1;
                break;
            
            case 'e': 
                LATBbits.LATB12 = 1;
                break;
            
            case 'f': 
                LATBbits.LATB13 = 1;
                break;
            
            case 'g': 
                LATBbits.LATB14 = 1;
                break;
            
            case '.': 
                LATBbits.LATB15 = 1;
                break;
        }


    }

    return 1;   
}
