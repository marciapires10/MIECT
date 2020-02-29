# include <detpic32.h>

void send2displays(unsigned char value){

    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char trigger = 0;

    TRISB = (TRISB & 0x00FF);
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    char dh = value >> 4;
    char dl = value & 0x0F;

    if(trigger == 0){
        LATB = (LATB & 0x00FF) | (display7Scodes[dl] << 8);
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
    }
    else{
        LATB = (LATB & 0x00FF) | (display7Scodes[dh] << 8);
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
    }

    trigger = !trigger;






 // send digit_high (dh) to display_high: dh = value >> 4
 // send digit_low (dl) to display_low: dl = value & 0x0F
 }