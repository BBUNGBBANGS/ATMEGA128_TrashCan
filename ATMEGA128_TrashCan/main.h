#ifndef _MAIN_H
#define _MAIN_H

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
/* ------------------------------------------------------------------------------- */
/*  OK128.h : I/O Address Definition & User Function for OK-128 V2.2 Training Kit  */
/* ------------------------------------------------------------------------------- */
#define LCD_DATABUS	(*(volatile unsigned char *)0x2000) // LCD/GLCD data
							    // 7-segment LED pattern
#define LCD_CONTROL	(*(volatile unsigned char *)0x2100) // LCD/GLCD control signal
#define DIG_SELECT	(*(volatile unsigned char *)0x2200) // 7-segment LED digit select
							    // 8-bit parallel data

#define RTC_SECOND	(*(volatile unsigned char *)0x2300) // DS12C887 RTC
#define RTC_SEC_ALM	(*(volatile unsigned char *)0x2301)
#define RTC_MINUTE	(*(volatile unsigned char *)0x2302)
#define RTC_MIN_ALM	(*(volatile unsigned char *)0x2303)
#define RTC_HOUR	(*(volatile unsigned char *)0x2304)
#define RTC_HOUR_ALM	(*(volatile unsigned char *)0x2305)
#define RTC_WEEKDAY	(*(volatile unsigned char *)0x2306)
#define RTC_DATE	(*(volatile unsigned char *)0x2307)
#define RTC_MONTH	(*(volatile unsigned char *)0x2308)
#define RTC_YEAR	(*(volatile unsigned char *)0x2309)
#define RTC_A 		(*(volatile unsigned char *)0x230A)
#define RTC_B		(*(volatile unsigned char *)0x230B)
#define RTC_C		(*(volatile unsigned char *)0x230C)
#define RTC_D		(*(volatile unsigned char *)0x230D)
#define RTC_FLAG	(*(volatile unsigned char *)0x230F)

#endif