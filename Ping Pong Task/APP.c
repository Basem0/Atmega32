/*
 * main.c
 *
 * Created: 1/30/2024 3:11:29 PM
 *  Author: ahmed
 */ 

#include "APP.h"

#define GAME_ACTIVE 1
#define GAME_DEACTIVE 0
void restart();
uint8 rocket[] = {
	0x0E,
	0x0E,
	0x04,
	0x0E,
	0x15,
	0x04,
	0x0A,
	0x11
};
uint8 ball[] = {
	0x00,
	0x0A,
	0x00,
	0x04,
	0x11,
	0x0E,
	0x00,
	0x00
};

chr_lcd_4bit_t lcd = {
	.lcd_rs = { PORTA_INDEX, GPIO_PIN0, GPIO_DIRECTION_OUTPUT, GPIO_LOW },
	.lcd_en = { PORTA_INDEX, GPIO_PIN1, GPIO_DIRECTION_OUTPUT, GPIO_LOW },
	.lcd_data = {
		{ PORTA_INDEX, GPIO_PIN2, GPIO_DIRECTION_OUTPUT, GPIO_LOW },
		{ PORTA_INDEX, GPIO_PIN3, GPIO_DIRECTION_OUTPUT, GPIO_LOW },
		{ PORTA_INDEX, GPIO_PIN4, GPIO_DIRECTION_OUTPUT, GPIO_LOW },
		{ PORTA_INDEX, GPIO_PIN5, GPIO_DIRECTION_OUTPUT, GPIO_LOW }
	}
};

EXTI_t EXT_INTx[3] = {
	{EXTI_Handler_0, ACTIVE, RISING_EDGE, INTERRUPT_EXTERNAL_INT0},
	{EXTI_Handler_1, ACTIVE, RISING_EDGE, INTERRUPT_EXTERNAL_INT1},
	{NULL, DEACTIVE}
};

sint8 rocket1_index = 2;
sint8 rocket1_mod = 1;
sint8 rocket2_index = 3;
sint8 rocket2_mod = -1;

sint8 game_flag = GAME_ACTIVE;
sint8 ball_row = 2;
sint8 ball_row_mod = 1;
sint8 ball_col = 2;
sint8 ball_col_mod = 2;

uint8 message1[] = "PLAYER1 Win";
uint8 message2[] = "PLAYER2 Win";
uint8 message3[] = "Press To Play";
uint8 player1_flag = DEACTIVE;
uint8 player2_flag = DEACTIVE;
int main(void)
{
	
	Std_ReturnType ret = E_OK;
	ret = lcd_4bit_intialize(&lcd);
	ret = EXTI_Init(EXT_INTx);
	lcd_4bit_send_custom_char(&lcd,ball_row,ball_col,ball,2);

    while(1)
    {
		if(GAME_ACTIVE == game_flag)
		{
			lcd_4bit_send_char_data_pos(&lcd, ball_row, ball_col, ' ');
			ball_row += ball_row_mod;
			ball_col += ball_col_mod;
			if(ball_row == 4) ball_row_mod = -1;
			if(ball_row == 1) ball_row_mod = 1;
			if(ball_col == 20){
				if(ball_row == rocket2_index){
					 ball_col -= 2;
					 ball_col_mod = -2;
				}
				else
				{
					game_flag = GAME_DEACTIVE;
					player1_flag = ACTIVE;
				}	 
			}

			if(ball_col == 0){
				if(ball_row == rocket1_index)
				{
					ball_col +=2;
					ball_col_mod = 2;
				}
				else
				{
					 game_flag = GAME_DEACTIVE;
					 player2_flag = ACTIVE;
				}
			}
			lcd_4bit_send_custom_char(&lcd,ball_row,ball_col,ball,2);
			_delay_ms(500);
			if(ACTIVE == player1_flag)
			{
				lcd_4bit_send_command(&lcd,_LCD_CLEAR);
				lcd_4bit_send_char_data(&lcd,' ');
				lcd_4bit_send_string_pos(&lcd,2,6,message1);
				lcd_4bit_send_string_pos(&lcd,3,4,message3);
			}
			if(ACTIVE == player2_flag)
			{
				lcd_4bit_send_command(&lcd,_LCD_CLEAR);
				lcd_4bit_send_char_data(&lcd,' ');
				lcd_4bit_send_string_pos(&lcd,2,6,message2);
				lcd_4bit_send_string_pos(&lcd,3,4,message3);
			}
			
		}
		else
		{
			
			
		}

    }
	
}
void EXTI_Handler_0()
{
	if(game_flag == GAME_ACTIVE)
	{
		if(rocket1_index == 1)		rocket1_mod = 1;
		else if(rocket1_index == 4) rocket1_mod = -1;
		lcd_4bit_send_char_data_pos(&lcd, rocket1_index, 1, ' ');
		rocket1_index += rocket1_mod;
		lcd_4bit_send_custom_char(&lcd,rocket1_index,1,rocket,1);
		lcd_4bit_send_custom_char(&lcd,rocket2_index,20,rocket,1);
	}
	else
	{
		restart();
	}
}
void EXTI_Handler_1()
{
	if(game_flag == GAME_ACTIVE)
	{
		if(rocket2_index == 1)		rocket2_mod = 1;
		else if(rocket2_index == 4) rocket2_mod = -1;
		lcd_4bit_send_char_data_pos(&lcd, rocket2_index, 20, ' ');
		rocket2_index += rocket2_mod;
		lcd_4bit_send_custom_char(&lcd,rocket1_index,1,rocket,1);
		lcd_4bit_send_custom_char(&lcd,rocket2_index,20,rocket,1);
	}
	else
	{
		restart();
	}
}
void restart(){
	lcd_4bit_send_command(&lcd, _LCD_CLEAR);
	rocket1_index = 2;
	rocket1_mod = 1;
	rocket2_index = 3;
	rocket2_mod = -1;
	ball_row = 2;
	ball_row_mod = 1;
	ball_col = 2;
	ball_col_mod = 2;
	game_flag = GAME_ACTIVE;
	lcd_4bit_send_custom_char(&lcd,rocket1_index,1,rocket,1);
	lcd_4bit_send_custom_char(&lcd,rocket2_index,20,rocket,1);
}
