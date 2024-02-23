/*
 * Timer0_Register.h
 *
 * Created: 2/22/2024 2:35:49 AM
 *  Author: ahmed
 */ 


#ifndef TIMER0_REGISTER_H_
#define TIMER0_REGISTER_H_

#include "../Std_Types.h"
#include "../Std_Libraries.h"
#include "../GPIO/hal_gpio.h"

// Timer0 Control register - TCCR0
#define TCCR0			*((volatile uint8*) 0x53)
// Timer0 Control register bits
#define TCCR0_FOC0		7
#define TCCR0_WGM00		6	
#define TCCR0_COM01		5
#define TCCR0_COM00		4
#define TCCR0_WGM01		3	
#define TCCR0_CS02		2
#define TCCR0_CS01		1
#define TCCR0_CS00		0

// Timer/Counter0 register
#define TCNT0			*((volatile uint8*) 0x52)

// Compare Match register
#define OCR0			*((volatile uint8*) 0x5C)

// Timer0 Interrupt Mask
#define TIMSK			*((volatile uint8*) 0x59)
// Timer0 Interrupt Mask bits
#define TIMSK_OCIE0		1	
#define TIMSK_TOIE0		0		

// Timer0 flag
#define TIFR			*((volatile uint8*) 0x58)
#define  TIFR_TOV0    0
#define  TIFR_OCF0   1

#endif /* TIMER0_REGISTER_H_ */