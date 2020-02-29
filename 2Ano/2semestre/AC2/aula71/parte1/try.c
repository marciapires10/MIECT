#include <detpic32.h>
#include "Aux.c"

volatile unsigned char voltage = 0; // Global variable

void _int_(4) isr_T1(void){
    // Start A/D conversion
    AD1CON1bits.ASAM = 1;
    // Reset T1IF flag
    IFS0bits.T1IF == 0;
} 

void _int_(12) isr_T3(void){
    // Send "voltage" (global variable) to displays
    send2displays(toBcd(voltage));
    // Reset T3IF flag
    IFS0bits.T3IF = 0;
} 

void _int_(27) isr_adc(void){
    // Calculate buffer average (8 samples)
    int total = 0;
    int *p = (int *)(&ADC1BUF0);
    int j = 0;
    for( j = 0; j < 8; j++ ){
        // printInt( p[j*4], 10 | 4 << 16);
        // putChar(' ');
        total += p[j*4];
    }
    int val_ad = total/8;
    // Calculate voltage amplitude
    voltage = (val_ad*33 + 511)/1023;
    // Convert voltage amplitude to decimal. Assign it to "voltage"
    IFS1bits.AD1IF = 0; // Reset AD1IF flag
} 

void TimerConfig1(){
    T1CONbits.TCKPS = 3; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR1 = 19530; // Fout = (20000000 / 2^prescaler(7 = 256)) / Freq    -  1   Int[ < 62499]
    TMR1 = 0; // Reset timer T1 count register
    T1CONbits.TON = 1; // Enable timer T1 (must be the last command of the
    // timer configuration sequence) 
}

void TimerConfig3(){
    T3CONbits.TCKPS = 2; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR3 = 50000; // Fout = (20000000 / 2^prescaler(7 = 256)) / Freq    -  1   Int[ < 62499]
    TMR3 = 0; // Reset timer T2 count register
    T3CONbits.TON = 1; // Enable timer T3 (must be the last command of the
    // timer configuration sequence) 
}

void InterruptsTimers1(){
    IPC1bits.T1IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T1IE = 1; // Enable timer T1 interrupts
    IFS0bits.T1IF = 0; // Reset timer T1 interrupt flag 
}

void InterruptsTimers3(){
    IPC3bits.T3IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T3IE = 1; // Enable timer T2 interrupts
    IFS0bits.T3IF = 0; // Reset timer T2 interrupt flag 
}

void configureAll(){
    // Configure all (digital I/O, analog input, A/D module, interrupts)
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CHSbits.CH0SA = 4; // replace x by the desired input
    init_adc();

    IPC6bits.AD1IP = 1; //configurar o nível de prioridade das interrupções geradas pelo módulo A/D 
    IEC1bits.AD1IE = 1; // autorizar as interrupções geradas pelo módulo A/D – registo IEC1, bit AD1IE;
    IFS1bits.AD1IF = 0; // fazer o reset de alguma interrupção pendente – registo IFS1, bit AD1IF;
    
    // mode an internal counter ends sampling and
    // starts conversion
    
    // interrupt is generated. At the same time,
    // hardware clears the ASAM bit
    
    
    // This must the last command of the A/D
    // configuration sequence
    

    

    TimerConfig1();
    TimerConfig3();
    InterruptsTimers1();
    InterruptsTimers3();
}

int main(void){
    configureAll(); // Function to cTRISB = (TRISB & 0x00FF);onfigure all (digital I/O, analog
    EnableInterrupts(); // Global Interrupt Enable
    while(1);
    return 1;
} 