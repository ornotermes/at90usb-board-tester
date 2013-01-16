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

void custchars(void)
{
	lcd_command(_BV(LCD_CGRAM)+0*8);    //The 0 on this line may be 0-7
	lcd_data(0b00100);
	lcd_data(0b00000);
	lcd_data(0b01110);
	lcd_data(0b00001);
	lcd_data(0b01111);
	lcd_data(0b10001);
	lcd_data(0b01111);
	lcd_data(0b00000);
	
	lcd_command(_BV(LCD_CGRAM)+1*8);
	lcd_data(0b01010);
	lcd_data(0b00000);
	lcd_data(0b01110);
	lcd_data(0b00001);
	lcd_data(0b01111);
	lcd_data(0b10001);
	lcd_data(0b01111);
	lcd_data(0b00000);
		
	lcd_command(_BV(LCD_CGRAM)+2*8);
	lcd_data(0b01010);
	lcd_data(0b00000);
	lcd_data(0b01110);
	lcd_data(0b10001);
	lcd_data(0b10001);
	lcd_data(0b10001);
	lcd_data(0b01110);
	lcd_data(0b00000);
	
	lcd_command(_BV(LCD_CGRAM)+3*8);
	lcd_data(0b11111);
	lcd_data(0b10001);
	lcd_data(0b10001);
	lcd_data(0b10001);
	lcd_data(0b10001);
	lcd_data(0b10001);
	lcd_data(0b10001);
	lcd_data(0b11111);
	
	lcd_command(_BV(LCD_CGRAM)+4*8);
	lcd_data(0b10101);
	lcd_data(0b01010);
	lcd_data(0b10101);
	lcd_data(0b01010);
	lcd_data(0b10101);
	lcd_data(0b01010);
	lcd_data(0b10101);
	lcd_data(0b01010);
	
	lcd_command(_BV(LCD_CGRAM)+5*8);
	lcd_data(0b00000);
	lcd_data(0b01010);
	lcd_data(0b01010);
	lcd_data(0b00000);
	lcd_data(0b01110);
	lcd_data(0b10001);
	lcd_data(0b00000);
	lcd_data(0b00000);
	
	lcd_command(_BV(LCD_CGRAM)+6*8);
	lcd_data(0b00000);
	lcd_data(0b01010);
	lcd_data(0b01010);
	lcd_data(0b00000);
	lcd_data(0b01110);
	lcd_data(0b10001);
	lcd_data(0b10001);
	lcd_data(0b01110);
	
	lcd_command(_BV(LCD_CGRAM)+7*8);
	lcd_data(0b01110);
	lcd_data(0b11111);
	lcd_data(0b10101);
	lcd_data(0b10101);
	lcd_data(0b11111);
	lcd_data(0b11111);
	lcd_data(0b11111);
	lcd_data(0b10101);
	
}
