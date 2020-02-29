#include <detpic32.h>

void delay(int);

 void main(void){
     
     TRISB = TRISB & 0x00FF;
     TRISDbits.TRISD5 = 0;
     TRISDbits.TRISD6 = 0;

     //display low
     LATDbits.LATD5 = 1;
     LATDbits.LATD6 = 0;

     while(1){
         delay(250);

     LATB = LATB & 0x00FF;

     char c = toLowerCase(getChar());
     while(c != 'a' && c != 'b' && c != 'c' && c != 'd' && c != 'e' && c != 'f' && c != 'g' && c != '.'){
        c = getChar();

        printStr("\nRead char:");
        putChar(c);

        c = toLowerCase(c);

        printStr("")


     }


     LATE = (LATE & 0XFFF0);


     int count = 0;

     while(1){
         delay(1000);
         LATE = (LATE & 0XFFF0) | count;
         count++;
     }

     return 1;



 } 

 void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);
    }
} 