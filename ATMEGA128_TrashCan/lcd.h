#ifndef _LCD_H
#define _LCD_H

#include "main.h"

extern void LCD_command(unsigned char command);		
extern void LCD_data(unsigned char data);		
extern void LCD_string(unsigned char command, unsigned char *string); 
extern void LCD_initialize(void);		
#endif 
