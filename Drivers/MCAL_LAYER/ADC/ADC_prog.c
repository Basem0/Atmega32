/*
 * ADC_prog.c
 *
 * Created: 2/14/2024 2:35:00 AM
 *  Author: ahmed
 */ 

#include "ADC_init.h"
#include "ADC_config.h"
#include "ADC_priv.h"



static void(*ADC_PNotificationFunc)(void)=NULL;
static uint16* ADC_Reading=NULL;
static uint8 ADC_BusyState=IDLE;

Std_ReturnType ADC_Init(void)
{
	Std_ReturnType ret =E_NOT_OK;
	//voltage reference selection
#if (ADC_REFRENCE_SELECTION==ADC_AREF)
	CLEAR_BIT(ADMUX,ADMUX_REFS0);
	CLEAR_BIT(ADMUX,ADMUX_REFS1);
#elif(ADC_REFRENCE_SELECTION==ADC_AVCC)
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLEAR_BIT(ADMUX,ADMUX_REFS1);
#elif(ADC_REFRENCE_SELECTION==ADC_INTERNL_REF)
	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);
#else
#error"Wrong selection"
#endif

	//left adjust
#if(ADC_ADJUSTMENT==ADC_LEFT_ADJUST)
	SET_BIT(ADMUX,ADMUX_ADLAR);
#elif(ADC_ADJUSTMENT==ADC_RIGHT_ADJUST)
	CLEAR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error"Wrong selection"
#endif
	//prescaler Select Bits
#if(ADC_PRESCALER_SELECTION==Division_Factor_2)
	CLEAR_BITS_REG(ADCSRA,PRESCALER_128);
	SET_BITS_REG(ADCSRA,PRESCALER_2);
#elif(ADC_PRESCALER_SELECTION==Division_Factor_4)
	CLEAR_BITS_REG(ADCSRA,PRESCALER_128);
	SET_BITS_REG(ADCSRA,PRESCALER_4);
#elif(ADC_PRESCALER_SELECTION==Division_Factor_8)
	CLEAR_BITS_REG(ADCSRA,PRESCALER_128);
	SET_BITS_REG(ADCSRA,PRESCALER_8);
#elif(ADC_PRESCALER_SELECTION==Division_Factor_16)
	CLEAR_BITS_REG(ADCSRA,PRESCALER_128);
	SET_BITS_REG(ADCSRA,PRESCALER_16);
#elif(ADC_PRESCALER_SELECTION==Division_Factor_32)
	CLEAR_BITS_REG(ADCSRA,PRESCALER_128);
	SET_BITS_REG(ADCSRA,PRESCALER_32);
#elif(ADC_PRESCALER_SELECTION==Division_Factor_64)
	CLEAR_BITS_REG(ADCSRA,PRESCALER_128);
	SET_BITS_REG(ADCSRA,PRESCALER_64);
#elif(ADC_PRESCALER_SELECTION==Division_Factor_128)
	CLEAR_BITS_REG(ADCSRA,PRESCALER_128);
	SET_BITS_REG(ADCSRA,PRESCALER_128);
#else
#error"Wrong selection"
#endif

	//ADC enable
#if(ADC_INITIAL_STATE==ADC_ENABLE)
	SET_BIT(ADCSRA,ADCSRA_ADEN);
#elif(ADC_INITIAL_STATE==ADC_DISABLE)
	CLEAR_BIT(ADCSRA,ADCSRA_ADEN);
#else
#error"Wrong selection"
#endif

#if(ADC_AUTO_TRIGGER_SOURCE==ADC_FREE_RUNNING_MODE)
	CLEAR_BITS_REG(SFIOR,ADC_TIMER1_CAPTURE_EVENT);
#elif(ADC_AUTO_TRIGGER_SOURCE==ADC_ANALOG_COMPARATOR)
	CLEAR_BITS_REG(SFIOR,ADC_TIMER1_CAPTURE_EVENT);
	SET_BITS_REG(SFIOR,ADC_TIMER1_CAPTURE_EVENT);
#elif(ADC_AUTO_TRIGGER_SOURCE==ADC_EXTERNAL_INTERRUPT_REQUIST0)
	CLEAR_BITS_REG(SFIOR,ADC_TIMER1_CAPTURE_EVENT);
	SET_BITS_REG(SFIOR,ADC_EXTERNAL_INTERRUPT_REQUIST0);
