# include <detpic32.h>

void setPWM (unsigned int dutyCycle){

    //duty_cycle must be in the range [0, 100]
    if(dutyCycle < 0 || dutyCycle > 100){
        dutyCycle = 50;
    }

    OC1RS = ((49999+1)*dutyCycle)/100; //evaluate OC1RS as a function of "dutyCycle"
}

int main(void){

    //configure Timer 3
    T3CONbits.TCKPS = 2;
    PR3 = 49999;
    TMR3 = 0;
    T3CONbits.TON = 1;

    OC1CONbits.OCM = 6;
    OC1CONbits.OCTSEL = 1;
    setPWM(100);
    OC1CONbits.ON = 1;

    while (1);

    return 1;
    
}