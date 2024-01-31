/*
 * interrupt_external.h
 *
 * Created: 1/30/2024 8:23:14 PM
 *  Author: ahmed
 */ 


#ifndef INTERRUPT_PRIVATE_H_
#define INTERRUPT_PRIVATE_H_

/* Section : Includes */
#include "interrupt_config.h"

/* Section: Macro Declarations */
/*
#define ACTIVE 		5
#define DEACTIVE 		9


#define RISING_EDGE			5
#define FALLING_EDGE		9
#define ANY_LOGIC			19
#define LOW_LEVEL			93
*/
#define GICR   *((volatile uint8 *) 0x5B)
#define GIFR   *((volatile uint8 *) 0x5A)
#define MCUCSR *((volatile uint8 *) 0x54)
#define MCUCR  *((volatile uint8 *) 0x55)
#define SREG   *((volatile uint8 *) 0x5F)

/* Section: Macro Functions Declarations */
#define Ext_INT0_Enable()  (GICR |= 0x40)
#define Ext_INT1_Enable()  (GICR |= 0x80)
#define Ext_INT2_Enable()  (GICR |= 0x20)
#define Ext_INT0_Disable() (GICR &= 0xBF)
#define Ext_INT1_Disable() (GICR &= 0x7F)
#define Ext_INT2_Disable() (GICR &= 0xDF)

/* Section: Data Type Declarations */
typedef enum{
	INTERRUPT_EXTERNAL_INT0 =  0,
	INTERRUPT_EXTERNAL_INT1,
	INTERRUPT_EXTERNAL_INT2
}interrupt_INTx_src;

typedef enum{
	LOW_LEVEL =  0,
	ANY_LOGIC,
	FALLING_EDGE,
	RISING_EDGE
}interrupt_INTx_State;

typedef struct {
	void (* EXT_InterruptHandler)(void);
	pin_config_t mcu_pin;
	interrupt_INTx_State state;
	interrupt_INTx_src source;
}interrupt_INTx_t;


/* Section: Function Declarations */
Std_ReturnType Interrupt_External_Init(interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_External_Enable(interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_External_Disable(interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_External_CallBack(interrupt_INTx_t *int_obj,void * Copy_pvidParameter);



#endif /* INTERRUPT_PRIVATE_H_ */