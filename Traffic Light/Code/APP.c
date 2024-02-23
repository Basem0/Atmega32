/*
 * main.c
 *
 * Created: 1/30/2024 3:11:29 PM
 *  Author: ahmed
 */ 

#include "APP.h"

void normal();
void algotithm();
void RED_LightCar();
void GREEN_LightCar();
void RED_LightR();
void GREEN_LightR();
void toggle_yellow1(void);
void toggle_yellow2(void);
void people_traffic();

EXTI_t EXT_INTx[3] = {
	{algotithm, ACTIVE, RISING_EDGE, INTERRUPT_EXTERNAL_INT0},
	{NULL, DEACTIVE},
	{NULL, DEACTIVE}
};
led_t R_red = {
	.port_name = PORTC_INDEX,
	.pin = GPIO_PIN0,
	.led_status = LED_OFF
};
led_t R_yellow = {
	.port_name = PORTC_INDEX,
	.pin = GPIO_PIN1,
	.led_status = LED_OFF
};
led_t R_green = {
	.port_name = PORTC_INDEX,
	.pin = GPIO_PIN2,
	.led_status = LED_OFF
};
led_t Car_red = {
	.port_name = PORTC_INDEX,
	.pin = GPIO_PIN3,
	.led_status = LED_OFF
};
led_t Car_yellow = {
	.port_name = PORTC_INDEX,
	.pin = GPIO_PIN4,
	.led_status = LED_OFF
};
led_t Car_green = {
	.port_name = PORTC_INDEX,
	.pin = GPIO_PIN5,
	.led_status = LED_OFF
};

uint8 carGreenFlag = 0 , carRedFlag = 0 , carYellowFlag = 0;


int main(void)
{
	Std_ReturnType ret = E_OK;
	ret = led_initialize(&Car_green);
	ret = led_initialize(&Car_red);
	ret = led_initialize(&Car_yellow);
	ret = led_initialize(&R_green);
	ret = led_initialize(&R_red);
	ret = led_initialize(&R_yellow);
	ret = EXTI_Init(EXT_INTx);
	ret = TIMER0_Init();
	while(1)
	{
		normal();
	}
}


void algotithm(void*Copy_pvoidArg)
{
	if(carRedFlag==1)
	{
		RED_LightCar();
		GREEN_LightR();
		TIMER0_Delay_ms_Synch(5000);
		led_turn_off(&Car_green);
		toggle_yellow2();
		GREEN_LightCar();
		RED_LightR();
		TIMER0_Delay_ms_Synch(5000);
		toggle_yellow1();
		RED_LightCar();
		TIMER0_Delay_ms_Synch(2500);
	}
	else if(carGreenFlag==1)
	{
		RED_LightR();
		GREEN_LightCar();
		TIMER0_Delay_ms_Synch(5000);
		led_turn_off(&Car_green);
		toggle_yellow2();
		RED_LightCar();
		GREEN_LightR();
		TIMER0_Delay_ms_Synch(5000);
		GREEN_LightR();
		toggle_yellow2();
		RED_LightR();
		GREEN_LightCar();
		TIMER0_Delay_ms_Synch(2500);
	}
	else if(carYellowFlag==1)
	{
		toggle_yellow2();
		RED_LightCar();
		GREEN_LightR();
		TIMER0_Delay_ms_Synch(5000);
		GREEN_LightR();
		toggle_yellow2();
		RED_LightR();
		GREEN_LightCar();
		TIMER0_Delay_ms_Synch(5000);
	}
}
void RED_LightCar()
{
	carRedFlag=1;
	carYellowFlag=0;
	carGreenFlag=0;
	led_turn_off(&Car_yellow);
	led_turn_off(&Car_green);
	led_turn_on(&Car_red);
}
void GREEN_LightCar()
{
	carGreenFlag=1;
	carRedFlag=0;
	carYellowFlag=0;
	led_turn_off(&Car_red);
	led_turn_off(&Car_yellow);
	led_turn_on(&Car_green);
}
void RED_LightR()
{
	carRedFlag=1;
	carYellowFlag=0;
	carGreenFlag=0;
	led_turn_off(&R_yellow);
	led_turn_off(&R_green);
	led_turn_on(&R_red);
}
void GREEN_LightR()
{
	carGreenFlag=1;
	carRedFlag=0;
	carYellowFlag=0;
	led_turn_off(&R_red);
	led_turn_off(&R_yellow);
	led_turn_on(&R_green);
}
void toggle_yellow1()
{
	carYellowFlag=1;
	carGreenFlag=0;
	carRedFlag=0;
	uint8 counter;
	for(counter=0;counter<10;counter++)
	{
		led_turn_off(&Car_red);
		led_turn_off(&Car_green);
		led_turn_toggle(&Car_yellow);
		TIMER0_Delay_ms_Synch(500);
	}
}
void toggle_yellow2()
{
	carYellowFlag=1;
	carGreenFlag=0;
	carRedFlag=0;
	led_turn_off(&Car_red);
	led_turn_off(&R_red);
	led_turn_off(&Car_green);
	led_turn_off(&R_green);
	uint8 counter;
	for(counter=0;counter<10;counter++)
	{
		led_turn_toggle(&Car_yellow);
		led_turn_toggle(&R_yellow);
		TIMER0_Delay_ms_Synch(500);
	}
}
void normal()
{
	GREEN_LightCar();
	TIMER0_Delay_ms_Synch(5000);
	toggle_yellow1();
	RED_LightCar();
	TIMER0_Delay_ms_Synch(5000);
	toggle_yellow1();
}
