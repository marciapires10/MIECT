# include <detpic32.h>

void delay(int ms);

int main(void){

    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 16-1;

    AD1CHSbits.CH0SA = 4;

    AD1CON1bits.ON = 1;

    while(1){

        AD1CON1bits.ASAM = 1;

        while(ISF1bits.AD1IF == 0);

        printInt(ADC1BUF0, 16 | 3 << 16);
        delay(500);

        IFS1bits.AD1IF = 0;

    }

    return 0;
}


void delay(int ms) {
	for(; ms > 0; ms--) {
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
} 