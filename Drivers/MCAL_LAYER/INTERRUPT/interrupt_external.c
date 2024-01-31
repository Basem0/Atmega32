/*
 * interrupt_external.c
 *
 * Created: 1/30/2024 8:46:35 PM
 *  Author: ahmed
 */ 

#include "interrupt_external.h"
static volatile void (*EXTI_Fun[3])(void*) = {NULL,NULL,NULL};
void * EXTI_ApvidGenericparameter[3] = {NULL,NULL,NULL};
	
static Std_ReturnType Interrupt_External_state(interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_External_Init(interrupt_INTx_t *int_obj)
{
	Std_ReturnType ret = E_NOT_OK;
	if(NULL == int_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		gpio_pin_direction_intialize(&int_obj->mcu_pin);
		Interrupt_External_Enable(int_obj);
		Interrupt_External_state(int_obj);
		ret = E_OK;
	}
	return ret;
}
Std_ReturnType Interrupt_External_Enable(interrupt_INTx_t *int_obj)
{
	Std_ReturnType ret = E_NOT_OK;
	if(NULL == int_obj)
	{
		ret = E_NOT_OK;
	}	
	else
	{
		if(INTERRUPT_EXTERNAL_INT0 == int_obj->source)
		{
			Ext_INT0_Enable();
			ret = E_OK;
		}
		else if(INTERRUPT_EXTERNAL_INT1 == int_obj->source)
		{
			Ext_INT1_Enable();
			ret = E_OK;
		}
		else if(INTERRUPT_EXTERNAL_INT2 == int_obj->source)
		{
			Ext_INT2_Enable();
			ret = E_OK;
		}
		else
		{
			ret = E_NOT_OK;
		}
	}
	return ret;
}
Std_ReturnType Interrupt_External_Disable(interrupt_INTx_t *int_obj)
{
	Std_ReturnType ret = E_NOT_OK;
	if(NULL == int_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		if(INTERRUPT_EXTERNAL_INT0 == int_obj->source)
		{
			Ext_INT0_Disable();
			ret = E_OK;
		}
		else if(INTERRUPT_EXTERNAL_INT1 == int_obj->source)
		{
			Ext_INT1_Disable();
			ret = E_OK;
		}
		else if(INTERRUPT_EXTERNAL_INT2 == int_obj->source)
		{
			Ext_INT2_Disable();
			ret = E_OK;
		}
		else
		{
			ret = E_NOT_OK;
		}
	}
	return ret;
}
Std_ReturnType Interrupt_External_CallBack(interrupt_INTx_t *int_obj,void * Copy_pvidParameter)
{
	Std_ReturnType ret = E_NOT_OK;

	if (NULL == int_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		EXTI_Fun[int_obj->source] = int_obj->EXT_InterruptHandler;
		EXTI_ApvidGenericparameter[int_obj->source] = Copy_pvidParameter;
		ret = E_OK;
	}

	return ret;
}
ISR(VECT_INT0)
{
	if (NULL == EXTI_Fun[INTERRUPT_EXTERNAL_INT0])
	{
		
	}
	else
	{
		EXTI_Fun[INTERRUPT_EXTERNAL_INT1] (EXTI_ApvidGenericparameter[0]);
	}
}

ISR(VECT_INT1)
{
	if (NULL == EXTI_Fun[INTERRUPT_EXTERNAL_INT1])
	{
		
	}
	else
	{
		EXTI_Fun[INTERRUPT_EXTERNAL_INT1] (EXTI_ApvidGenericparameter[INTERRUPT_EXTERNAL_INT1]);
	}
}

ISR(VECT_INT2)
{
	if (NULL == EXTI_Fun[INTERRUPT_EXTERNAL_INT2])
	{
		
	}
	else
	{
		EXTI_Fun[INTERRUPT_EXTERNAL_INT2] (EXTI_ApvidGenericparameter[INTERRUPT_EXTERNAL_INT2]);
	}
}

static Std_ReturnType Interrupt_External_state(interrupt_INTx_t *int_obj)
{
	Std_ReturnType ret = E_NOT_OK;
	if(NULL == int_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		if(INTERRUPT_EXTERNAL_INT0 == int_obj->source)
		{
			MCUCR &= 0xFC;
			switch(int_obj->state)
			{
				case LOW_LEVEL:
					MCUCR |= LOW_LEVEL;
					break;
				case ANY_LOGIC:
					MCUCR |= ANY_LOGIC;
					break;
				case FALLING_EDGE :
					MCUCR |= FALLING_EDGE;
					break;
				case RISING_EDGE :
					MCUCR |= RISING_EDGE;
					break;
				default:
				ret = E_NOT_OK;
			}
		}
		else if(INTERRUPT_EXTERNAL_INT1 == int_obj->source)
		{
			MCUCR &= 0xF3;
			switch(int_obj->state)
			{
				case LOW_LEVEL:
					MCUCR |= (LOW_LEVEL<<2);
					break;
				case ANY_LOGIC:
					MCUCR |= (ANY_LOGIC<<2);
					break;
				case FALLING_EDGE :
					MCUCR |= (FALLING_EDGE<<2);
					break;
				case RISING_EDGE :
					MCUCR |= (RISING_EDGE<<2);
					break;
				default:
					ret = E_NOT_OK;
			}
		}
		else if(INTERRUPT_EXTERNAL_INT2 == int_obj->source)
		{
			MCUCSR &= 0xBF;
			ret = E_OK;
			switch(int_obj->state)
			{
				case FALLING_EDGE :
					MCUCSR |= (0<<6);
					break;
				case RISING_EDGE :
					MCUCSR |= (1<<6);
					break;
				default:
					ret = E_NOT_OK;
			}
		}
		else
		{
			ret = E_NOT_OK;
		}
	}
	return ret;
}