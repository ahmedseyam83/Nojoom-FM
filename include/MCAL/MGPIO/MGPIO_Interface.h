/*
 * MGPIO_Interface.h
 *
 *  Created on: 22 Apr 2024
 *      Author: User
 */

#ifndef MGPIO_INTERFACE_H_
#define MGPIO_INTERFACE_H_

/*********************GENERAL MACROS*******************/
/***************PORTS**************/
#define GPIO_PORTA			0
#define GPIO_PORTB			1
#define GPIO_PORTC			2

/***************PINS**************/
#define GPIO_PIN0			0
#define GPIO_PIN1 			1
#define GPIO_PIN2 			2
#define GPIO_PIN3 			3
#define GPIO_PIN4 			4
#define GPIO_PIN5 			5
#define GPIO_PIN6 			6
#define GPIO_PIN7 			7
#define GPIO_PIN8 			8
#define GPIO_PIN9 			9
#define GPIO_PIN10			10
#define GPIO_PIN11			11
#define GPIO_PIN12			12
#define GPIO_PIN13			13
#define GPIO_PIN14			14
#define GPIO_PIN15			15

/***************PIN MODES**************/
#define GPIO_INPUT			0b00
#define GPIO_OUTPUT			0b01
#define GPIO_ALT_FUNC		0b10
#define GPIO_ANALOG			0b11

/***************OUTPUT MODES**************/
#define GPIO_PUSH_PULL		0
#define GPIO_OPED_DRAIN		1

/***************OUTPUT SPEED**************/
#define GPIO_LOW_SPEED		0b00
#define GPIO_MEDIUM_SPEED	0b01
#define GPIO_HIGH_SPEED		0b10
#define GPIO_VHIGH_SPEED	0b11


/***************INPUT MODES**************/
#define GPIO_NOPUPD			0b00
#define GPIO_PULLUP			0b01
#define GPIO_PULLDOWN		0b10

/***************ALTERNATE FUNCTIONS MODES**************/
#define GPIO_SYS_AF				0
#define GPIO_TIM1_AF			1
#define GPIO_TIM2_AF			1
#define GPIO_TIM3_AF			2
#define GPIO_TIM4_AF			2
#define GPIO_TIM5_AF			2
#define GPIO_TIM9_AF			3
#define GPIO_TIM10_AF			3
#define GPIO_TIM11_AF			3
#define GPIO_I2C1_AF			4
#define GPIO_I2C2_AF			4
#define GPIO_SPI1_AF			5
#define GPIO_SPI2_AF			5
#define GPIO_SPI3_AF			6
#define GPIO_I2S2_AF			5
#define GPIO_I2S3_AF			6
#define GPIO_USART1_AF			7
#define GPIO_USART2_AF			7
#define GPIO_USART6_AF			8
#define GPIO_OTG1_FS_AF			9
#define GPIO_SDIO_AF			12


/***************PIN VALUES**************/
#define GPIO_PIN_LOW		0
#define GPIO_PIN_HIGH		1

/***************PIN SET RESET**************/
#define GPIO_SET		1
#define GPIO_RESET		0


/************************************************************************************************/
/*									FUNCTIONS API's												*/
/************************************************************************************************/

void MGPIO_voidSetPinMode(u8 copyu8Port, u8 copyu8Pin, u8 copyu8Mode);
void MGPIO_voidSetPinOutputMode(u8 copyu8Port, u8 copyu8Pin, u8 copyu8OutputMode, u8 copyu8Speed);
void MGPIO_voidSetPinInputMode(u8 copyu8Port, u8 copyu8Pin, u8 copyu8InputMode);
void MGPIO_voidSetPinAlternateFunctionMode(u8 copyu8Port, u8 copyu8Pin, u8 copyu8AltFuncMode);

void MGPIO_voidSetPinValue(u8 copyu8Port, u8 copyu8Pin, u8 copyu8Output);
void MGPIO_voidGetPinValue(u8 copyu8Port, u8 copyu8Pin, u8* pu8Return);
void MGPIO_voidTogglePin(u8 copyu8Port, u8 copyu8Pin);

void MGPIO_voidSetPortValue(u8 copyu8Port, u16 copyu16Output);
void MGPIO_voidSetPortValue_Byte(u8 copyu8Port, u8 copyu8Output);

void MGPIO_voidSetRestPin(u8 copyu8Port, u8 copyu8Pin, u8 copyu8SetResetValue);

#endif /* MGPIO_INTERFACE_H_ */
