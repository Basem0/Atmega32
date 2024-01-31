/*
 * APP.h
 *
 * Created: 1/30/2024 4:17:46 PM
 *  Author: ahmed
 */ 


#ifndef APP_H_
#define APP_H_


#include "MCAL_LAYER/GPIO/hal_gpio.h"
#include "MCAL_LAYER/INTERRUPT/EXTI_Config.h"
#include "MCAL_LAYER/INTERRUPT/EXTI_int.h"
/****************** ECU DRIVERS INCLUDE ******************/ 
#include "ECU_LAYER/Led/ecu_led.h"
#include "ECU_LAYER/Lcd/ecu_chr_lcd.h"
#include "ECU_LAYER/7Segment/ecu_seven_segment.h"
#include "ECU_LAYER/Button/ecu_button.h"
#include "ECU_LAYER/Keypad/ecu_keypad.h"
#include "ECU_LAYER/dc_motor/ecu_dc_motor.h"
#include "ECU_LAYER/Relay/ecu_relay.h"
/*********************************************************/ 
void EXTI_Handler_0();
void EXTI_Handler_1();

#endif /* APP_H_ */