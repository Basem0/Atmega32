/*
 * Timer0.c
 *
 * Created: 2/22/2024 3:05:04 AM
 *  Author: ahmed
 */ 

#include "Timer0_Config.h"
#include "../INTERRUPT/EXTI_int.h"
#include "../Std_Types.h"
#include "../Std_Libraries.h"
#include "../GPIO/hal_gpio.h"
#include "Timer0_Config.h"
#include "Timer0/Timer0_Register.h"


volatile static void (* TIMER_OFV_Fun)(void*)=NULL;
volatile static void* TIMER_OFV_FunArg = NULL;

volatile static uint32  u8_OFV_Number=0;
volatile static uint8  TIMER0_Preload = 0;
volatile static uint32 ISR_Counter=0;

//=================================================================================================================
Std_ReturnType TIMER0_Init(void)
{
	Std_ReturnType ret = E_NOT_OK;

	#if (TIMER_CLOCK_SELECT==TIMER_NO_CLOCK)
	CLEAR_BIT(TCCR0,TCCR0_CS00);
	CLEAR_BIT(TCCR0,TCCR0_CS01);
	CLEAR_BIT(TCCR0,TCCR0_CS10);

	#elif (TIMER_CLOCK_SELECT==TIMER_NO_Prescaler)
	SET_BIT(TCCR0,TCCR0_CS00);
	CLEAR_BIT(TCCR0,TCCR0_CS01);
	CLEAR_BIT(TCCR0,TCCR0_CS10);

	#elif (TIMER_CLOCK_SELECT==TIMER_Prescaler8)
	CLEAR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLEAR_BIT(TCCR0,TCCR0_CS10);

	#elif (TIMER_CLOCK_SELECT==TIMER_Prescaler64)
	SET_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLEAR_BIT(TCCR0,TCCR0_CS10);

	#elif (TIMER_CLOCK_SELECT==TIMER_Prescaler256)
	CLEAR_BIT(TCCR0,TCCR0_CS00);
	CLEAR_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS10);

	#elif (TIMER_CLOCK_SELECT==TIMER_Prescaler1024)
	SET_BIT(TCCR0,TCCR0_CS00);
	CLEAR_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS10);

	#elif (TIMER_CLOCK_SELECT==TIMER_EXTERNAL_CLOCK_SOURCE_FALING)
	CLEAR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS10);

	#elif (TIMER_CLOCK_SELECT==TIMER_EXTERNAL_CLOCK_SOURCE_RISING)
	CLEAR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS10);

	#else
	#error "Wrong Clock Selection"
	#endif

	#if (WAVEFORM_GENERATION_MODE == TIMER0_NORMAL_MODE)
	CLEAR_BIT(TCCR0,TCCR0_WGM00);
	CLEAR_BIT(TCCR0,TCCR0_WGM01);
	
	#if (COMPARE_MATCH_OUTPUT_MODE == OC0_DISCONNECTED )
	CLEAR_BIT(TCCR0,TCCR0_COM00);
	CLEAR_BIT(TCCR0,TCCR0_COM01);

	#else
	#error "OC0 IS CONNECTED"
	#endif

	#elif (WAVEFORM_GENERATION_MODE == TIMER0_PHASE_CORRECT_PWM_MODE)
	SET_BIT(TCCR0,TCCR0_WGM00);
	CLEAR_BIT(TCCR0,TCCR0_WGM01);
	#if (COMPARE_MATCH_OUTPUT_MODE == OC0_DISCONNECTED )
	CLEAR_BIT(TCCR0,TCCR0_COM00);
	CLEAR_BIT(TCCR0,TCCR0_COM01);

	#elif (COMPARE_MATCH_OUTPUT_MODE == OC0_NON_INVERTING_MODE)
	CLEAR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

	#elif (COMPARE_MATCH_OUTPUT_MODE == OC0_INVERTING_MODE)
	SET_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

	#else
	#error "wrong OC0 selection"
	#endif

	#elif (WAVEFORM_GENERATION_MODE == TIMER0_CTC_MODE)
	CLEAR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
	
	#if (COMPARE_MATCH_OUTPUT_MODE == OC0_DISCONNECTED )
	CLEAR_BIT(TCCR0,TCCR0_COM00);
	CLEAR_BIT(TCCR0,TCCR0_COM01);

	#elif (COMPARE_MATCH_OUTPUT_MODE == OC0_TOGGLE)
	SET_BIT(TCCR0,TCCR0_COM00);
	CLEAR_BIT(TCCR0,TCCR0_COM01);
	#elif (COMPARE_MATCH_OUTPUT_MODE == OC0_CLEAR)
	CLEAR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

	#elif (COMPARE_MATCH_OUTPUT_MODE == OC0_SET)
	SET_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

	#else
	#error "wrong OC0 selection"
	#endif

	#elif (WAVEFORM_GENERATION_MODE == TIMER0_FAST_PWM_MODE)
	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
	#if (COMPARE_MATCH_OUTPUT_MODE == OC0_DISCONNECTED )
	CLEAR_BIT(TCCR0,TCCR0_COM00);
	CLEAR_BIT(TCCR0,TCCR0_COM01);

	#elif (COMPARE_MATCH_OUTPUT_MODE == OC0_NON_INVERTING_MODE)
	CLEAR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

	#elif (COMPARE_MATCH_OUTPUT_MODE == OC0_INVERTING_MODE)
	SET_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

	#else
	#error "wrong OC0 selection"

	#endif

	#else
	#error "Waveform Generation Mode Is Wrong"
	#endif

	CLEAR_BIT(TCCR0,TCCR0_FOC0);
	
	ret=E_OK;
	return ret;
}

