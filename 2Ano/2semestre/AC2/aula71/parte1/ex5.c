#include <detpic32.h>

volatile int voltage = 0; //global variable

static int sample_num = 8;

void send2displays(unsigned char value){
    
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,
        0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

    static char displayFlag = 0;

    unsigned char digit_lov = value & 0x0F;
    unsigned char digit_high = value >> 4;

    if(!displayFlag){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;

        LATB = (LATB & 0x00FF) | ((int) display7Scodes[digit_lov] << 8);
    }
    else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;

        LATB = (LATB & 0X00FF) | ((int) display7Scodes[digit_high] << 8);
    }

    displayFlag = !displayFlag;
}

int main(void){
    //configureAll(); //function to configure all (digital I/O, analog input, A/D module,
                    //timers T1 and T3, interrupts)

    //Timer 1
    T1CONbits.TCKPS = 3;
    PR1 = 19530;
    TMR1 = 0;
    T1CONbits.TON = 1;

    //Timer 3
    T3CONbits.TCKPS = 2;
    PR3 = 49999;
    TMR3 = 0;
    T3CONbits.TON = 1;

    //Interrupts Timer1
    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;

    //Interrupts Timer3
    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;

    //ADC
	IPC6bits.AD1IP = 2; 	// configure priority of A/D interrupts
	IEC1bits.AD1IE = 1; 	// enable A/D interrupts
	IFS1bits.AD1IF = 0; 	// clear A/D interrupt flag

    //Configure the A/D module and port RB4 as analog input
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = sample_num-1;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    //Configura 7seg display outputs
    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 1;

    TRISB = TRISB & 0x00FF;
    TRISD = TRISD & 0xFF9F;

    //Reset AD1IF, T1IF and T3IF flags

    EnableInterrupts();

    while(1);

    return 0;
}

void _int_(4) isr_T1(void){
    
    //start A/D conversion
    AD1CON1bits.ASAM = 1;

    //reset T1IF flag
    IFS0bits.T1IF = 0;
}

void _int_(12) isr_T3(void){
    
    //send voltage to displays
    send2displays(voltage);

    //reset T3IF flag
    IFS0bits.T3IF = 0;
}

void _int_(27) isr_adc(void){

    //calculate buffer average (8 samples)
    int volt = 0;

    int *p = (int *)(&ADC1BUF0);
    int i;
    for(i = 0; i < sample_num; i++){
        printInt(p[i*4], 10);
        volt += p[i*4];
        putChar(' ');
    }

    putChar('\n');

    //calculate voltage amplitude
    volt = volt / sample_num;

    //convert voltage amplitude to decimal. Copy it to "voltage"
    int V = (volt*33+511)/1023;
    int whole_part = V/10;
    int decimal_part = V % 10;

    voltage = (whole_part & 0x000F) << 4 | (decimal_part & 0x000F);

    IFS1bits.AD1IF = 0; //Reset AD1IF flag
}