#elif(ADC_AUTO_TRIGGER_SOURCE==ADC_TIMER0_COPMPARE_MATCH)
	CLEAR_BITS_REG(SFIOR,ADC_TIMER1_CAPTURE_EVENT);
	SET_BITS_REG(SFIOR,ADC_ADC_TIMER0_COPMPARE_MATCH);
#elif(ADC_AUTO_TRIGGER_SOURCE==ADC_TIMER0_OVERFLOW)
	CLEAR_BITS_REG(SFIOR,ADC_TIMER1_CAPTURE_EVENT);
	SET_BITS_REG(SFIOR,ADC_TIMER0_OVERFLOW);
#elif(ADC_AUTO_TRIGGER_SOURCE==ADC_TIMER1_COPMPARE_MATCH_B)
	CLEAR_BITS_REG(SFIOR,ADC_TIMER1_CAPTURE_EVENT);
	SET_BITS_REG(SFIOR,ADC_ADC_TIMER1_COPMPARE_MATCH_B);
#elif(ADC_AUTO_TRIGGER_SOURCE==ADC_TIMER1_OVERFLOW)
	CLEAR_BITS_REG(SFIOR,ADC_TIMER1_CAPTURE_EVENT);
	SET_BITS_REG(SFIOR,ADC_TIMER1_OVERFLOW);
#elif(ADC_AUTO_TRIGGER_SOURCE==ADC_TIMER1_CAPTURE_EVENT)
	SET_BITS_REG(SFIOR,ADC_TIMER1_CAPTURE_EVENT);
#else
#error"Wrong selection"
#endif

	ret =E_OK;

	return ret;
}

Std_ReturnType ADC_ConversionSync (uint8 channel , uint16* value)
{
	Std_ReturnType ret = E_NOT_OK;
	if(ADC_BusyState==IDLE)
	{
		uint32 Local_Counter=0;
		if(value !=NULL)
		{
			if(channel <= GND)
			{
				ADC_BusyState = BUSY;

				CLEAR_BITS_REG(ADMUX,0X1F);
				SET_BITS_REG(ADMUX,channel);
				SET_BIT(ADCSRA,ADCSRA_ADSC);
				while((CHECK_BIT(ADCSRA,ADCSRA_ADIF)==0)&&(Local_Counter<ADC_U32TIME_OUT))
				{Local_Counter++;}

				if(Local_Counter!=ADC_U32TIME_OUT)
				{
					SET_BIT(ADCSRA,ADCSRA_ADIF);
					if(ADC_RESOLUTION == ADC_10BIT_RESOLUTION)
					{
						*value=ADCH;
					}
					else
					{
						*value = (uint8*)ADCH;

					}
				}
				ADC_BusyState=IDLE;

				ret = E_OK;
			}
			else
			{
				ret = E_NOT_OK;
			}
		}
		else
		{
			ret = E_NOT_OK;
		}
	}
	else
	{
		ret = E_NOT_OK;
	}
	return ret;
}

Std_ReturnType ADC_ConversionAsync (uint8 channel , uint16* value,void(*PNotificationFunc)(void))
{
	Std_ReturnType ret = E_NOT_OK;
	if(ADC_BusyState==IDLE)
	{
	if((value !=NULL)&& (PNotificationFunc!=NULL))
	{
		if(channel<=GND)
		{
			ADC_BusyState=BUSY;
			ADC_Reading=value;
			ADC_PNotificationFunc=PNotificationFunc;
			CLEAR_BITS_REG(ADMUX,0X1F);
			SET_BITS_REG(ADMUX,channel);
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			ret = E_NOT_OK;
		}
	}
	else
	{
		ret = E_NOT_OK;
	}
	}
	else
	{
		ret = E_NOT_OK;
	}
	return ret;

}

ISR(VECT_ADC)
{
	if((ADC_PNotificationFunc!=NULL)&&(ADC_Reading!=NULL))
	{
		if(ADC_ADJUSTMENT==ADC_LEFT_ADJUST)
		{
			*ADC_Reading=ADCH;
		}
		else
		{
			*ADC_Reading=(uint8*)ADCH;
			//*ADC_pu8Reading=ADCH;
		}

		ADC_BusyState=IDLE;

		ADC_PNotificationFunc();
		CLEAR_BIT(ADCSRA,ADCSRA_ADIE);

	}
}