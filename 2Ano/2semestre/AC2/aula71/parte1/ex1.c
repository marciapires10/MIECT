#include <detpic32.h>


int main(void){
    //Configure Timer T3 (2Hz with interrupts disabled)

    T3CONbits.TCKPS = 7; //pre-scaler 1:(2, ou 4, etc...)  20MHz/256 (pq 7) = x, x/2Hz = y
    PR3 = 39062; //não pode ser maior que 62499; y-1 resultado
    TMR3 = 0;
    T3CONbits.TON = 1;

    while(1){
        //Wait until T3IF = 1
        while(IFS0bits.T3IF == 0);

        //Reset T3IF
        IFS0bits.T3IF = 0;

        putChar('.');
    }

    return 0;
}

