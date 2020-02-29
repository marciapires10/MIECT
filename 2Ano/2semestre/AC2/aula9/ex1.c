# include <detpic32.h>
# include "configUART1.c"

# define DisableUart1RxInterrupt() IEC0bits.U1RXIE = 0
# define EnableUart1RxInterrupt() IEC0bits.U1RXIE = 1
# define DisableUart1TxInterrupt() IEC0bits.U1TXIE = 0
# define EnableUart1TxInterrupt() IEC0bits.U1TXIE = 1
# define TRUE 1
# define FALSE 0

# define BUF_SIZE 8
# define INDEX_MASK (BUF_SIZE - 1)

typedef struct{
    unsigned char data[BUF_SIZE];
    unsigned int head;
    unsigned int tail;
    unsigned int count;
}

circularBuffer;

volatile circularBuffer txb; //Transmission buffer
volatile circularBuffer rxb; //Reception buffer


void comDrv_flushRx(void){
    //initialize variables of the reception buffer
    rxb.head = 0;
    rxb.tail = 0;
    rxb.count = 0;
}

void comDrv_flushTx(void){
    //Initialize variables of the transmission buffer
    txb.head = 0;
    txb.tail = 0;
    txb.count = 0;
}


void comDrv_putc(char ch){

    while(txb.count == BUF_SIZE){} //Wait while buffer is full

    txb.data[txb.tail] = ch; //Copy character to the transmission
                             //buffer at position "tail"

    txb.tail = (txb.tail + 1) & INDEX_MASK;

    DisableUart1TxInterrupt(); //Begin of critical section

    txb.count = txb.count + 1; //Increment "count" variable

    EnableUart1TxInterrupt(); //End of critical section
}

void comDrv_puts(char *s){

    while(*s != '\0'){
        comDrv_putc(*s);
        s++;
    }
}

void _int_(24) isr_uart1(void){
    if(IFS0bits.U1TXIF == 1){ //if U1TXIF is set
    if(txb.count > 0){ // if "count" variable is greater than 0
        U1TXREG = txb.data[txb.head]; //copy character pointed by "head" to U1TXREG register
        txb.head = (txb.head + 1) & INDEX_MASK; //increment "head" variable 
        txb.count = txb.count - 1; //decrement "count" variable
    }

    if(txb.count == 0){ //if "count" variable is 0 then
        DisableUart1TxInterrupt(); 
    }

    IFS0bits.U1TXIF = 0; //Reset UART1 TX interrupt flag


    }

    //If U1RXIF is set
    if(IFS0bits.U1RXIF == 1){
    rxb.data[rxb.tail] = U1RXREG; //Read character from UART and
                                  //write it to "tail" position
                                  //of the reception buffer
    
    rxb.tail = (rxb.tail + 1) & INDEX_MASK; //Increment "tail" variable

    //If reception buffer is not full then increment "count" variable
    if(rxb.count < BUF_SIZE){
        rxb.count = rxb.count + 1;
    }
    else{
        rxb.head = rxb.head + 1; //increment "head" variable (discard oldest character)
    }

    //reset UART1 RX interrupt flag
    IFS0bits.U1RXIF = 0;
}

}

void comDrv_config(unsigned int baudrate, char parity, unsigned int numStopBits){
    configUART1(baudrate, 8, parity, numStopBits);
}

char comDrv_getc(char *pchar){

    //Test "count" variable and return FALSE if it is zero

    if(rxb.count == 0){
        return FALSE;
    }

    DisableUart1RxInterrupt(); //Begin of critical section

    //Copy character pointed by "head" to *pchar
    *pchar = rxb.data[rxb.head];

    //Decrement "count" variable
    rxb.count = rxb.count - 1;

    //Increment "heda" variable (mod BUF_SIZE)
    rxb.head  = (rxb.head + 1) & INDEX_MASK;

    EnableUart1RxInterrupt();

    return TRUE;
}

//changed by ex10
int main(void){

    comDrv_config(115200, 'N', 1); //default pterm parameters
                                   //with TX and RX interrupts disabled
    
    

    comDrv_flushRx();
    comDrv_flushTx();
    EnableInterrupts();

    DisableUart1TxInterrupt();

    comDrv_puts("PIC32 UART Device-driver\n");

    char aux;

    while(1){
        if(comDrv_getc(&aux)){
            comDrv_putc(aux);
        }
        
        //comDrv_puts("Teste do bloco de transmissao do device driver!...");
    }

    return 0;
}



