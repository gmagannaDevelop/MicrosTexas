/*******************************************************************************
 *
 *                       Libreria para LCD
 *
 *******************************************************************************
 * FileName:        lcd.c
 * Processor:       MSP430G2231 (Puede ser otro)
 * Complier:        CCS 6.0.0
 * Author:          Jose Manuel Alvarado Farias, versión para PIC
 * 					Pedro Sánchez Ramírez (MrChunckuee) versión para MSP430
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:		Libreria para usarse a 4 bits de datos, soporta pantallas de
 * 					4 lineas, el tiempo de los retardos esta considerado para
 * 					usarse con un oscilador de 1MHz.
 *******************************************************************************
 * Historial del firmware
 * Rev.		Date		Comment
 * 	v1.00   --/--/----  	Creación del firmware para PIC
 * 	v1.01   28/06/2014  	Migración del firmware para MSP430
 *  	v1.02	25/09/2015	Corrección de algunas secciones de código para trabajar en CSS
 *
 ******************************************************************************/

#include "lcd.h"

/*******************************************************************************
 * Function:        void LCD_Init(void)
 * Description:     This function initilizes the LCD
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 * ****************************************************************************/
void LCD_Init(void){
	LCD_WriteNibble(0x03);
	LCD_Wait(5);
	LCD_WriteNibble(0x03);
	LCD_WriteNibble(0x03);
	LCD_WriteNibble(0x02);
	LCD_WriteCommand(0x20);
	LCD_WriteCommand(0x28);// set data length 4 bit 2 line
	LCD_WriteCommand(0x14);
	LCD_WriteCommand(0x0F);
	LCD_WriteCommand(0x01);// clear lcd
	LCD_WriteCommand(0x06);// cursor shift direction
	LCD_WriteCommand(0x06);//
	LCD_WriteCommand(LCD_ON);
	LCD_Wait(2);
	LCD_WriteCommand(LCD_CURSOR_OFF);
	//Escribe caracter definido en la CGRAM
	LCD_WriteCommand(0x40);
	LCD_WriteData(0x08);
	LCD_WriteData(0x0C);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x0F);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x0C);
	LCD_WriteData(0x08);
	LCD_WriteData(0x00);
	LCD_WriteCommand(LCD_HOME);
}

void LCD_Strobe(void){
	P1OUT |= EN;
	LCD_Wait(2);
	P1OUT &= ~EN;
	LCD_Wait(2);
}

void LCD_Wait(volatile unsigned int x){
	volatile unsigned int i;
	for (x; x>1;x--){
		for (i=0;i<=110;i++);
	}
}

void LCD_WriteNibble(unsigned char LCD_COMMAND){
	P1OUT &= ~RS; //Because sending command
	P1OUT &= ~EN;
	P1OUT &= 0xF0;
	P1OUT |= LCD_COMMAND;
	LCD_Strobe();
}

/*
 * @brief  Escribe un comando en el lcd alfanumerico
 * @param  LCD_COMMAND: comando enviado al display alfanumerico
 * @param  None
 * @retval None
 */
void LCD_WriteCommand(unsigned char LCD_COMMAND){
	P1OUT &= ~RS; //Because sending command
	P1OUT &= ~EN;
	P1OUT &= 0xF0;
	P1OUT |= ((LCD_COMMAND >> 4) & 0x0F);
	LCD_Strobe();
	LCD_Wait(4);
	P1OUT &= 0xF0;
	P1OUT |= (LCD_COMMAND & 0x0F);
	LCD_Strobe();
	LCD_Wait(4);
	if((LCD_COMMAND==LCD_HOME)||(LCD_COMMAND==LCD_CLEAR_SCREEN))
		LCD_Wait(2);
}

/*
 * @brief  Escribe un dato en el lcd alfanumerico
 * @param  LCD_DATA: dato enviado al display alfanumerico
 * @param  None
 * @retval None
 */
void LCD_WriteData(unsigned char LCD_DATA){
	P1OUT |= RS;  //because sending data
	P1OUT &= ~EN;
	P1OUT &= 0xF0;
	P1OUT |= ((LCD_DATA >> 4) & 0x0F);
	LCD_Strobe();
	P1OUT &= 0xF0;
	P1OUT |= (LCD_DATA & 0x0F);
	LCD_Strobe();
	LCD_Wait(4);
}

/*
 * @brief  Escribe un comando en el lcd alfanumerico
 * @param  LCD_DATA: dato enviado al display alfanumerico
 * @param  LCD_X: columna en la que se desea colocar un caracter en el display
 * @param  LCD_Y: fila en la que se desea colocar un caracter en el display
 * @retval None
 */
void LCD_WriteDataXY(char LCD_DATA, unsigned char LCD_X, unsigned char LCD_Y){
	LCD_GotoXY(LCD_X,LCD_Y);
	LCD_WriteData(LCD_DATA);
}

