# include <detpic32.h>

//ex2
void i2c1_init(unsigned int clock_freq){

    //Config baudrate generator
    I2C1BRG = (PBCLK + clock_freq) / (2 * clock_freq) - 1;


    //Enable I2C1 module
    I2C1CONbits.ON = 1;
}

//ex3

void i2c1_start(void){
    //Wait until the lower 5 bits of I2CxCON are all 0 
    while((I2C1CON & 0x001F) != 0);

    //Activate start event (I2C1CON, bit SEN)
    I2C1CONbits.SEN = 1;

    //Wait for completion of the start event (I2C1CON, bit SEN)
    while(I2C1CONbits.SEN == 1);

}

//ex4

void i2c1_stop(void){
    //Wait until the lower 5 bits of I2CxCON are all 0
    while((I2C1CON & 0x001F) != 0);

    //Activate stop event (I2C1CON, bit PEN)
    I2C1CONbits.PEN = 1;

    //Wait for completion of the stop event (I2C1CON, bit PEN)
    while(I2C1CONbits.PEN == 1);

}

//ex5

int i2c1_send(unsigned char value){
    //Copy "value" to I2C1TRN register
    I2C1TRN = value;

    //Wait while master transmission is in progress
    while(I2C1STATbits.TRSTAT == 1);

    //Return acknowledge status bit 
    return I2C1STATbits.ACKSTAT;
}

//ex6

char i2c1_receive(char ack_bit){
    // Wait util the lower 5 bits of I2C1CON are all 0 (the lower 5 bits
    // of I2C1CON must be 0 before attempting to set the RCEN bit)
    while((I2C1CON & 0x001F) != 0);

    // Activate RCEN bit (receive enable bit, I2C1CON register)
    I2C1CONbits.RCEN = 1;

    // Wait while byte not received (I2C1STAT, bit RBF – receive buffer
    // full status bit)
    while(I2C1STATbits.RBF == 0);

    // Send ACK / NACK bit. For that:
    // 1. Copy "ack_bit" to I2C1CON, bit ACKDT (be sure "ack_bit" value
    // is only 0 or 1)
    I2C1CONbits.ACKDT = ack_bit;

    // 2. Wait until the lower 5 bits of I2C1CON are all 0 (the lower
    // 5 bits of I2C1CON must be 0 before attempting to
    // set the ACKEN bit.
    while((I2C1CON & 0x001F) != 0);

    // 3. Start Acknowledge sequence (I2C1CON register, bit ACKEN=1)
    I2C1CONbits.ACKEN = 1;

    // Wait for completion of Acknowledge sequence (I2C1CON, bit ACKEN)
    while(I2C1CONbits.ACKEN == 1);

    // Return received value (I2C1RCV)
    return I2C1RCV;
}
