#include <detpic32.h>

//void delay(int);


void main(void)
 {
   
    // Configure Timer T3 (2 Hz with interrupts disabled)
   T3CONbits.TCKPS = 7; // 1:256ca prescaler (i.e. fout_presc = 78125 KHz)
   PR3 = 39063;
   TMR3 = 0;
   T3CONbits.TON = 1;

    while(1)
    {

    // Wait until T3IF = 1
      while(IFS0bits.T3IF == 0);

    // Reset T3IF
    IFS0bits.T3IF = 0;

    putChar('.');
    }
 }


// void delay(int ms)
// {
//  for(; ms > 0; ms--)
//  {
//  resetCoreTimer();
//  while(readCoreTimer() < 20000);
//  }
// } 