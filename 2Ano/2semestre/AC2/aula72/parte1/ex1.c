# include <detpic32.h>

int main(void){

    //Configure Timer T3 (2Hz)
    T3CONbits.TCKPS = 7;
    PR3 = 39062;
    TMR3 = 0;
    T3CONbits.TON = 1;

// atendimento por polling

    while(1){

        //Wait until T3IF = 1
        while(IFS0bits.T3IF == 0);

        //Reset T3IF
        IFS0bits.T3IF = 0;

        putChar('.');
    }

    return 0;
}