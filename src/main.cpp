#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h> 

#include "uart.h"
#include "i2c.h"
#include "spi.h"
#include "i2c_display.h"
#include "buttons.h"
#include "utils.h"

 

void LCDTest() {
	// I2C and LCD test
	LCDI2C lcd;
	lcd.init(LCD_I2C_ADDRESS); // address of pcf8574
	lcd.backlight();
	lcd.cursorAt(0, 4);
	lcd.print("SCALE v.1");
	
	while(true) { 
		for (int32_t i = 0; i < 100; i++) {
			lcd.cursorAt(2, 10);
			lcd.print(i);
			_delay_ms(500);
		}
		lcd.clear();
	}
}

void uartTest() {
	Uart uart;
	uart.init(9600);
	uart.printf("Text, signed int16=%d, hex=%2x and  sting[%s] bin[%8b]", 123, 11, "my string", 11);
}

//***************************************************

Buttons g_buttons;	//global instance, because of interrupt

ISR(TIMER0_OVF_vect) {
    g_buttons.isrHandle();
}


//****************************************************
int main() {

	Uart uarta;
	uarta.init(9600);
	
	char buffer[20];
	strcpy_P(buffer, PSTR("Here you go!"));

	uarta.sendString(buffer);
	while(1) {};


}
