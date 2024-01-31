/*
 * EXTI_Config.h
 *
 * Created: 1/31/2024 2:04:55 AM
 *  Author: ahmed
 */ 


#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

#include "EXTI_Private.h"

typedef struct
{
	void (* EXT_InterruptHandler)(void);
	uint8 EXTI_State;
	EXTI_status EXTI_Level;
	interrupt_INTx_src source;
}EXTI_t;



#endif /* EXTI_CONFIG_H_ */