// # include <detpic32.h>
// # include "send2displays.c"

// volatile int voltage;
// volatile int value2display;
// static int sample = 8;

// volatile int min_voltage = 35;
// volatile int max_voltage = 0;

// void putc(char byte2send){
//     while(U1STAbits.UTXBF == 1);

//     U1TXREG = byte2send;
// }

// void puts(char *str){
//     //use putc() function to send each character ('\0' should not be sent)
//     while(*str != '\0'){
//         putc(*str++);
//     }
// }


// void _int_(4) isr_T1(void){
    
//     //start A/D conversion
//     AD1CON1bits.ASAM = 1;

//     //reset T1IF flag
//     IFS0bits.T1IF = 0;
// }

// void _int_(12) isr_T3(void){

//     static int counter = 0;
    
//     //send voltage to displays
//     send2displays(value2display);
//     if(++counter == 100){
//         counter = 0;
//         putc(voltage);
//     }

//     //reset T3IF flag
//     IFS0bits.T3IF = 0;
// }

// void _int_(24) isr_uart1(void){

//     //putc(U1RXREG);
//     if(U1RXREG == 'L'){
//         putc(min_voltage);
//         putc(' ');
//         putc(max_voltage);
//     }

//     //Clear UART1 rx interrupt flag
//     IFS0bits.U1RXIF = 0;

// }

// void _int_(27) isr_adc(void){

//     //calculate buffer average (8 samples)
//     int volt = 0;

//     int *p = (int *)(&ADC1BUF0);
//     int i;
//     for(i = 0; i < sample; i++){
//         //printInt(p[i*4], 10);
//         volt += p[i*4];
//         //putChar(' ');
//     }

//     //putChar('\n');

//     //calculate voltage amplitude
//     volt = volt / sample;

//     //convert voltage amplitude to decimal. Copy it to "voltage"
//     int voltage = (volt*33+511)/1023;
//     int whole_part = voltage/10;
//     int decimal_part = voltage % 10;

//     value2display = (whole_part & 0x000F) << 4 | (decimal_part & 0x000F);

//     if(voltage < min_voltage){
//         min_voltage = voltage;
//     }

//     if(voltage > max_voltage){
//         max_voltage = voltage;
//     }

//     IFS1bits.AD1IF = 0; //Reset AD1IF flag
// }

// void setPWM (unsigned int dutyCycle){

//     //duty_cycle must be in the range [0, 100]
//     if(dutyCycle < 0 || dutyCycle > 100){
//         dutyCycle = 50;
//     }

//     OC1RS = ((49999+1)*dutyCycle)/100; //evaluate OC1RS as a function of "dutyCycle"
// }

// int configureUART1(unsigned int baud, char parity, unsigned int stopbits){
//     //Configure UART1:

//     //1 - Configure BaudRate Generator
//     if(baud < 600 || baud > 115200){
//         baud = 115200;
//     }
//     U1BRG = ((PBCLK + 8*baud)/(16*baud))-1;
//     U1MODEbits.BRGH = 0; //fator de divisão é  16

//     //2 - Configure number of data bits, parity and number of stop bits
//     if(parity == 'E'){
//         U1MODEbits.PDSEL = 01;
//     }
//     else if(parity == 'O'){
//         U1MODEbits.PDSEL = 10;
//     }
//     else{
//         U1MODEbits.PDSEL = 00;
//     }
//     if(stopbits == 2){
//         U1MODEbits.STSEL = 1; // 2 stop bit
//     }
//     else{
//         U1MODEbits.STSEL = 0; // 1 stop bit
//     }

//     //3 - Enable the transmitter and receiver modules
//     U1STAbits.UTXEN = 1; //transmission module
//     U1STAbits.URXEN = 1; //reception module

//     //4 - Enable UART1
//     U1MODEbits.ON = 1;
// }

// int configureAll(void){

//     configureUART1(115200, 'N', 1);

//     //Timer 1
//     T1CONbits.TCKPS = 3;
//     PR1 = 19530;
//     TMR1 = 0;
//     T1CONbits.TON = 1;

//     //Timer 3
//     T3CONbits.TCKPS = 2;
//     PR3 = 49999;
//     TMR3 = 0;
//     T3CONbits.TON = 1;

//     //Interrupts Timer1
//     IPC1bits.T1IP = 2;
//     //IEC0bits.T1IE = 1;
//     IFS0bits.T1IF = 0;

//     //Interrupts Timer3
//     IPC3bits.T3IP = 2;
//     IEC0bits.T3IE = 1;
//     IFS0bits.T3IF = 0;

//     //ADC
// 	IPC6bits.AD1IP = 2; 	// configure priority of A/D interrupts
// 	IEC1bits.AD1IE = 1; 	// enable A/D interrupts
// 	IFS1bits.AD1IF = 0; 	// clear A/D interrupt flag

//     //Configure the A/D module and port RB4 as analog input
//     TRISBbits.TRISB4 = 1;
//     AD1PCFGbits.PCFG4 = 0;
//     AD1CON1bits.SSRC = 7;
//     AD1CON1bits.CLRASAM = 1;

