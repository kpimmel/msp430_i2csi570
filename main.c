#include <msp430.h>
#include "serial.h"
#include "i2c.h"

void kpprintf(char *format, ...);


void main(void)
{
    char c;
    char dev_address = 0xAA;
    int i;

    // Disable watchdog 
    WDTCTL = WDTPW + WDTHOLD;

    // Use 1 MHz DCO factory calibration
    DCOCTL = 0;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
            
    // Setup the serial port
    // Serial out: P1.1 (BIT1)
    // Serial in:  P1.2 (BIT2)
    // Bit rate:   9600 (CPU freq / bit rate)  
    serial_setup (BIT1, BIT2, 1000000 / 9600);
    
    kpprintf("serial is working...\r\n");
    char err;

    char i2cWriteBuf[] = {0, 0, 0, 0, 0, 0};
    int j;

    // Hard reset of frequency to 14.2 MHz
    i2cWriteBuf[0]=0xA9 ; 
    i2cWriteBuf[1]=0xC2; 
    i2cWriteBuf[2]=0xA8 ; 
    i2cWriteBuf[3]=0x7C ; 
    i2cWriteBuf[4]=0x5D ; 
    i2cWriteBuf[5]=0x39; 
		kpprintf("14.2 MHz\r\n");

    kpprintf("init i2c...\r\n");
		i2c_init();
		__delay_cycles(20000);

      
    //Freeze DCO
    kpprintf("Freeze DCO...\r\n");
    u8 buf;
    buf = 0b00010000;
    i2c_tx(1, dev_address, &buf, 0, 135); 

    kpprintf("Write buffer...\r\n");
    for (i = 0; i < 6 ; ++i) 
    { 
      i2c_tx(1, dev_address, i2cWriteBuf, 0, i+8); 
    }
    //Unfreeze DCO  
    kpprintf("Unfreeze DCO...\r\n");
    buf = 0;
    i2c_tx(1, dev_address, &buf, 0, 135); 
    
    kpprintf("Read input from serial...\r\n");
    for (;;) {                  // Do forever
      c = serial_getc ();     // Get a char
      serial_putc (c);        // Echo it back
    }
}
