#include <detpic32.h>

int main(void){
    //Configure Timers T1 and T3 with interrupts enabled

    //T1
    T1CONbits.TCKPS = 3;
    PR1 = 39062;
    TMR1 = 0;
    T1CONbits.TON = 1;

    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;

    //T3
    T3CONbits.TCKPS = 5;
    PR3 = 32149;
    TMR3 = 0;
    T3CONbits.TON = 1;

    IPC3bits.T3IP = 2; //Interrupt priority (must be in range [1..6])
    IEC0bits.T3IE = 1; //Enable timer T3 interrupts

    //Reset T1IF and T3IF flags
    IFS0bits.T1IF = 0;
    IFS0bits.T3IF = 0;

    EnableInterrupts();

    while(1);

    return 0;
}

void _int_(4) isr_T1(void){
    //print char '1'
    putChar('1');

    //Reset T1IF flag
    IFS0bits.T1IF = 0;
}

void _int_(12) isr_T3(void){
    //print char '3'
    putChar('3');

    //Reset T3IF flag
    IFS0bits.T3IF = 0;
}