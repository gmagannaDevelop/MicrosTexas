
#include <msp430g2553.h>
#include "lcd.h"
#include "special.h"

void Delay_centSeg(volatile unsigned int t);

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
    ADC10CTL1 = (                       // Configura convertidor analogico-digital
            INCH_3 |                    // INCH_3 : (3*0x1000u)  Selects Channel 3              !!
            SHS_0                       // (0x0400) /* ADC10 Sample/Hold Source Bit: 0 */
    );

    ADC10AE0  = 0x40;                   //
    ADC10CTL0 = (
            SREF_0 |
            ADC10SHT_0 |
            ADC10ON
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
            //mame = 10 * d / 850;


            for(i=0; i<16; i++){ char_LCD[i]=0; } //Clear char_LCD
            itoa(d, char_LCD, 10); //Pasar int_Value a decimal
            LCD_WriteROMString("Voltaje:",0,0);
            LCD_WriteString(char_LCD,0,1);
            Delay_centSeg(50);


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


void Delay_centSeg(volatile unsigned int t)
{
    volatile unsigned int i;
    for (i=0 ;i<t; i++){
            __delay_cycles(10000);
    }
}

// ADC10 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC10_VECTOR))) ADC10_ISR (void)
#else
#error Compiler not supported!
#endif
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}


