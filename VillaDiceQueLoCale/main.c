#include "msp430g2553.h"
//#include <stdio.h>

void my_delay(int n);
int multiplica(int a, int b);

int main( void )
{
// Stop watchdog timer to prevent time out reset WDTCTL = WDTPW + WDTHOLD;

  P1DIR = 0x37;
  P2DIR = 0x01;
  int i = 0, n = 0, d = 0;
  ADC10CTL1 = (INCH_3 | SHS_0);     // Conf convertidor analogico-digital
  //printf("ALV WE : %d", ADC10CTL1);
  ADC10AE0  = 0x08;
  ADC10CTL0 = (SREF_0 | ADC10SHT_0 | ADC10ON);

  while(1)
  {
    ADC10CTL0 = (SREF_0 | ADC10SHT_0 | ADC10ON | ENC | ADC10SC);

    d=ADC10MEM;

    //while((ADC10IFG&0x04)==0){}
    //for (i=100*d; i>0; i--)
    //{
        P1OUT=0x01;
        my_delay(30);
        P1OUT=0x02;
        my_delay(30);
        P1OUT=0x04;
        my_delay(3);
        P1OUT=0x10;
        my_delay(3);
        P1OUT=0x20;
        my_delay(3);
        P1OUT=0x00;
        my_delay(3);
    //}

    /*
    n++;

    if((n>=0)&&(n<170))
    {
        P1OUT=0x01;
        P2OUT=0x00;
    }
    else if((n>=170)&&(n<340))
    {
        P1OUT=0x02;
        P2OUT=0x00;
    }
    else if((n>=340)&&(n<510))
    {
        P1OUT=0x04;
        P2OUT=0x00;
    }
    else if((n>=510)&&(n<680))
    {
        P1OUT=0x10;
        P2OUT=0x00;
    }
    else if((n>=680)&&(n<850))
    {
        P1OUT=0x20;
        P2OUT=0x00;
    }
    else
    {
        n = 0;
        P1OUT=0x00;
        P2OUT=0x01;
    }
    */

  } // end while
} // end main

int multiplica(int a, int b)
{
    int i, c;
    c = 0;
    for (i=b; i>0; i--)
        c += a;

    return c;
}


void my_delay(int n)
{
    int i, j;
    j = multiplica(4000, n);
    for (i=j; i>0; i--){}
    return;
}

