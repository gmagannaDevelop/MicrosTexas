#include "msp430g2553.h"
#include <stdio.h>
 int main( void )
{
// Stop watchdog timer to prevent time out reset WDTCTL = WDTPW + WDTHOLD;

  P1DIR = 0x37;
  P2DIR = 0x01;
  int d = 0;
  ADC10CTL1 = (INCH_3 | SHS_0);     // Conf convertidor analogico-digital
  //printf("ALV WE : %d", ADC10CTL1);
  ADC10AE0  = 0x08;
  ADC10CTL0 = (SREF_0 | ADC10SHT_0 | ADC10ON);

  while(1)
  {
    ADC10CTL0 = (SREF_0 | ADC10SHT_0 | ADC10ON | ENC | ADC10SC);

    while((ADC10IFG&0x04)==0){}

    d=ADC10MEM;

    if((d>=0)&&(d<170))
    {
        P1OUT=0x01;
        P2OUT=0x00;
    }
    else if((d>=170)&&(d<340))
    {
        P1OUT=0x02;
        P2OUT=0x00;
    }
    else if((d>=340)&&(d<510))
    {
        P1OUT=0x04;
        P2OUT=0x00;
    }
    else if((d>=510)&&(d<680))
    {
        P1OUT=0x10;
        P2OUT=0x00;
    }
    else if((d>=680)&&(d<850))
    {
        P1OUT=0x20;
        P2OUT=0x00;
    }
    else
    {
        P1OUT=0x00;
        P2OUT=0x01;
    }

  } // end while
} // end main
