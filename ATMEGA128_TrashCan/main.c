/*
 * ATMEGA128_TrashCan.c
 *
 * Created: 2023-05-29 오전 12:18:48
 * Author : jisu8
 */ 

#include "lcd.h"


static void Port_Init(void);

int main(void)
{
    Port_Init();
    LCD_initialize();
    /* Replace with your application code */
    while (1) 
    {

    }
}

static void Port_Init(void)
{
    MCUCR = 0x80;					// enable external memory and I/O
    XMCRA = 0x44;					// 0x1100-0x7FFF=1 wait, 0x8000-0xFFFF=0 wait
    XMCRB = 0x80;					// enable bus keeper, use PC0-PC7 as address

    DDRB = 0xFF;					// PORTB = output (D/A, LED1-4, matrix LED)
    PORTB = 0x00;
    DDRD = 0xFF;					// PORTD = output (matrix LED)
    PORTD = 0x00;
    DDRE = 0x0C;					// PORTE = output for PE3, PE2
    PORTE = 0x00;
    DDRF = 0x00;					// PORTF = input (KEY1-4)

    DIG_SELECT = 0x00;				// clear 7-segment LED
}
