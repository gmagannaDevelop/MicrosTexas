#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    P1DIR |= 0x01;              // programa P1 como salida (OR)
	P1DIR |= 0x40;              // programa P1 como salida (OR)


	for (;;)
	{
	    volatile unsigned int i, j, k;

	    P1OUT ^= 0x01;
	    for(i=100000; i>0; i--)
	        P1OUT ^= 0x40;
	        for(j=500000; j>0; j--);
	            //P1OUT ^= 0x01;

	}
	return 0;
}
