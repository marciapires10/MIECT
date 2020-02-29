# include <detpic32.h>


void _int_(27) isr_adc(void){

    //Print ADC1BUF0 value
    printInt(ADC1BUF0, 16 | 3 << 16);

    //Start A/D conversion
    AD1CON1bits.ASAM = 1;

    IFS1bits.AD1IF = 0;

}


int main(void){
    //Configure all (digital I/O, analog input, A/D module)

    LATE.
    
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 16-1;

    AD1CHSbits.CH0SA = 4;

    AD1CON1bits.ON = 1;

    //Interrupt System

    //step1
    IPC6bits.AD1IP = 2; // configure priority of A/D interrupts

    //step2
    IFS1bits.AD1IF = 0; // clear A/D interrupt flag

    //step3
    IEC1bits.AD1IE = 1; // enable A/D interrupt

    //step4
    EnableInterrupts();

    //Start A/D conversion 
    AD1CON1bits.ASAM = 1;

    while(1){}

    return 0;

}