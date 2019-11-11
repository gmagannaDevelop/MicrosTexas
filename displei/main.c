
#define RS 2
#define EN 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

#include <msp430.h> 
#include <LiquidCrystal.h>

void setup(void);

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
	lcd.begin(16, 2);
	lcd.setCursor (0,0);
	
	return 0;
}

void setup() {
  lcd.begin(16, 2); //We are using a 16*2 LCD display
  lcd.setCursor (0,0); //Place the cursor at 1st row 1st column
  lcd.print("MSP430G2553"); //Display a intro message
  lcd.setCursor(0, 1);   // set the cursor to 1st column 2nd row
  lcd.print("-CircuitDigest"); //Display a intro message

   delay(2000); //Wait for display to show info
   lcd.clear(); //Then clean it

}

