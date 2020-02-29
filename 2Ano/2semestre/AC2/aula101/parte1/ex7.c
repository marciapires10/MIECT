# include <detpic32.h>
# include "ex2.c"
# include "delay.c"

#define I2C_READ 1
#define I2C_WRITE 0
#define I2C_ACK 0
#define I2C_NACK 1

#define SENS_ADDRESS 0x4D // device dependent
#define ADDR_WR ((SENS_ADDRESS << 1) | I2C_WRITE)
#define ADDR_RD ((SENS_ADDRESS << 1) | I2C_READ)
#define TC74_CLK_FREQ 100000 // 100 KHz
#define RTR 0 // Read temperature command



int main(void){
    int ack, temperature;
    i2c1_init(TC74_CLK_FREQ);
 
    while(1){
    // Send Start event
    i2c1_start();

    // Send Address + WR (ADDR_WR); copy return value to "ack" variable
    ack = i2c1_send(ADDR_WR);

    // Send Command (RTR); add return value to "ack" variable
    ack += i2c1_send(RTR);

    // Send Start event (again)
    i2c1_start();

    // Send Address + RD (ADDR_RD); add return value to "ack" variable
    ack += i2c1_send(ADDR_RD);

    // Test "ack" variable; if "ack" != 0 then an error has occurred;
    // send the Stop event, print an error message and exit loop
    if(ack != 0){
        i2c1_stop();
        printStr("Error");
        break;
    }

    // Receive a value from slave (send NACK as argument); copy
    // received value to "temperature" variable
    temperature = i2c1_receive(I2C_NACK);

    // Send Stop event
    i2c1_stop();

    // Print "temperature" variable (syscall printInt10)
    printInt10(temperature);
    printStr("\n");

    // Wait 250 ms
    delay(250);
    }

    return 0;

 } 