/*
 * ADC_init.h
 *
 * Created: 2/14/2024 2:30:38 AM
 *  Author: ahmed
 */ 


#ifndef ADC_INIT_H_
#define ADC_INIT_H_



#include "../Std_Types.h"
#include "../GPIO/hal_gpio.h"
#include "../INTERRUPT/EXTI_int.h"

#include "ADC_config.h"
#include "ADC_priv.h"

Std_ReturnType ADC_Init(void);

Std_ReturnType ADC_ConversionSync (uint8 channel , uint16* value);

Std_ReturnType ADC_ConversionAsync (uint8 channel , uint16* value,void(*PNotificationFunc)(void));


#endif /* ADC_INIT_H_ */