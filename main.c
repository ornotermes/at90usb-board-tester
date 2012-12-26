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

#define LED_R		(1<<PC6)
#define LED_R_PORT	PORTC
#define LED_R_DDR	DDRC
#define LED_R_PWM	OCR1A

#define LED_G		(1<<PC5)
#define LED_G_PORT	PORTC
#define LED_G_DDR	DDRC
#define LED_G_PWM	OCR1B

#define LED_B		(1<<PB7)
#define LED_B_PORT	PORTB
#define LED_B_DDR	DDRB
#define LED_B_PWM	OCR1C

#define BTN		(1<<PD7)
#define BTN_PORT	PORTD
#define BTN_PIN		PIND
#define BTN_DDR		DDRD

#define LED_MAX		16 //number of steps in each color
#define LED_MAX_PWM	LED_MAX*LED_MAX

char led_phase = 0; //The phase is what color shifting is going on 0:R-Y, 1:Y-G, 2:G-C etc
unsigned char led_step = 0; //step in current phase
unsigned char output_test=0; //step in PGIO output test

int main(void)
{
	//--- Set clock speed ---//
	//Set full speed (disables CKDIV8 by registers)
	CLKPR = (1<<CLKPCE);
	CLKPR = 0;

	//--- Init LEDs ---//
	LED_R_DDR |= LED_R;
	LED_G_DDR |= LED_G;
	LED_B_DDR |= LED_B;
	
	//Set up as 16-bit PWM
	TCCR1A = (1<<COM1A1)|(1<<COM1A0)|(1<<COM1B1)|(1<<COM1B0)|(1<<COM1C1)|(1<<COM1C0)|(1<<WGM11);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10);
	ICR1 = 0xFFFF;
	
	//Set initial values
	LED_R_PWM = LED_MAX_PWM;
	LED_G_PWM = 0x0;
	LED_B_PWM = 0x0;

	//--- Init timer0 ---//
	TCCR0B = (1<<CS00)|(0<<CS01)|(1<<CS02); //Select clock source
	TIMSK0 = (1<<TOIE0); //Enable overflow interrupt

	//--- Init button ---//
	//Has external pullup due to HWB
	EICRB |= (1<<ISC71); //trigger interrupt on falling edge
	EIMSK |= (1<<INT7); //Enable interrupt 7

	//--- Set all GPIO as output ---//
	DDRB = (1<<PB7) | (1<<PB6) | (1<<PB5) | (1<<PB4) | (1<<PB3) | (1<<PB2) | (1<<PB1) | (1<<PB0);
	DDRC = (1<<PC7) | (1<<PC6) | (1<<PC5) | (1<<PC4) | (1<<PC2);
	DDRD = (0<<PD7) | (1<<PD6) | (1<<PD5) | (1<<PD4) | (1<<PD3) | (1<<PD2) | (1<<PD1) | (1<<PD0);

	sei();
	while(1){
		//--- Output test, to see that all GPIO has contact with PCB ---///
		output_test = output_test << 1;
		if (output_test == 0) output_test = 1;
		PORTB = output_test;
		PORTC = 0b11110100 & output_test;
		PORTD = BTN | output_test;
		_delay_ms(500);
	}
}

//--- HWB Button interrupt ---//
ISR(INT7_vect)
{

}

//--- Timer0 interrupt ---//
ISR(TIMER0_OVF_vect)
{
	//--- LEDs are not linear, compensating by running them in 16bit PWM and giving them eponential value (up to 255*255).
	int led_val = led_step * led_step;
	
	switch (led_phase)
	{
	case 0: //Red is max, increase green
		LED_G_PWM = led_val;
		break;
	case 1: //Red and green is max, decrease red
		LED_R_PWM = LED_MAX_PWM - led_val ;
		break;
	case 2: //Green is max, increase blue
		LED_B_PWM = led_val;
		break;
	case 3: //Green and blue is max, decrease green
		LED_G_PWM = LED_MAX_PWM - led_val;
		break;
	case 4: //Blue is max, increase red
		LED_R_PWM = led_val;
		break;
	case 5: //Red and blue is max, decrease blue
		LED_B_PWM = LED_MAX_PWM - led_val;
		break;
	}
	
	led_step++; //Next step in current phase
	if (led_step == LED_MAX) //End of current phase
	{
		led_step = 0;
		led_phase++; //Next phase
		if (led_phase > 5) led_phase = 0; Go from phase 0 to phase 5 and start over.
	}
}
