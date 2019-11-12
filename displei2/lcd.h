/*******************************************************************************
 *
 *                       Libreria para LCD
 *
 *******************************************************************************
 * FileName:        lcd.h
 * Processor:       MSP430G2231 (Puede ser otro)
 * Complier:        CCS 6.0.0
 * Author:          Jose Manuel Alvarado Farias, versi�n para PIC
 * 					Pedro S�nchez Ram�rez (MrChunckuee) versi�n para MSP430
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

//Incluimos el microcontrolador utilizado
#include <msp430g2553.h>

/*******************************************************************************
 * Perfil de hardware para el LCD
 * Pin	Nombre		MSP430
 * 	4	R/S			P1.4
 * 	6	EN			P1.5
 * 	11	Data4		P1.0
 * 	12	Data5		P1.1
 * 	13	Data6		P1.2
 * 	13	Data7		P1.3
 *
 * 	Cambiar la distribucion de pines implica variar secciones de codigo
 *******************************************************************************/
#define	RS BIT4
#define EN BIT5

#define	LCD_OFF             8
#define LCD_ON              12
#define	LCD_CURSOR_ON       14
#define	LCD_CURSOR_OFF      12
#define	LCD_CURSOR_BLINK    15
#define	LCD_CURSOR_NOBLINK  14
#define	LCD_CLEAR_SCREEN    1
#define LCD_HOME            2
#define	LCD_LINE1           0x80
#define	LCD_LINE2           0xC0
#define	LCD_LINE3           0X90
#define	LCD_LINE4           0xD0
#define	LCD_SPACE_ASCII     0X20

void LCD_Init(void);
void LCD_Strobe(void);
void LCD_Wait(volatile unsigned int x);
void LCD_WriteNibble(unsigned char LCD_COMMAND);
void LCD_WriteCommand(unsigned char LCD_COMMAND);
void LCD_WriteData(unsigned char LCD_DATA);
void LCD_WriteDataXY(char LCD_DATA, unsigned char LCD_X, unsigned char LCD_Y);
void LCD_GotoXY(unsigned char LCD_X, unsigned char LCD_Y);
void LCD_ClearSpace(unsigned char LCD_X, unsigned char LCD_Y, unsigned char LCD_WIDE);
void LCD_ClearLine(unsigned char LCD_Y);
void LCD_WriteString(char *LCD_STRING, unsigned char LCD_X, unsigned char LCD_Y);
void LCD_WriteROMString(const char *LCD_STRING, unsigned char LCD_X, unsigned char LCD_Y);

#endif /* LCD_H_ */
