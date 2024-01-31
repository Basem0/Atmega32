/*
 * hal_dio_cfg.h
 *
 * Created: 1/30/2024 3:16:59 PM
 *  Author: ahmed
 */ 


#ifndef HAL_GPIO_CFG_H_
#define HAL_GPIO_CFG_H_

#include "../Std_Types.h"

#define CONFIG_ENABLE   0x01
#define CONFIG_DISABLE  0x00

#define GPIO_PORT_PIN_CONFIGURATIONS  CONFIG_ENABLE
#define GPIO_PORT_CONFIGURATIONS      CONFIG_ENABLE

#define PORTA  ((volatile uint8*)0x3B)
#define PINA   ((volatile uint8*)0x39)
#define DDRA   ((volatile uint8*)0x3A)

#define PORTB  ((volatile uint8*)0x38)
#define PINB   ((volatile uint8*)0x36)
#define DDRB   ((volatile uint8*)0x37)

#define PORTC  ((volatile uint8*)0x35)
#define PINC   ((volatile uint8*)0x33)
#define DDRC   ((volatile uint8*)0x34)

#define PORTD  ((volatile uint8*)0x32)
#define PIND   ((volatile uint8*)0x30)
#define DDRD   ((volatile uint8*)0x31)


#endif /* HAL_DIO_CFG_H_ */