//     AD1CON3bits.SAMC = 16;
//     AD1CON2bits.SMPI = sample-1;
//     AD1CHSbits.CH0SA = 4;
//     AD1CON1bits.ON = 1;
// }

// int main(void){

//     configureAll();
    
//     EnableInterrupts();

//     //Configura 7seg display outputs
//     LATDbits.LATD5 = 0;
//     LATDbits.LATD6 = 1;

//     TRISB = TRISB & 0x00FF;
//     TRISD = TRISD & 0xFF9F;


//     //Configure RB1 and RB0 as inputs
//     TRISB = ((TRISB & 0xFFFC) | 0x0003);

//     int dutyCycle;

//     while(1){

//         // Read RB1, RB0 to the variable portVal
//         char portVal = PORTB & 0x0003;

//         switch (portVal)
//         {
//         case 0: // measure input voltage
//             IEC0bits.T1IE = 1;//Enable T1 interrupts
//             setPWM(0); // LED OFF
//             break;
        
//         case 1: // Freeze
//             IEC0bits.T1IE = 0;//Disable T1 interrupts
//             setPWM(100); // LED ON (maximum bright)
//             break;

//         default: // LED brightness control
//             IEC0bits.T1IE = 1;//Enable T1 interrupts
//             dutyCycle = voltage * 3;
//             setPWM(dutyCycle);
//             break;
//         }
//     }

//     return 0;
// }

# include <detpic32.h>
# include "send2displays.c"

volatile int voltage;
static int sample = 8;

volatile int value2display;

volatile int min_voltage = 35;
volatile int max_voltage = 0;

void putc(char byte2send){
    while(U1STAbits.UTXBF == 1);

    U1TXREG = byte2send;
}

void puts(char *str){
    //use putc() function to send each character ('\0' should not be sent)
    while(*str != '\0'){
        putc(*str++);
    }
}

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
    static int counter = 0;
    //send voltage to displays
    send2displays(value2display);

    if(++counter == 100){
        counter = 0;
        putc(voltage);
    }
    //reset T3IF flag
    IFS0bits.T3IF = 0;
}

void _int_(27) isr_adc(void){

    //calculate buffer average (8 samples)
    int volt = 0;

    int *p = (int *)(&ADC1BUF0);
    int i;
    for(i = 0; i < sample; i++){
        //printInt(p[i*4], 10);
        volt += p[i*4];
        //putChar(' ');
    }

    //putChar('\n');

    //calculate voltage amplitude
    volt = volt / sample;

    //convert voltage amplitude to decimal. Copy it to "voltage"
    int voltage = (volt*33+511)/1023;
    int whole_part = voltage/10;
    int decimal_part = voltage % 10;

    value2display = (whole_part & 0x000F) << 4 | (decimal_part & 0x000F);

    if(voltage < min_voltage){
        min_voltage = voltage;
    }

    if(voltage > max_voltage){
        max_voltage = voltage;
    }

    IFS1bits.AD1IF = 0; //Reset AD1IF flag
}

void _int_(24) isr_uart1(void){
    //putc(U1RXREG);

    if(U1RXREG == 'L'){
        putc((min_voltage/10) + 0x30);
        putc(' ');
        putc((max_voltage/10) + 0x30);
    }

    //Clear UART1 rx interrupt flag
    IFS0bits.U1RXIF = 0;
}

void setPWM (unsigned int dutyCycle){

    //duty_cycle must be in the range [0, 100]
    if(dutyCycle < 0 || dutyCycle > 100){
        dutyCycle = 50;
    }

    OC1RS = ((49999+1)*dutyCycle)/100; //evaluate OC1RS as a function of "dutyCycle"
}

int configureUART1(unsigned int baud, char parity, unsigned int stopbits){
    //Configure UART1:

    //1 - Configure BaudRate Generator
    if(baud < 600 || baud > 115200){
        baud = 115200;
    }
    U1BRG = ((PBCLK + 8*baud)/(16*baud))-1;
    U1MODEbits.BRGH = 0; //fator de divisão é  16

    //2 - Configure number of data bits, parity and number of stop bits
    if(parity == 'E'){
        U1MODEbits.PDSEL = 01;
    }
    else if(parity == 'O'){
        U1MODEbits.PDSEL = 10;
    }
    else{
        U1MODEbits.PDSEL = 00;
    }
    if(stopbits == 2){
        U1MODEbits.STSEL = 1; // 2 stop bit
    }
    else{
        U1MODEbits.STSEL = 0; // 1 stop bit
    }

    //3 - Enable the transmitter and receiver modules
    U1STAbits.UTXEN = 1; //transmission module
    U1STAbits.URXEN = 1; //reception module

    // Enable Interrupts
    U1STAbits.URXISEL = 00;
    U1STAbits.URXEN = 1;

    IEC0bits.U1RXIE = 1;
    IEC0bits.U1EIE = 1;

    IFS0bits.U1RXIF = 0;
    IFS0bits.U1EIF = 0;

    IPC6bits.U1IP = 2;
    
    //4 - Enable UART1
    U1MODEbits.ON = 1;
}

int main(void){

    int dutyCycle;

    configureAll();

    configureUART1(115200,'N',1);
    
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