/*
 * main.c
 *
 * Created: 1/30/2024 3:11:29 PM
 *  Author: ahmed
 */ 

#include "APP.h"

chr_lcd_4bit_t lcd = {
	.lcd_rs.port = PORTD_INDEX,
	.lcd_rs.pin = GPIO_PIN0,
	.lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
	.lcd_rs.logic = GPIO_LOW,
	.lcd_en.port = PORTD_INDEX,
	.lcd_en.pin = GPIO_PIN1,
	.lcd_en.direction = GPIO_DIRECTION_OUTPUT,
	.lcd_en.logic = GPIO_LOW,
	.lcd_data[0].port = PORTC_INDEX,
	.lcd_data[0].pin = GPIO_PIN0,
	.lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
	.lcd_data[0].logic = GPIO_LOW,
	.lcd_data[1].port = PORTC_INDEX,
	.lcd_data[1].pin = GPIO_PIN1,
	.lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
	.lcd_data[1].logic = GPIO_LOW,
	.lcd_data[2].port = PORTC_INDEX,
	.lcd_data[2].pin = GPIO_PIN2,
	.lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
	.lcd_data[2].logic = GPIO_LOW,
	.lcd_data[3].port = PORTC_INDEX,
	.lcd_data[3].pin = GPIO_PIN3,
	.lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
	.lcd_data[3].logic = GPIO_LOW
};

EXTI_t EXT_INTx[3] = {
	{EXTI_Handler_0, ACTIVE, RISING_EDGE, INTERRUPT_EXTERNAL_INT0},
	{EXTI_Handler_1, ACTIVE, RISING_EDGE, INTERRUPT_EXTERNAL_INT1},
	{NULL, DEACTIVE}
};

uint16 value;
uint8 word[] = "Temp = ";
uint8 temp[];

int main(void)
{
	
	Std_ReturnType ret = E_OK;
	ret = EXTI_Init(EXT_INTx);
	ret = ADC_Init();
	ret	= lcd_4bit_intialize(&lcd);
	ret = lcd_4bit_send_string(&lcd, word);
    while(1)
    {

	ret =  ADC_ConversionSync (SingleEnded_ADC0 , &value);
	value = value * 1.95313f;
	ret = convert_uint16_to_string(value, temp);
	ret = lcd_4bit_send_string_pos(&lcd, 1, 8, temp);
    }
	
}
void EXTI_Handler_0()
{

}
void EXTI_Handler_1()
{

}
