#include <detpic32.h>
#include "delay.c"

int main(void){

    int cnt = 0;


    //atribuir valor inicial para que possam ser configurados como outputs
    LATEbits.LATE0 = 0; 
    LATEbits.LATE1 = 0;
    LATEbits.LATE2 = 0;
    LATEbits.LATE3 = 0;


    //configurar como outputs
    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE2 = 0;
    TRISEbits.TRISE3 = 0;


    while(1){
        //frequência de 4Hz
        delay(1000); 

        //em cada ciclo, os outputs são postos a zero (dão reset) e é atribuído o valor do count
        LATE = (LATE & 0XFFF0) | cnt;

        cnt++;
    }

    return 1;



}