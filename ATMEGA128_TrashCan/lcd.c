

#include "lcd.h"

/* write a command(instruction) to text LCD */
void LCD_command(unsigned char command)		
{
    LCD_CONTROL = 0x00;				// E = 0, Rs = 0
    LCD_DATABUS = command;			// output command
    LCD_CONTROL = 0x01;				// E = 1
    _delay_us(1);
    LCD_CONTROL = 0x00;				// E = 0
    _delay_us(50);
}
/* display a character on text LCD */
void LCD_data(unsigned char data)		
{
    LCD_CONTROL = 0x02;				// E = 0, Rs = 1
    LCD_DATABUS = data;				// output data
    LCD_CONTROL = 0x03;				// E = 1
    _delay_us(1);
    LCD_CONTROL = 0x02;				// E = 0
    _delay_us(50);
}
/* display a string on LCD */
void LCD_string(unsigned char command, unsigned char *string) 
{
    LCD_command(command);				// start position of string
    while(*string != '\0')			// display string
    { 
        LCD_data(*string);
        string++;
    }
}
/* initialize text LCD module */
void LCD_initialize(void)			
{
    LCD_CONTROL = 0x03;				// E = 1, Rs = 1 (dummy write)
    LCD_CONTROL = 0x02;				// E = 0, Rs = 1
    _delay_ms(2);

    LCD_command(0x38);				// function set(8 bit, 2 line, 5x7 dot)
    LCD_command(0x0C);				// display control(display ON, cursor OFF)
    LCD_command(0x06);				// entry mode set(increment, not shift)
    LCD_command(0x01);				// clear display
    _delay_ms(2);
}
