/*******************************************************************************
 *
 *                  Libreria para funciones especiales
 *
 *******************************************************************************
 * FileName:        special.c
 * Processor:       ---------
 * Complier:        CCS 6.0.0
 * Author:          Pedro Sánchez Ramírez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:	    Libreria para funciones especiales, o funciones que apliquen
 * 		    para varios proyectos
 *******************************************************************************
 * Historial del firmware
 * Rev.		Date		Comment
 * 	v1.00   19/10/2015    	- Creación de la libreria
 * 				- Se implemento la funcion itoa
 ******************************************************************************/
#include "special.h"

/*******************************************************************************
 * Function:        char *itoa(int value, char *s, int radix)
 * Description:     Esta funcion convierte una variable int a una char
 * Precondition:    None
 * Parameters:      int value = Variable tipo int que se convertira
 * 					char *s = Variable tipo char conde se guardara el resultado
 * 					int radix = Base que tendra *s, Ej: Decimal=10, Binario=2
 * Return Values:   Regresa el valor de "s"
 * Remarks:         Considerar que una int abarca de -32768 a 32767
 * 					Ej: itoa (INT_VARIABLE, CHAR_VARIABLE, 10)
 * Links:	    	https://www.daniweb.com/programming/software-development/threads/11049/convert-int-to-string
 * ****************************************************************************/
char *itoa(int value, char *s, int radix){
    const char *digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    unsigned long ulvalue = value;
    char *p = s, *q = s;
    char temp;
    if (radix == 10 && value < 0) {
    	*p++ = '-';
        q = p;
        ulvalue = -value;
    }
    do {
    	*p++ = digits[ulvalue % radix];
        ulvalue /= radix;
    } while (ulvalue > 0);
    *p-- = '\0';
    while (q < p) {
        temp = *q;
        *q++ = *p;
        *p-- = temp;
    }
    return s;
}

