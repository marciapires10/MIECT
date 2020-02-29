// Contador Jonhson nos leds, aumentar a frequência através do ADC e inverter o sentido através do RB0. E ainda enviar para os displays a freq
// RB0 = 0 -> contador para a direita
// RB0 = 1 -> contador para a esquerda
// Frequência = ADC (0-1000);

# include <detpic32.h>

# define sample 8

volatile int voltage;

void send2displays(unsigned char str){

    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

    static char displayFlag = 0;

    TRISB = (TRISB & 0x00FF);
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    char dh = str >> 4;
    char dl = str & 0x0F;

    if(displayFlag == 0){
        LATB = ((LATB & 0x00FF) | display7Scodes[dl] << 8);
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
    }
    else{
        LATB = ((LATB & 0x00FF) | display7Scodes[dh] << 8);
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
    }

    displayFlag = !displayFlag;
}

void _int_(27) isr_adc(void){
    int i;
    int VAL_AD;

    int *p = (int *)(&ADC1BUF0);

    for(i=0; i < sample; i++){
        VAL_AD += p[i*4];
    }

    VAL_AD = VAL_AD/sample;

    voltage = ((VAL_AD*1000)+511)/1023;

    IFS1bits.AD1IF = 0;

}

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();

        while(readCoreTimer() < 20000);
    }
}

int main(void){

    //ADC

    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;

    AD1CON1bits.CLRASAM = 1;

    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = sample - 1;

    AD1CHSbits.CH0SA = 4;

    AD1CON1bits.ON = 1;

    //Interrupção ADC

    IPC6bits.AD1IP = 2;
    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;

    EnableInterrupts();

    // LEDS

    TRISB = (TRISB & 0xFFFE) | 0x0001;
    TRISE = (TRISE & 0xFFF0);
    //TRISB = (TRISB & 0xFFF0) | 0x0008;

    int led = 0;
    while(1){

        LATE = (LATE & 0xFFF0) | led;

        if(PORTBbits.RB0 == 0){
            if(LATEbits.LATE3 == 0){
                led = (led << 1) + 1;
            }
            else if(LATEbits.LATE3 == 1){
                led = (led << 1) & 0x000F;
            }
        }
        else if(PORTBbits.RB0 == 1){
            if(LATEbits.LATE0 == 0){
                led = (led >> 1) + 8;
            }
            else if(LATEbits.LATE0 == 1){
                led = (led >> 1);
            }
        }

        delay(voltage);
        // 0000  0001  0011  0111  1111 1110 1100 1000 0000
        // 0000 1000 1100 1110 1111 0111 0011 0001 0000

    }

    return 1;
}
