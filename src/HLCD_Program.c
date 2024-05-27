/*
 * LCD_Program.c
 *
 *  Created on: Mar 19, 2024
 *      Author: Ibrahim Refaey
 */

/************************************************************************************************/
/*										FILE INCLUSION											*/
/************************************************************************************************/
/***********************LIB*************************/
#include <LIB/Std_Types.h>
#include "../include/LIB/BIT_Math.h"
#include "../include/MCAL/MGPIO/MGPIO_Interface.h"
#include "../include/MCAL/MSYSTICK/MSYSTICK_Interface.h"

/****************************HAL***************************/
#include "../include/HAL/HLCD/HLCD_Config.h"
#include "../include/HAL/HLCD/HLCD_Interface.h"
#include "../include/HAL/HLCD/HLCD_Private.h"


/********************Functions Definitions*****************/

static void HLCD_voidInitPort(void)
{
	u8 Local_u8Counter=0;
	for(Local_u8Counter=LCD_D0_PIN;Local_u8Counter<=LCD_D7_PIN;Local_u8Counter++)
	{
	MGPIO_voidSetPinMode(LCD_DATA_PORT,Local_u8Counter,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LCD_DATA_PORT,Local_u8Counter,GPIO_PUSH_PULL,GPIO_LOW_SPEED);
	}
}

static void HLCD_SetPortValue(u8 copy_u8Data)
{
	u16 copy_u16Data = (copy_u8Data<<LCD_D0_PIN);
	MGPIO_voidSetPortValue(LCD_DATA_PORT,copy_u16Data);
}


void HLCD_voidInit(void)
{
	u32 Local_u32Counter=0;
	/************Set the control pins to be output**********/
	MGPIO_voidSetPinMode(LCD_CTRL_PORT,LCD_EN_PIN,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LCD_CTRL_PORT,LCD_EN_PIN,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(LCD_CTRL_PORT,LCD_RW_PIN,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LCD_CTRL_PORT,LCD_RW_PIN,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(LCD_CTRL_PORT,LCD_RS_PIN,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LCD_CTRL_PORT,LCD_RS_PIN,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	/*Waiting for more than 30ms*/
	MSYSTICK_voidSetBusyWait_ms(30);

#if LCD_MODE == LCD_EIGHT_BIT
	HLCD_voidInitPort();

	/*Send the function set command: N->1 (2 lines) ,F-> 0 (5*7 char font)*/
	HLCD_voidSendCommand(0x38);

	/*delay 39 us*/
	//	_delay_us(40);

	/*Display ON/OFF control*/
	HLCD_voidSendCommand(0x0C);


	/*delay 39 us*/
	//_delay_us(40);

	/*Display clear control*/
	HLCD_voidSendCommand(0x01);



#elif LCD_MODE == LCD_FOUR_BIT
	DIO_u8SetPortDirection(LCD_DATA_PORT,0b1111);

	HLCD_voidSendCommand(0x28);

	/*delay 39 us*/
	//_delay_us(40);

	/*Display ON/OFF control*/
	HLCD_voidSendCommand(0x0C);

	/*delay 39 us*/
	//_delay_us(40);

	/*Display clear control*/
	HLCD_voidSendCommand(0x01);

#else
#error "Wrong LCD_MODE Configuration parameter"
#endif
}



void HLCD_voidSendCommand(u8 copy_u8Command)
{
	u16 Local_u16Counter=0;
	/*Set the RS pin to be low*/
	MGPIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,GPIO_PIN_LOW);

	/*Set the RW pin to be low*/
	MGPIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,GPIO_PIN_LOW);

#if LCD_MODE == LCD_EIGHT_BIT
	HLCD_SetPortValue(copy_u8Command);

	//DIO_u8SetPortValue(LCD_DATA_PORT,copy_u8Command );

#elif LCD_MODE == LCD_FOUR_BIT
	DIO_u8SetPortValue(LCD_DATA_PORT,(copy_u8Command &0xF0));

	/*set the EN pin to high: 1 to read, waiting 2 msec and then make it low again*/
	MGPIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,GPIO_PIN_HIGH);

	/*Wait 2 msec*/
	for(Local_u16Counter=0;Local_u16Counter<32000;Local_u16Counter++);
	MGPIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,GPIO_PIN_LOW);

	MGPIO_voidSetPortValue(LCD_DATA_PORT,(((copy_u8Command<<4)&0xF0))<<LCD_D0_PIN);


