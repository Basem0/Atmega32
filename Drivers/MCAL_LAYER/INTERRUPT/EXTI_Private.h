/*
 * EXTI_Private.h
 *
 * Created: 1/31/2024 1:59:30 AM
 *  Author: ahmed
 */ 


#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#define DEACTIVE 	0
#define ACTIVE 		1

typedef enum{
	INTERRUPT_EXTERNAL_INT0 =  0,
	INTERRUPT_EXTERNAL_INT1,
	INTERRUPT_EXTERNAL_INT2
}interrupt_INTx_src;

typedef enum{
	LOW_LEVEL = 0,
	ANY_LOGIC,
	FALLING_EDGE,
	RISING_EDGE
}EXTI_status;

typedef struct{
	
}EXTIx;

#define MCUCR				*((volatile uint8*)0x55)
#define MCUCSR				*((volatile uint8*)0x54)
#define GICR				*((volatile uint8*)0x5B)
#define GIFR				*((volatile uint8*)0x5A)
#define SREG				*((volatile uint8*)0x5F)

#define ISR(VECT_NUM)		void VECT_NUM (void) __attribute__ ((signal));\
void VECT_NUM (void)

#define VECT_INT0			__vector_1
#define VECT_INT1			__vector_2
#define VECT_INT2			__vector_3
#define VECT_TIMER2_CTC		__vector_4

#endif /* EXTI_PRIVATE_H_ */