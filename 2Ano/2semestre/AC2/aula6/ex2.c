# include <detpic32.h>
# include "send2displays.c"

volatile unsigned char voltage = 0; // global variable
void delay(int ms);

void _int_(27) isr_adc(void){
    int i;

    // Calculate buffer average (8 samples)
    // Calculate voltage amplitude
    // Convert voltage amplitude to decimal. Assign it to "voltage"
			 
	// Read conversion result (ADC1BUF0 value) and print it
	int VAL_AD = 0;
	int *p = (int *)(&ADC1BUF0);
	for( i = 0; i < 8; i++ ) {
		VAL_AD += p[i*4];
	} 

	VAL_AD = VAL_AD / 8;
	voltage = (VAL_AD*33+511)/1023;
		
	// Reset AD1IF
	IFS1bits.AD1IF = 0;


}


int main(void){

    unsigned int cnt = 0;

    //Configure all (digital I/O, analog input, A/D module)

    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 8-1;

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


    while(1){
        if(cnt % 25 == 0){ //250 ms (4 samples/second)
            //Start A/D conversion 
            AD1CON1bits.ASAM = 1;
        }

        //Send voltage variable to displays
        send2displays(voltage);

        cnt++;

        delay(10);
    }

    return 0;

}

void delay(int ms) {
	for(; ms > 0; ms--) {
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}