# include <detpic32.h>
# include "send2displays.c"

volatile int voltage;
static int sample = 8;


int configureAll(void){

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
    //IEC0bits.T1IE = 1;
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
    AD1CON2bits.SMPI = sample-1;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;
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
    for(i = 0; i < sample; i++){
        printInt(p[i*4], 10);
        volt += p[i*4];
        putChar(' ');
    }

    putChar('\n');

    //calculate voltage amplitude
    volt = volt / sample;

    //convert voltage amplitude to decimal. Copy it to "voltage"
    int V = (volt*33+511)/1023;
    int whole_part = V/10;
    int decimal_part = V % 10;

    voltage = (whole_part & 0x000F) << 4 | (decimal_part & 0x000F);

    IFS1bits.AD1IF = 0; //Reset AD1IF flag
}

void setPWM (unsigned int dutyCycle){

    //duty_cycle must be in the range [0, 100]
    if(dutyCycle < 0 || dutyCycle > 100){
        dutyCycle = 50;
    }

    OC1RS = ((49999+1)*dutyCycle)/100; //evaluate OC1RS as a function of "dutyCycle"
}

int main(void){

    int dutyCycle;

    configureAll();
    
    EnableInterrupts();

    //Configura 7seg display outputs
    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 1;

    TRISB = TRISB & 0x00FF;
    TRISD = TRISD & 0xFF9F;

    OC1CONbits.OCM = 6;
    OC1CONbits.OCTSEL = 1;
    OC1CONbits.ON = 1;

    //Configure RB1 and RB0 as inputs
    TRISB = ((TRISB & 0xFFFC) | 0x0003);

    while(1){

        // Read RB1, RB0 to the variable portVal
        char portVal = PORTB & 0x0003;

        switch (portVal)
        {
        case 0: // measure input voltage
            IEC0bits.T1IE = 1;//Enable T1 interrupts
            setPWM(0); // LED OFF
            break;
        
        case 1: // Freeze
            IEC0bits.T1IE = 0;//Disable T1 interrupts
            setPWM(100); // LED ON (maximum bright)
            break;

        default: // LED brightness control
            IEC0bits.T1IE = 1;//Enable T1 interrupts
            dutyCycle = voltage * 3;
            setPWM(dutyCycle);
            break;
        }
    }

    return 0;
}