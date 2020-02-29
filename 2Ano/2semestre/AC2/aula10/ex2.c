#include <detpic32.h>

void i2c1_init(unsigned int clock_freq){
    //Config baudrate generator 
    I2C1BRG = (PBCLK + clock_freq) / (2 * clock_freq) - 1; //final da pág2 do guião

    //Enable I2C1 module
    I2C1CONbits.ON = 1;
}

void i2c1_start(void){
    //Wait until the lower 5 bits of I2CxCON are all 0 (the lower 5 bits of I2CxCON
    //must be 0 before attempting to set the SEN bit)
    while((I2C1CON & 0x001F) != 0);

    //Activate Start event (I2C1CON, bit SEN)
    I2C1CONbits.SEN = 1;

    //Wait for completion of the Start event (I2C1CON, bit SEN)
    while(I2C1CONbits.SEN == 1);
}

void i2c1_stop(void){
    //Wait until the lower 5 bits of I2CxCON are all 0 (the lower 5 bits of I2CxCON
    //must be 0 before attempting to set the PEN bit)
    //Activate Stop event (I2C1CON, bit PEN)
    //Wait for completion of the Stop event (I2C1CON, bit PEN)
}