Std_ReturnType TIMER0_Delay_ms_Synch(uint32 delay)
{
	Std_ReturnType ret = E_NOT_OK;

	#if ((TIMER_CLOCK_SELECT == TIMER_NO_Prescaler || TIMER_CLOCK_SELECT == TIMER_Prescaler8 || TIMER_CLOCK_SELECT == TIMER_Prescaler64 || TIMER_CLOCK_SELECT == TIMER_Prescaler256 || TIMER_CLOCK_SELECT == TIMER_Prescaler1024)&&WAVEFORM_GENERATION_MODE == TIMER0_NORMAL_MODE)
	f32 OVF_TIME=TIMER0_OVF_Counter*((f32)TIMER_CLOCK_SELECT/TIMER0_F_CPU);
	f32 OVF_Number=delay/OVF_TIME;
	if ((OVF_Number - ((uint32)OVF_Number)) > 0 )
	{
		TCNT0=(OVF_Number - ((uint32)OVF_Number))*OVF_TIME;
		uint8 u8_OFV_Number=(uint32)OVF_Number+1;

		while(u8_OFV_Number--)
		{
			while(CHECK_BIT(TIFR,TIFR_TOV0)==0);
			SET_BIT(TIFR,TIFR_TOV0);
		}
	}
	else
	{
		uint8 u8_OFV_Number=(uint32)OVF_Number;
		while(u8_OFV_Number--)
		{
			while(CHECK_BIT(TIFR,TIFR_TOV0)==0);
			SET_BIT(TIFR,TIFR_TOV0);
		}
	}
	#elif ((TIMER_CLOCK_SELECT == TIMER_NO_Prescaler || TIMER_CLOCK_SELECT == TIMER_Prescaler8 || TIMER_CLOCK_SELECT == TIMER_Prescaler64 || TIMER_CLOCK_SELECT == TIMER_Prescaler256 || TIMER_CLOCK_SELECT == TIMER_Prescaler1024)&&WAVEFORM_GENERATION_MODE == TIMER0_CTC_MODE)
	f32 OVF_TIME=TIMER0_OVF_Counter*((f32)TIMER_CLOCK_SELECT/TIMER0_F_CPU);
	TIMER0_Preload =(delay/OVF_TIME)*OVF_TIME;
	OCR0=TIMER0_Preload;
	
	while(CHECK_BIT(TIFR,TIFR_OCF0)==0);
	SET_BIT(TIFR,TIFR_OCF0);
	#endif

	ret=E_OK;
	return ret;
}

