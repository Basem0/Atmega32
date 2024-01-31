/*
 * interrupt_config.h
 *
 * Created: 1/30/2024 8:22:21 PM
 *  Author: ahmed
 */ 


#ifndef INTERRUPT_CONFIG_H_
#define INTERRUPT_CONFIG_H_

#include "../GPIO/hal_gpio.h"

#define ISR(VECT_NUM)		void VECT_NUM (void) __attribute__ ((signal));\
void VECT_NUM (void)

#define VECT_INT0			__vector_1
#define VECT_INT1			__vector_2
#define VECT_INT2			__vector_3



#endif /* INTERRUPT_CONFIG_H_ */