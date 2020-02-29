#include <detpic32.h>

void delay(int);

 void main(void){

     TRISEbits.TRISE0 = 0;
     TRISEbits.TRISE1 = 0;
     TRISEbits.TRISE2 = 0;
     TRISEbits.TRISE3 = 0;

     LATE = (LATE & 0XFFF0); //valor das saídas -> começa a 0000


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