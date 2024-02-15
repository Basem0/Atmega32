/*
 * ADC_priv.h
 *
 * Created: 2/14/2024 2:21:21 AM
 *  Author: ahmed
 */ 


#ifndef ADC_PRIV_H_
#define ADC_PRIV_H_

#define ADMUX							*((volatile uint8*)0x27)
#define ADCSRA							*((volatile uint8*)0x26)
#define ADCH							*((volatile uint8*)0x25)
#define ADCL						    *((volatile uint8*)0x24)
#define SFIOR							*((volatile uint8*)0x26)

#define ADMUX_ADLAR			    5
#define ADMUX_REFS0				6		
#define ADMUX_REFS1				7		

/*ADC Control and Status Register A*/

#define ADCSRA_ADIE						3	
#define ADCSRA_ADIF						4		
#define ADCSRA_ADATE				    5		
#define ADCSRA_ADSC			        	6		
#define ADCSRA_ADEN						7		

#define SFIOR_ADTS_0					5
#define SFIOR_ADTS_1					6
#define SFIOR_ADTS_2				    7

//voltage reference
#define ADC_AREF						0
#define ADC_AVCC				        1
#define	ADC_INTERNL_REF					3


//Analog channel&gain selection bits
#define SingleEnded_ADC0					0
#define SingleEnded_ADC1					1
#define SingleEnded_ADC2					2
#define SingleEnded_ADC3					3
#define SingleEnded_ADC4					4
#define SingleEnded_ADC5					5
#define SingleEnded_ADC6					6
#define SingleEnded_ADC7					7

#define Differential_ADC0_ADC0_10x			8
#define Differential_ADC1_ADC0_10x			9
#define Differential_ADC0_ADC0_200x			10
#define Differential_ADC1_ADC0_200x			11
#define Differential_ADC2_ADC2_10x			12
#define Differential_ADC3_ADC2_10x			13
#define Differential_ADC2_ADC2_200x			14
#define Differential_ADC3_ADC2_200x			15
#define Differential_ADC0_ADC1_1x			16
#define Differential_ADC1_ADC1_1x			17
#define Differential_ADC2_ADC1_1x			18
#define Differential_ADC3_ADC1_1x			19
#define Differential_ADC4_ADC1_1x			20
#define Differential_ADC5_ADC1_1x			21
#define Differential_ADC6_ADC1_1x			22
#define Differential_ADC7_ADC1_1x			23
#define Differential_ADC0_ADC2_1x			24
#define Differential_ADC1_ADC2_1x			25
#define Differential_ADC2_ADC2_1x			26
#define Differential_ADC3_ADC2_1x			27
#define Differential_ADC4_ADC2_1x			28
#define Differential_ADC5_ADC2_1x			29

#define VOLTAGE_1_22						30
#define GND									31

typedef enum{
	PRESCALER_2 = 0,
	PRESCALER_4,
	PRESCALER_8,
	PRESCALER_16,
	PRESCALER_32,
	PRESCALER_64,
	PRESCALER_128,
}PERSCALER_T;

#define ADC_FREE_RUNNING_MODE				0
#define ADC_ANALOG_COMPARATOR				1
#define ADC_EXTERNAL_INTERRUPT_REQUIST0		2
#define ADC_TIMER0_COPMPARE_MATCH			3
#define ADC_TIMER0_OVERFLOW					4
#define ADC_TIMER1_COPMPARE_MATCH_B			5
#define ADC_TIMER1_OVERFLOW					6
#define ADC_TIMER1_CAPTURE_EVENT			7

#define ADC_LEFT_ADJUST						1
#define ADC_RIGHT_ADJUST					0

#define ADC_8BIT_RESOLUTION					8
#define ADC_10BIT_RESOLUTION				10

#define ADC_DISABLE							0
#define ADC_ENABLE							1

#define ADC_AUTO_TRIGGER_DISABLE			0
#define ADC_AUTO_TRIGGER_ENABLE				1

#define IDLE								0
#define BUSY								1



#endif /* ADC_PRIV_H_ */