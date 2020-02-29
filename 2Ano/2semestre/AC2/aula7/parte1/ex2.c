#include <detpic32.h>

int main(void)
 {
 // Configure Timer T3 with interrupts enabled
    T3CONbits.TCKPS = 7; // 1:256ca prescaler (i.e. fout_presc = 78125 KHz)
    PR3 = 39063;
    TMR3 = 0;
    T3CONbits.TON = 1;

    IPC3bits.T3IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T3IE = 1; // Enable timer T2 interrupts
    IFS0bits.T3IF = 0; // Reset timer T2 interrupt flag 

    EnableInterrupts();
    while(1);
    return 0;

 }
 void _int_(12) isr_T3(void) // Replace VECTOR by the timer T3
 // vector number
 {
     IFS0bits.T3IF = 0;
     putChar('.');
 // Reset T3 interrupt flag
 } 