/*
	Copyright (c) 2012 Rikard Lindstrom <ornotermes@gmail.com>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "lcdlibrary/lcd.c"
#include "custchars.c"

#define LED_R		(1<<PC6)
#define LED_R_PORT	PORTC
#define LED_R_DDR	DDRC
#define LED_R_PWM	OCR1A

#define LED_G		(1<<PC5)
#define LED_G_PORT	PORTC
#define LED_G_DDR	DDRC
#define LED_G_PWM	OCR1B

#define BTN		(1<<PD7)
#define BTN_PORT	PORTD
#define BTN_PIN		PIND
#define BTN_DDR		DDRD

//Create a charecter stream for stdout
FILE lcd_str = FDEV_SETUP_STREAM(lcd_putc, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
	//--- Set clock speed ---//
	//Set full speed (disables CKDIV8 by registers)
	CLKPR = (1<<CLKPCE);
	CLKPR = 0;

	//negative contrast voltage generator
	DDRB = (1<<PB7);
	TCCR1A = (1<<COM1C0);
	TCCR1B = (1<<WGM12)|(1<<CS11)|(1<<CS10);
	OCR1A = 10;

	//--- Init button ---//
	//Has external pullup due to HWB
	EICRB |= (1<<ISC71); //trigger interrupt on falling edge
	EIMSK |= (1<<INT7); //Enable interrupt 7
	
	lcd_init(LCD_DISP_ON);
	custchars(); //upload custom chars
	lcd_clrscr();
	
	stdout = stdin = &lcd_str; //Connect stdout to stream

	sei(); //Set interrupt
	
	printf("Hello world!");
	
	while(1)
	{
	}
}
