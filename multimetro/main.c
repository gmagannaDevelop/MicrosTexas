/*
 *  Univesridad de Guanajuato
 *  División de Ciencias e Ingenierías
 *
 *  Curso :  Arquitectura de microcontroladores.
 *  Profesor : Dr. Carlos Villaseñor Mora
 *  Alumnos :
 *      Jonathan Alejandro Gonzalez Pérez
 *      Uriel Moreno
 *      Gustavo Magaña López
 * */


#include <msp430g2553.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#include "special.h"

void Delay(volatile unsigned int t);

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;           // Stop watchdog timer √
    BCSCTL1 = CALBC1_1MHZ;              // Use 1Mhz cal data for DCO √
    DCOCTL = CALDCO_1MHZ;               // Use 1Mhz cal data for DCO √
    P1DIR = 0xFF;                       // P1 <- SALIDA
    P1DIR ^= 0x80;                      // Ponemos en cero el bit P1.6, para leer el voltaje.
    P1OUT = 0x00;                       //                                                      ??

    LCD_Init();                         // Se inicializa LCD

    P2DIR = 0x01;                       // P2 <- ENTRADA; P2.0 <- SALIDA
    /*
     * The ADC10 core is configured by two control registers, ADC10CTL0 and ADC10CTL1.
     * The core is enabled with the ADC10ON bit.
     * With few exceptions the ADC10 control bits can only be modified when ENC = 0.
     * ENC must be set to 1 before any conversion can take place.
     * */

    ADC10CTL1 = (                       // Configura convertidor analogico-digital
            INCH_6 |                    // INCH_N : Selects Channel N                        !!
            SHS_0                       // (0x0400) /* ADC10 Sample/Hold Source Bit: 0 */
    );

    /*
    ADC10 analog enable. These bits enable the corresponding pin for analog input. BIT0 corresponds to A0, BIT1 corresponds to A1, etc. The analog enable bit of not implemented channels should not be programmed to 1.
    0 Analog input disabled
    1 Analog input enabled
    */
    ADC10AE0  = 0x40;                   // P1.6 <- ENTRADA ANALÓGICA

    ADC10CTL0 = (                       // Configura convertidor analógico-digital
            SREF_0 |                    /* ADC10 Reference Select Bit: 0 */
            ADC10SHT_0 |                /* 4 x ADC10CLKs */
            ADC10ON                     /* ADC10 On/Enable */
    );

    int int_Value = 10;
    char char_LCD[16], i;
    int d = 0;
    //int mame;

    while(1)
    {
        ADC10CTL0 = (
                SREF_0     |     /* ADC10 Reference Select Bit: 0 */
                ADC10SHT_0 |     /* VALUE = (0*0x800u) ; 4 x ADC10CLKs */
                ADC10ON    |     /* ADC10 On/Enable */
                ENC        |     /* ADC10 Enable Conversion */
                ADC10SC          /* ADC10 Start Conversion */
        );

            while((ADC10IFG&0x04)==0){}
            LCD_WriteCommand(LCD_CLEAR_SCREEN);

            d=ADC10MEM;
            d *= 4;
            d /= 1023;


            for(i=0; i<16; i++){ char_LCD[i]=0; }   // Clear char_LCD
            itoa(d, char_LCD, 10);                  // Pasar int_Value a decimal
            //snprintf(char_LCD, 16, "%f", d);
            LCD_WriteROMString("Voltaje:",0,0);
            LCD_WriteString(char_LCD,0,1);
            Delay(50);                              // Centésimas de segundo


            /*
            if((d>=0)&&(d<170))
            {
                LCD_WriteCommand(LCD_CLEAR_SCREEN);
                LCD_WriteROMString("Voltaje:",1,0);
                LCD_WriteROMString("||",0,1);
                Delay_centSeg(50);
            }
            else if((d>=170)&&(d<340))
            {
                LCD_WriteCommand(LCD_CLEAR_SCREEN);
                LCD_WriteROMString("Voltaje:",1,0);
                LCD_WriteROMString("|||",0,1);
                Delay_centSeg(50);
            }
            else if((d>=340)&&(d<510))
            {
                LCD_WriteCommand(LCD_CLEAR_SCREEN);
                LCD_WriteROMString("Voltaje:",1,0);
                LCD_WriteROMString("||||",0,1);
                Delay_centSeg(50);
            }
            else if((d>=510)&&(d<680))
            {
                LCD_WriteCommand(LCD_CLEAR_SCREEN);
                LCD_WriteROMString("Voltaje:",1,0);
                LCD_WriteROMString("|||||",0,1);
                Delay_centSeg(50);
            }
            else if((d>=680)&&(d<850))
            {
                LCD_WriteCommand(LCD_CLEAR_SCREEN);
                LCD_WriteROMString("Voltaje:",1,0);
                LCD_WriteROMString("||||||",0,1);
                Delay_centSeg(50);
            }
            else
            {
                LCD_WriteCommand(LCD_CLEAR_SCREEN);
                LCD_WriteROMString("Voltaje:",1,0);
                LCD_WriteROMString("NADA",0,1);
                Delay_centSeg(50);
            }
           */
           } //end while

} // end main


void Delay(volatile unsigned int t)
{
    /*
     * Delay utilizando ciclos del micro.
     * Cambiar el número dentro de
     * __delay_cycles(n) para modificar el comportamiento:
     *      n : 10000   -> Centésimas de segundo
     *      n : 100000  -> Décimas de segundo.
     *      n : 1000000 -> Segundos.
     */
    volatile unsigned int i;
    for (i=0 ;i<t; i++){
            __delay_cycles(10000);
    }
}

