
#include <msp430g2553.h>
#include "lcd.h"
#include "special.h"

void Delay_centSeg(volatile unsigned int t);

void main(void) {
    WDTCTL = WDTPW + WDTHOLD;//Stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ;// Use 1Mhz cal data for DCO
    DCOCTL = CALDCO_1MHZ;// Use 1Mhz cal data for DCO
    P1DIR = 0xFF;
    P1DIR ^= 0x80;  // Ponemos en cero el bit P1.6, para leer el voltaje.
    P1OUT = 0x00;
    LCD_Init();//Se inicializa LCD
    //P1DIR = 0x40;
    P2DIR = 0x01;
    ADC10CTL1 = (INCH_3 | SHS_0);     // Conf convertidor analogico-digital
    //ADC10AE0  = 0x08;
    ADC10AE0  = 0x40;
    ADC10CTL0 = (SREF_0 | ADC10SHT_0 | ADC10ON);

    int int_Value = 10;
    char char_LCD[16], i;
    int d = 0;
    //int mame;

    while(1){


        ADC10CTL0 = (SREF_0 | ADC10SHT_0 | ADC10ON | ENC | ADC10SC);

            while((ADC10IFG&0x04)==0){}
            LCD_WriteCommand(LCD_CLEAR_SCREEN);

            d=ADC10MEM;
            //mame = 10 * d / 850;

            for(i=0; i<16; i++){ char_LCD[i]=0; } //Clear char_LCD
            itoa(d, char_LCD, 10); //Pasar int_Value a decimal
            LCD_WriteROMString("Voltaje:",0,0);
            LCD_WriteString(char_LCD,0,1);
            Delay_centSeg(10);

            /*
            if((d>=0)&&(d<170))
            {
                LCD_WriteCommand(LCD_CLEAR_SCREEN);
                LCD_WriteROMString("Voltaje:",1,0);
                LCD_WriteROMString("",0,1);
                Delay_Seg(3);
            }
            else if((d>=170)&&(d<340))
            {
                LCD_WriteCommand(LCD_CLEAR_SCREEN);
                LCD_WriteROMString("Voltaje:",1,0);
                LCD_WriteROMString("~~",0,1);
                Delay_Seg(3);
            }
            else if((d>=340)&&(d<510))
            {
                LCD_WriteCommand(LCD_CLEAR_SCREEN);
                LCD_WriteROMString("Voltaje:",1,0);
                LCD_WriteROMString("~",0,1);
                Delay_Seg(3);
            }
            else if((d>=510)&&(d<680))
            {
                LCD_WriteCommand(LCD_CLEAR_SCREEN);
                LCD_WriteROMString("Voltaje:",1,0);
                LCD_WriteROMString("~~",0,1);
                Delay_Seg(3);
            }
            else if((d>=680)&&(d<850))
            {
                LCD_WriteCommand(LCD_CLEAR_SCREEN);
                LCD_WriteROMString("Voltaje:",1,0);
                LCD_WriteROMString("~~~",0,1);
                Delay_Seg(3);
            }
            else
            {
                LCD_WriteCommand(LCD_CLEAR_SCREEN);
                LCD_WriteROMString("Voltaje:",1,0);
                LCD_WriteROMString("NADA",0,1);
                Delay_Seg(3);
            }
           */
           } //end while

          } // end main


void Delay_centSeg(volatile unsigned int t){
    volatile unsigned int i;
    for (i=0 ;i<t; i++){
            __delay_cycles(10000);
    }
}