Std_ReturnType TIMER0_Delay_ms_Asynch(uint32 delay, void (*funCallBack)(void*), void * Copy_PvidArg)
{
	Std_ReturnType ret = E_NOT_OK;
	#if ((TIMER_CLOCK_SELECT == TIMER_NO_Prescaler || TIMER_CLOCK_SELECT == TIMER_Prescaler8 || TIMER_CLOCK_SELECT == TIMER_Prescaler64 || TIMER_CLOCK_SELECT == TIMER_Prescaler256 || TIMER_CLOCK_SELECT == TIMER_Prescaler1024)&&WAVEFORM_GENERATION_MODE == TIMER0_NORMAL_MODE)
	f32 OVF_TIME=TIMER0_OVF_Counter*((f32)TIMER_CLOCK_SELECT/TIMER0_F_CPU);
	f32 OVF_Number=delay/OVF_TIME;
	if ((OVF_Number - ((uint32)OVF_Number)) > 0 )
	{
		TIMER0_Preload =(OVF_Number - ((uint32)OVF_Number))*OVF_TIME;
		TCNT0=TIMER0_Preload;
		TIMER_OFV_Fun=funCallBack;
		TIMER_OFV_FunArg=Copy_PvidArg;
		u8_OFV_Number=(uint32)OVF_Number+1;
		ISR_Counter=0;
	}
	else
	{
		TIMER_OFV_Fun=funCallBack;
		TIMER_OFV_FunArg=Copy_PvidArg;
		u8_OFV_Number = 1;
		ISR_Counter = 0;
	}
	SET_BIT(TIMSK,TIMSK_TOIE0);
	
	#elif ((TIMER_CLOCK_SELECT == TIMER_NO_Prescaler || TIMER_CLOCK_SELECT == TIMER_Prescaler8 || TIMER_CLOCK_SELECT == TIMER_Prescaler64 || TIMER_CLOCK_SELECT == TIMER_Prescaler256 || TIMER_CLOCK_SELECT == TIMER_Prescaler1024)&&WAVEFORM_GENERATION_MODE == TIMER0_CTC_MODE)
	f32 OVF_TIME=TIMER0_OVF_Counter*((f32)TIMER_CLOCK_SELECT/TIMER0_F_CPU);
	TIMER0_Preload =(delay/OVF_TIME)*OVF_TIME;
	OCR0=TIMER0_Preload;
	TIMER_OFV_Fun=funCallBack;
	TIMER_OFV_FunArg=Copy_PvidArg;
	SET_BIT(TIMSK,TIMSK_OCIE0);

	#endif
	ret=E_OK;
	return ret;
}

Std_ReturnType TIMER0_GeneratePWM(uint8 DutyCycle)
{
	Std_ReturnType ret = E_NOT_OK;
	#if(WAVEFORM_GENERATION_MODE ==TIMER0_FAST_PWM_MODE)
	if((DutyCycle>0)||(DutyCycle<100))
	{
		#if (COMPARE_MATCH_OUTPUT_MODE == OC0_NON_INVERTING_MODE)
		f32 Local_f32OVFTime=TIMER0_OVF_Counter*((f32)TIMER_CLOCK_SELECT/TIMER0_F_CPU);
		OCR0=(DutyCycle*TIMER0_OVF_Counter/TIMER0_PERCENTAGE_RATIO);

		#elif (COMPARE_MATCH_OUTPUT_MODE == OC0_INVERTING_MODE)
		f32 Local_f32OVFTime=TIMER0_OVF_Counter*((f32)TIMER_CLOCK_SELECT/TIMER0_F_CPU);
		OCR0=Local_f32OVFTime-(DutyCycle*TIMER0_OVF_Counter/TIMER0_PERCENTAGE_RATIO);

		#endif
		ret = E_OK;
	}
	else
	{
		ret = E_NOT_OK;
	}

	#elif(WAVEFORM_GENERATION_MODE ==TIMER0_PHASE_CORRECT_PWM_MODE)
	if((DutyCycle>0)||(DutyCycle<100))
	{
		#if (COMPARE_MATCH_OUTPUT_MODE ==CLEAR_UP_COUNTING_SET_DOWN_COUNTING_OC0)
		f32 Local_f32OVFTime=TIMER0_OVF_Counter*((f32)TIMER_CLOCK_SELECT/TIMER0_F_CPU);
		OCR0=(DutyCycle*TIMER0_OVF_Counter/TIMER0_PERCENTAGE_RATIO);
		#elif (COMPARE_MATCH_OUTPUT_MODE ==SET_UP_COUNTING_CLEAR_DOWN_COUNTING_OC0)
		f32 Local_f32OVFTime=TIMER0_OVF_Counter*((f32)TIMER_CLOCK_SELECT/TIMER0_F_CPU);
		OCR0=Local_f32OVFTime-(DutyCycle*TIMER0_OVF_Counter/TIMER0_PERCENTAGE_RATIO);
		#endif
		ret = E_OK;
	}
	else
	{
		ret = E_NOT_OK;
	}

	#endif
	return ret;
}

ISR(VECT_TIMER0_OVF)
{
	if((TIMER_OFV_Fun != NULL))
	{
		ISR_Counter++;
		if(ISR_Counter==u8_OFV_Number)
		{
			TIMER_OFV_Fun(TIMER_OFV_FunArg);
		}
	}
}

ISR(VECT_TIMER0_COMP)
{
	if((TIMER_OFV_Fun != NULL))
	{
		TIMER_OFV_Fun(TIMER_OFV_FunArg);
	}
}
