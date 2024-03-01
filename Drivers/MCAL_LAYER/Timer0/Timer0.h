/*
 * Timer0.h
 *
 * Created: 2/22/2024 2:43:50 AM
 *  Author: ahmed
 */ 

#ifndef TIMER0_H_
#define TIMER0_H_

#define TCCR0	*((volatile uint8*)0x53)

#define TCCR0_CS00		0
#define TCCR0_CS01		1
#define TCCR0_CS10		2
#define TCCR0_WGM01		3			
#define TCCR0_WGM00		6			
#define TCCR0_COM00		4			
#define TCCR0_COM01		5			
#define TCCR0_FOC0		7			


#define TCNT0	*((volatile uint8*)0x52)

#define OCR0	*((volatile uint8*)0x5C)

#define TIMSK   *((volatile uint8*)0x59)

#define TIMSK_TOIE0	  0
#define TIMSK_OCIE0   1		 	

#define TIFR	*((volatile uint8*)0x58)

#define TIFR_TOV0						0
#define TIFR_OCF0						1

#define TIMER_NO_CLOCK							0
#define TIMER_NO_Prescaler			            1
#define TIMER_Prescaler8						8
#define TIMER_Prescaler64						64
#define TIMER_Prescaler256						256
#define TIMER_Prescaler1024						1024
#define TIMER_EXTERNAL_CLOCK_SOURCE_FALING		6
#define TIMER_EXTERNAL_CLOCK_SOURCE_RISING		7

#define TIMER_Prescaller_Mask					0x07

#define TIMER0_NORMAL_MODE						0
#define TIMER0_PHASE_CORRECT_PWM_MODE			1
#define TIMER0_CTC_MODE							2
#define TIMER0_FAST_PWM_MODE					3

#define OC0_DISCONNECTED						0
#define OC0_TOGGLE								1
#define OC0_CLEAR								2
#define OC0_SET									3

#define OC0_NON_INVERTING_MODE					2
#define OC0_INVERTING_MODE						3

#define CLEAR_UP_COUNTING_SET_DOWN_COUNTING_OC0		2
#define SET_UP_COUNTING_CLEAR_DOWN_COUNTING_OC0		3

#define TIMER0_F_CPU							1000UL
#define TIMER0_OVF_Counter						256
#define TIMER0_PERCENTAGE_RATIO					100.0


Std_ReturnType TIMER0_Init(void);

Std_ReturnType TIMER0_Delay_ms_Synch(uint32 delay);

Std_ReturnType TIMER0_Delay_ms_Asynch(uint32 delay , void (*funCallBack)(void*) , void * Copy_PvidArg);

Std_ReturnType TIMER0_GeneratePWM(uint8 DutyCycle)

#endif /* TIMER0_H_ */
