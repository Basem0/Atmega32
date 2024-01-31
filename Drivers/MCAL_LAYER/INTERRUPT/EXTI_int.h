/*
 * EXTI_int.h
 *
 * Created: 1/31/2024 2:02:11 AM
 *  Author: ahmed
 */ 


#ifndef EXTI_INT_H_
#define EXTI_INT_H_

#include "EXTI_Private.h"

#define Ext_INT0_Enable()  (GICR |= 0x40)
#define Ext_INT1_Enable()  (GICR |= 0x80)
#define Ext_INT2_Enable()  (GICR |= 0x20)
#define Ext_INT0_Disable() (GICR &= 0xBF)
#define Ext_INT1_Disable() (GICR &= 0x7F)
#define Ext_INT2_Disable() (GICR &= 0xDF)



Std_ReturnType EXTI_Init (EXTI_t * Copy_EXT_INTx);

Std_ReturnType EXTI_EnableINT(interrupt_INTx_src source);

Std_ReturnType EXTI_DisableINT(interrupt_INTx_src source);

Std_ReturnType EXTI_CallBack(EXTI_t Copy_EXT_INTx);



#endif /* EXTI_INT_H_ */