#else
#error "Wrong LCD_MODE Configuration parameter"
#endif

	/*set the EN pin to high: 1 to read, waiting 2 msec and then make it low again*/
	MGPIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,GPIO_PIN_HIGH);

	/*Wait 2 msec*/
	MSYSTICK_voidSetBusyWait_ms(2);
	MGPIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,GPIO_PIN_LOW);

}

void HLCD_voidSendData(u8 copy_u8Data)
{
	u16 Local_u16Counter=0;
	/*Set the RS pin to be low*/
	MGPIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,GPIO_PIN_HIGH);

	/*Set the RW pin to be low*/
	MGPIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,GPIO_PIN_LOW);

#if LCD_MODE == LCD_EIGHT_BIT
	HLCD_SetPortValue(copy_u8Data);


#elif LCD_MODE == LCD_FOUR_BIT
	HLCD_SetPortValue(LCD_DATA_PORT,((copy_u8Data &0xF0)));

	/*set the EN pin to high: 1 to read, waiting 2 msec and then make it low again*/
	MGPIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,GPIO_PIN_HIGH);

	/*Wait 2 msec*/
	for(Local_u16Counter=0;Local_u16Counter<32000;Local_u16Counter++);
	MGPIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,GPIO_PIN_LOW);

	DIO_u8SetPortValue(LCD_DATA_PORT,((copy_u8Data<<4)&0xF0));


#else
#error "Wrong LCD_MODE Configuration parameter"
#endif

	/*set the EN pin to high: 1 to read, waiting 2 msec and then make it low again*/
	MGPIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,GPIO_PIN_HIGH);

	/*Wait 2 msec*/
	MSYSTICK_voidSetBusyWait_ms(2);
	MGPIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,GPIO_PIN_LOW);

}

void HLCD_voidSendString(const u8* copy_pu8String)
{
	for(u8 local_u8Iterator = 0; copy_pu8String[local_u8Iterator] != '\0';local_u8Iterator++)
	{
		HLCD_voidSendData(copy_pu8String[local_u8Iterator]);
	}
}


void HLCD_voidSetPosition(u8 copy_u8XPosition,u8 copy_u8YPosition)
{
	u8 Local_u8Address = 0;
	if(copy_u8XPosition == LCD_ROW0)
	{
		Local_u8Address = copy_u8YPosition;
	}
	else if(copy_u8XPosition == LCD_ROW1)
	{
		Local_u8Address = copy_u8YPosition + DDRAM_OFFSET;
	}
	else
	{

	}

	SET_BIT(Local_u8Address,7);
	HLCD_voidSendCommand(Local_u8Address);
}

void HLCD_voidSendNumber(s64 copy_s32Number)
{
	u64 reversed = 1;
	if (copy_s32Number == 0)
	{
		HLCD_voidSendData('0');
	}
	else
	{
		if(copy_s32Number <0)
		{
			HLCD_voidSendData('-');
			copy_s32Number *=-1;
		}
		else
		{
			while(copy_s32Number!= 0)
			{
				reversed = (reversed*10) + (copy_s32Number%10);
				copy_s32Number/=10;
			}
			while(reversed != 1)
			{
				HLCD_voidSendData(reversed%10 +'0');
				reversed/=10;
			}
		}
	}
}

void HLCD_voidSendCustomCharacter(u8* copy_pu8CharacterArray,u8 copy_u8PatternNumber,u8 copy_u8XPosition,u8 copy_u8YPosition)
{
	u8 Local_u8CGRAMAddress = 0 ,Local_u8LoopCounter;

	/*Calculating CGRAM Address*/
	Local_u8CGRAMAddress = copy_u8PatternNumber*8;

	/*Make the 6th bit from address to be high and sending cmd to LCD*/
	SET_BIT(Local_u8CGRAMAddress,6);

	HLCD_voidSendCommand(Local_u8CGRAMAddress);

	for(Local_u8LoopCounter = 0; Local_u8LoopCounter<8 ; Local_u8LoopCounter++)
	{
		HLCD_voidSendData(copy_pu8CharacterArray[Local_u8LoopCounter]);
	}
	HLCD_voidSetPosition( copy_u8XPosition,copy_u8YPosition);

	/*Displaying the pattern from CGRAM*/
	HLCD_voidSendData(copy_u8PatternNumber);
}

void HLCD_voidClearScreen(void)
{
	HLCD_voidSendCommand(0x01);
}