/*
 * @brief  Coloca el cursor en la fila y columna indicada
 * @param  LCD_X: Columna donde se desea colocar el cursor
 * @param 	LCD_Y: Fila donde se desea colocar el cursor
 * @retval None
 */
void LCD_GotoXY(unsigned char LCD_X, unsigned char LCD_Y){
	switch(LCD_Y){
		case 0:
			LCD_WriteCommand(LCD_LINE1+LCD_X);
		break;
		case 1:
			LCD_WriteCommand(LCD_LINE2+LCD_X);
		break;
		case 2:
			LCD_WriteCommand(LCD_LINE3+LCD_X);
		break;
		case 3:
			LCD_WriteCommand(LCD_LINE4+LCD_X);
		break;
		default:
		break;
	}
}

/*
 * @brief  Genera LCD_WIDE espacios en blanco comenzando en la fila LCD_Y y la columna LCD_X
 * @param  LCD_X: Columna donde se desea colocar el primer espacio en balnco
 * @param  LCD_Y: Fila donde se desea colocar el primer espacio en balnco
 * @param  LCD_WIDE: Cantidad de espacios en blanco que se desea colocar
 * @retval None
 */
void LCD_ClearSpace(unsigned char LCD_X, unsigned char LCD_Y, unsigned char LCD_WIDE){
	unsigned char LCD_SPACE_COUNT=0;
	unsigned char LCD_WIDE_COUNT=LCD_WIDE;
	LCD_SPACE_COUNT=16-LCD_X;
	if((LCD_SPACE_COUNT>0)&&(LCD_SPACE_COUNT<4)){
		LCD_GotoXY(LCD_X,LCD_Y);
		do{
			LCD_WriteData(LCD_SPACE_ASCII);
			LCD_WIDE_COUNT--;
			LCD_SPACE_COUNT--;
		}
		while(LCD_WIDE_COUNT&&LCD_SPACE_COUNT);
	}
	LCD_GotoXY(LCD_X,LCD_Y);
}

/*
 * @brief  Limpia la linea indicada por LCD_Y
 * @param  LCD_Y: Fila en donde se desea limpiar la linea
 * @param  None
 * @retval None
 */
void LCD_ClearLine(unsigned char LCD_Y){
	unsigned char LCD_SPACE_COUNT=16;
	switch(LCD_Y){
		case 0:
			LCD_WriteCommand(LCD_LINE1);
		break;
		case 1:
			LCD_WriteCommand(LCD_LINE2);
		break;
		case 2:
			LCD_WriteCommand(LCD_LINE3);
		break;
		case 3:
			LCD_WriteCommand(LCD_LINE4);
		break;
		default:
		break;
		}
	do{
		LCD_WriteData(LCD_SPACE_ASCII);
		LCD_SPACE_COUNT--;
	}
	while(LCD_SPACE_COUNT);
}

/*
 * @brief  Coloca una cadena ubicada en RAM en la fila LCD_Y y la columna LCD_X
 * @param  *LCD_STRING: Dirección de la cadena en RAM
 * @param  LCD_X: Columna donde se desea colocar el primer caracter
 * @param  LCD_Y: Linea donde se colocara la cadena
 * @retval None
 */
void LCD_WriteString(char *LCD_STRING, unsigned char LCD_X, unsigned char LCD_Y){
	unsigned char LCD_INDEX=0;
	unsigned char LCD_WIDE_COUNT=0;
	LCD_WIDE_COUNT=16-LCD_X;
	LCD_GotoXY(LCD_X,LCD_Y);
	for(LCD_INDEX=0;(*(LCD_STRING+LCD_INDEX)&&LCD_WIDE_COUNT);LCD_INDEX++,LCD_WIDE_COUNT--)
		LCD_WriteData(*(LCD_STRING+LCD_INDEX));
}

/*
 * @brief  Coloca una cadena ubicada en FLASH en la fila LCD_Y y la columna LCD_X
 * @param  *LCD_STRING: Dirección de la cadena en FLASH
 * @param  LCD_X: Columna donde se desea colocar el primer caracter
 * @param  LCD_Y: Linea donde se colocara la cadena
 * @retval None
 */
void LCD_WriteROMString(const char *LCD_STRING, unsigned char LCD_X, unsigned char LCD_Y){
	unsigned char LCD_INDEX=0;
	unsigned char LCD_WIDE_COUNT=0;
	LCD_WIDE_COUNT=16-LCD_X;
	LCD_GotoXY(LCD_X,LCD_Y);
	for(LCD_INDEX=0;(*(LCD_STRING+LCD_INDEX)&&LCD_WIDE_COUNT);LCD_INDEX++,LCD_WIDE_COUNT--)
		LCD_WriteData(*(LCD_STRING+LCD_INDEX));
}



