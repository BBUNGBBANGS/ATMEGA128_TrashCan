/*
 * ATMEGA128_TrashCan.c
 *
 * Created: 2023-05-29 오전 12:18:48
 * Author : jisu8
 */ 

#include "lcd.h"

static void Port_Init(void);
static void Timer1_Init(void);
static void Timer3_Init(void);
static int UltraSonic(char ch); 
static void ServoControl(char control); 

unsigned int Echo_count[2];
unsigned int Distance[2];

#define ULTRA_SONIC_CH1     0
#define ULTRA_SONIC_CH2     1

#define SERVO_CLOSE         0
#define SERVO_OPEN          1

int main(void)
{
    Port_Init();
    LCD_initialize();
    /* Replace with your application code */
    LCD_string(0x80,"Smart Trash Can");
    LCD_string(0xC0,"Initializing");
    Timer1_Init();
    Timer3_Init();
    _delay_ms(200);
    while (1) 
    {
        Distance[ULTRA_SONIC_CH1] = UltraSonic(ULTRA_SONIC_CH1);        
        Distance[ULTRA_SONIC_CH2] = UltraSonic(ULTRA_SONIC_CH2);

        if(Distance[ULTRA_SONIC_CH1] < 30)
        {
            ServoControl(SERVO_OPEN);
        }
        else
        {
            ServoControl(SERVO_CLOSE);            
        }

        if(Distance[ULTRA_SONIC_CH2] < 30)
        {
            LCD_string(0xC0,"Status : Full");
        }
        else
        {
            LCD_string(0xC0,"Status : Empty");            
        }

        _delay_ms(100);
    }
}

static void Port_Init(void)
{
    MCUCR = 0x80;					// enable external memory and I/O
    XMCRA = 0x44;					// 0x1100-0x7FFF=1 wait, 0x8000-0xFFFF=0 wait
    XMCRB = 0x80;					// enable bus keeper, use PC0-PC7 as address

    DDRB = 0xF0;					// 입력/출력 방향결정, PORTB7..4 = output, PORTB3..0 = Input
    PORTB = 0x00;                   // I/O pin 초기값 지정

    DDRD = 0x00;					// Port D = Input, “1= Output, 0= Input”
    PORTD = 0x00;

    DDRE = 0x0A;					// Port E1,E3 = output, All other PORTs are Input
    PORTE = 0x00;

    DDRF = 0x00;					// Port F = Input
    PORTF = 0x00;

    DDRG = 0x1F;
    
    LCD_CONTROL = 0x00;
    LCD_DATABUS = 0x00;
}

static void Timer1_Init(void)
{
    TCCR1A = 0x00; // Normal Port Operation
    TCCR1B = 0x02; // CLK/8(16MHz/8) = 2MHz(T=0.5us)
    TCCR1C = 0x00; // Do not use "force output compare"
    
    TCNT1H = 0x00; // Upper Byte of Timer/Counter 1
    TCNT1L = 0x00; // Lower Byte of Timer/Counter 1 
    EICRA = 0x0A; // INT0, INT1: falling edge trigger
    EICRB = 0x88; // falling edge trigger 
    sei();
}

static void Timer3_Init(void)
{
	TCCR3A=0x82;
	TCCR3B=0x1b;
	ICR3 =4999; //TOP
}

ISR(INT0_vect) 
{
    Echo_count[0] = TCNT1; //PD0
}

ISR(INT1_vect) 
{
    Echo_count[1] = TCNT1; //PD0
}

static int UltraSonic(char ch) 
{ 
    int range = 0;
    switch(ch) 
    { //triggering Ultrasonic Sensor
        case ULTRA_SONIC_CH1 : 
            PORTE |= 0x10; // PE4, output Trig Pulse 
            EIMSK |= 0x01; // Enable the INT0 
            _delay_us(12);
            PORTE &= ~0x10; // off PE4 of the PORTE 
            TCNT1 = 0; // Counter1 is cleared
            EIFR = 0x00; // Clear interrupt Flag Reg.    
            _delay_ms(50);
            EIMSK = 0x00; //Disable the all INTx

            if(Echo_count[ULTRA_SONIC_CH1] < 232 ) 
            {
                Echo_count[ULTRA_SONIC_CH1] = 232; //2cm, 116us
            }
            if(Echo_count[ULTRA_SONIC_CH1] > 46400 ) 
            {
                Echo_count[ULTRA_SONIC_CH1] = 46400; //400cm, 23.2ms
            }

            range = Echo_count[ULTRA_SONIC_CH1] / 116;
        break;
        case ULTRA_SONIC_CH2 : 
            PORTE |= 0x20; // PE5, output Trig Pulse  
            EIMSK |= 0x02; // Enable the INT1
            _delay_us(12);
            PORTE &= ~0x20; // off PE5 of the PORTE
            TCNT1 = 0; // Counter1 is cleared
            EIFR = 0x00; // Clear interrupt Flag Reg.    
            _delay_ms(50);
            EIMSK = 0x00; //Disable the all INTx

            if(Echo_count[ULTRA_SONIC_CH2] < 232 ) 
            {
                Echo_count[ULTRA_SONIC_CH2] = 232; //1.6cm, 90us
            }
            if(Echo_count[ULTRA_SONIC_CH2] > 46400 ) 
            {
                Echo_count[ULTRA_SONIC_CH2] = 46400; //160cm, 18ms
            }

            range = Echo_count[ULTRA_SONIC_CH2] / 116;
        break; 
        default : 
        break;
    }
    
    return range;
}

static void ServoControl(char control)
{
    switch(control)
    {
        case SERVO_CLOSE : 
            OCR3A = 125; //0도
        break;
        case SERVO_OPEN : 
            OCR3A = 625; //180도
        break;
    }

}