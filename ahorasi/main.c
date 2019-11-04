
#include <msp430.h>

//#include  <msp430g2553.h> // For the M430G2553 chip,

void main(void)
{
    //  https://e2e.ti.com/support/microcontrollers/msp430/f/166/t/185139?Turn-on-LED-with-button-Press-
    unsigned int i; // variable de retardo

    WDTCTL  =  WDTPW | WDTHOLD;               // stop watchdog timer
    P2REN  |=  0x08;
    P2OUT   =  0x08;
    P1DIR   =  0x01;
    P2DIR   =  0x00;

    while( 1 )
    {
        if( !(P2IN & 0x08) )
        {
            P1OUT ^= 0x01;
            for(i=30000; i==0; i--);
        }
    }
}
