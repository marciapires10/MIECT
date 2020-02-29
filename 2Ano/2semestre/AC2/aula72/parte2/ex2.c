# include <detpic32.h>

void setPWM(unsigned int dutyCycle){

    if(dutyCycle < 0 || dutyCycle > 100){
        dutyCycle = 50;
    }
    
    OC1RS = ((12499 + 1) * dutyCycle)/100;
}

int main(void){

    //Configure Timer T3
    T3CONbits.TCKPS = 4;
    PR3 = 12499;
    TMR3 = 0;
    T3CONbits.TON = 1;

    //duty-cycle
    OC1CONbits.OCM = 6;
    OC1CONbits.OCTSEL = 1;
    setPWM(100);
    OC1CONbits.ON = 1;


    while(1);

    return 0;
}