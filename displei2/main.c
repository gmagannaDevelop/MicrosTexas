/*******************************************************************************
 *
 * MSP-EXP430G2_007: Manejo de LCD 16x2 "Mostrar Textos"
 *
 *******************************************************************************
 * FileName:        lcd.c
 * Processor:       MSP430G2231 (Puede ser otro)
 * Complier:        CCS 7.2.0.00013
 * Author:          Pedro Sánchez Ramírez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Considerar la distribucion de pines especificada en lcd.h
 *          Forma de mostar textos simples en el LCD
 *******************************************************************************
 * Historial del firmware
 * Rev.     Date        Comment
 *  v0.00   28/09/2015  Creación del firmware
 *  v0.01   29/11/2017  Se compilo con CCS 7.2.0.00013
 ******************************************************************************/
#include <msp430.h>
#include "lcd.h"

void Delay_Seg(volatile unsigned int t);

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;//Stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ;// Use 1Mhz cal data for DCO
    DCOCTL = CALDCO_1MHZ;// Use 1Mhz cal data for DCO
    P1DIR = 0xFF;
    P1OUT = 0x00;
    LCD_Init();//Se inicializa LCD
    while(1)
    {

        LCD_WriteCommand(LCD_CLEAR_SCREEN);
        LCD_WriteROMString("El mejor profe" ,1,0);
        LCD_WriteROMString("Dr. Villa",0,1);
        Delay_Seg(3);
        LCD_WriteCommand(LCD_CLEAR_SCREEN);
        LCD_WriteROMString("Ya estamos",1,0);
        LCD_WriteROMString("exentos? <3",0,1);
        Delay_Seg(3);
    }
}

/*
 *
 *  ///Su main :
 *  LCD_WriteCommand(LCD_CLEAR_SCREEN);
        LCD_WriteROMString("Hello World!!",1,0);
        LCD_WriteROMString("by MrChunckuee!!",0,1);
        Delay_Seg(3);
        LCD_WriteCommand(LCD_CLEAR_SCREEN);
        LCD_WriteROMString("Using LCD 16x2",1,0);
        LCD_WriteROMString("Code Composer S.",0,1);
        Delay_Seg(3);
        LCD_WriteCommand(LCD_CLEAR_SCREEN);
        LCD_WriteROMString("Electr. y Robot.",0,0);
        LCD_WriteROMString("Likes FB: 5170",1,1);
        Delay_Seg(3);
        LCD_WriteCommand(LCD_CLEAR_SCREEN);
        LCD_WriteROMString("http://mrchuncku",0,0);
        LCD_WriteROMString("ee.blogspot.com/",0,1);
        Delay_Seg(3);
 *
 *
 *
 *
 *
 *
 * */


/*******************************************************************************
 * Function:        void Delay_Seg(volatile unsigned int t)
 * Description:     Realiza retardo en segundos
 * Precondition:    None
 * Parameters:      t = Tiempo de espera
 * Return Values:   None
 * Remarks:         None
 * ****************************************************************************/
void Delay_Seg(volatile unsigned int t){
    volatile unsigned int i;
    for (i=0 ;i<t; i++){
            __delay_cycles(1000000);
    }
}
