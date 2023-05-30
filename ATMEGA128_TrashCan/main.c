/*
 * ATMEGA128_TrashCan.c
 *
 * Created: 2023-05-29 오전 12:18:48
 * Author : jisu8
 */ 

#include <avr/io.h>

void Port_Init(void);

int main(void)
{
    Port_Init();
    /* Replace with your application code */
    while (1) 
    {

    }
}

void Port_Init(void)
{
    /* D0~D7 출력 설정 */
    DDRA = 0xFF;
    PORTA = 0x00;
}
