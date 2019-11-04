#include <msp430.h> 
#include <time.h>
// Definicion de funciones :
void delayMS(int msecs);
void retardo(int milisegundos);

unsigned int OFCount;

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;               // stop watchdog timer
	P1DIR |= BIT0 | BIT1 | BIT2 | BIT4;     // Configure P1.0, 1, 2, 4 as outputs
	//P1DIR &= ~BIT1;                       // Configure P1.3 as Input
	P1DIR &= ~BIT3 ;                        //explicitly making P1.3 as Input - even though by default its Input
	P1REN = BIT3;                           //Enable Pullup/down
	P1OUT = BIT3;                           //Select Pullup

    P1OUT = 0x00;
    while(1)
    {
         // esto ya jala :      if( !(P1IN & BIT3) )                //Evaluates to True for a 'LOW' on P1.3


        while( !(P1IN & BIT3) )                //Evaluates to True for a 'LOW' on P1.3
        {
            P1OUT = 0x02;
            //delayMS(2000);
            //_delay_ms(20);
            //P1OUT ^= BIT0;                  //Toggle the state of P1.6
            //retardo(50000);
            //while( !(P1IN & BIT3) );        //wait until button is released
        }
        P1OUT = 0x00;
    }

}


void retardo(int milisegundos)
{
    int i, sinsentido;

    for (i=milisegundos; i==0; i--)
    {
        sinsentido = i;
    }
}



/*
 *
 *  void delayMS(int msecs)
{
    int i;
    i = 0;
    OFCount = 0; //Reset Over-Flow counter
    TACCR0 = 1000-1; //Start Timer, Compare value for Up Mode to get 1ms delay per loop
    //Total count = TACCR0 + 1. Hence we need to subtract 1.

    while(i<=msecs)
        i--;

    TACCR0 = 0; //Stop Timer
}
 *
 *
    P1OUT = 0x00;
    while(1)
    {
         // esto ya jala :      if( !(P1IN & BIT3) )                //Evaluates to True for a 'LOW' on P1.3

        if( !(P1IN & BIT3) )                //Evaluates to True for a 'LOW' on P1.3
        {
            //delayMS(2000);
            //_delay_ms(20);
            P1OUT ^= BIT0;                  //Toggle the state of P1.6
            //while( (P1IN & BIT3) );        //wait until button is released
        }



         // esto no jala :(
        if( !(P1IN & BIT3) )                //Evaluates to True for a 'LOW' on P1.3
        {
            i++;
            //__delay(50);
            delayMS(50);
            while( !(P1IN & BIT3) );        //wait until button is released

        }

        if (i == 1)
            P1OUT ^= BIT0;                  //Toggle the state of P1.0

        if (i == 2)
            P1OUT ^= BIT1;                  //Toggle the state of P1.1

        if (i == 3)
            P1OUT ^= BIT2;                  //Toggle the state of P1.2

        if (i == 4)
            P1OUT ^= BIT4;                  //Toggle the state of P1.4

        if (i == 5)
        {
            i = 0;
            P1OUT = 0x00;
        }

    }

    // return 0;
 *
 *
 *
 *
 *
 */



/*
 *  int i;
    i = 0;

    P1OUT = 0x00;
    while(1)
    {


         // esto no jala :(

        if( !(P1IN & BIT3) )                //Evaluates to True for a 'LOW' on P1.3
        {
            while( !(P1IN & BIT3) );        //wait until button is released
            i++;
        }


        while( !(P1IN & BIT3) )        //wait until button is released
            i++;

        if (i == 1)
            P1OUT = 0x01;                  //Toggle the state of P1.0

        if (i == 2)
            P1OUT = 0x02;                  //Toggle the state of P1.1

        if (i == 3)
            P1OUT = 0x04;                  //Toggle the state of P1.2

        if (i == 4)
            P1OUT = 0x10;                  //Toggle the state of P1.4

        if (i == 5)
        {
            i = 0;
            P1OUT = 0x00;
        }

    }

    // return 0;
 *
 *
 *
 * */
