/*
 * HS2P_Program.c
 *
 *  Created on: 12 May 2024
 *      Author: User
 */
/***********************LIB*************************/
#include "../include/LIB/Std_Types.h"
#include "../include/LIB/BIT_Math.h"
#include "../include/MCAL/MGPIO/MGPIO_Interface.h"
#include "../include/MCAL/MSYSTICK/MSYSTICK_Interface.h"

/****************************HAL***************************/
#include "../include/HAL/HS2P/HS2P_Config.h"
#include "../include/HAL/HS2P/HS2P_Interface.h"
#include "../include/HAL/HS2P/HS2P_Private.h"

#if S2P1_ENABLE_SELECT == ENABLED

void HS2P_voidInit(void)
{
	//Make the Direction of S2P pins Output
	MGPIO_voidSetPinMode(S2P_PORT,S2P_DS_PIN,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(S2P_PORT,S2P_DS_PIN,GPIO_PUSH_PULL,GPIO_MEDIUM_SPEED);

	MGPIO_voidSetPinMode(S2P_PORT,S2P_SH_CLK_PIN,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(S2P_PORT,S2P_SH_CLK_PIN,GPIO_PUSH_PULL,GPIO_MEDIUM_SPEED);

	MGPIO_voidSetPinMode(S2P_PORT,S2P_STRG_CLK_PIN,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(S2P_PORT,S2P_STRG_CLK_PIN,GPIO_PUSH_PULL,GPIO_MEDIUM_SPEED);

#if S2P_SELECT == S2P_16_BIT

	MGPIO_voidSetPinMode(S2P_PORT,S2P_RST_PIN,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(S2P_PORT,S2P_RST_PIN,GPIO_PUSH_PULL,GPIO_MEDIUM_SPEED);

	MGPIO_voidSetPinMode(S2P_PORT,S2P_ENABLE_PIN,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(S2P_PORT,S2P_ENABLE_PIN,GPIO_PUSH_PULL,GPIO_MEDIUM_SPEED);

#endif


}

void HS2P_voidSendByte(u8 Copy_u8Data)
{
	s8 Local_u8Counter;
	u8 Local_u8BitValue;
	for(Local_u8Counter=7;Local_u8Counter>=0;Local_u8Counter--)
	{
		// Set the value of every single bit each time
		Local_u8BitValue = GET_BIT(Copy_u8Data,Local_u8Counter);
		MGPIO_voidSetPinValue(S2P_PORT,S2P_DS_PIN,Local_u8BitValue);
		//Send Pulse to shift register to synchronise
		MGPIO_voidSetPinValue(S2P_PORT,S2P_SH_CLK_PIN,GPIO_PIN_HIGH);
		MSYSTICK_voidSetBusyWait_us(2);
		MGPIO_voidSetPinValue(S2P_PORT,S2P_SH_CLK_PIN,GPIO_PIN_LOW);
		MSYSTICK_voidSetBusyWait_us(2);
	}
	//Send Pulse to storage register to synchronise
	MGPIO_voidSetPinValue(S2P_PORT,S2P_STRG_CLK_PIN,GPIO_PIN_HIGH);
	MSYSTICK_voidSetBusyWait_us(2);
	MGPIO_voidSetPinValue(S2P_PORT,S2P_STRG_CLK_PIN,GPIO_PIN_LOW);
	MSYSTICK_voidSetBusyWait_us(2);
}

void HS2P_voidSendData(u16 Copy_u8Data)
{
	s8 Local_u8Counter;
	u8 Local_u8BitValue;
	for(Local_u8Counter=15;Local_u8Counter>=0;Local_u8Counter--)
	{
		// Set the value of every single bit each time
		Local_u8BitValue = GET_BIT(Copy_u8Data,Local_u8Counter);
		MGPIO_voidSetPinValue(S2P_PORT,S2P_DS_PIN,Local_u8BitValue);
		//Send Pulse to shift register to synchronise
		MGPIO_voidSetPinValue(S2P_PORT,S2P_SH_CLK_PIN,GPIO_PIN_HIGH);
		MSYSTICK_voidSetBusyWait_us(2);
		MGPIO_voidSetPinValue(S2P_PORT,S2P_SH_CLK_PIN,GPIO_PIN_LOW);
		MSYSTICK_voidSetBusyWait_us(2);
	}
	//Send Pulse to storage register to synchronise
	MGPIO_voidSetPinValue(S2P_PORT,S2P_STRG_CLK_PIN,GPIO_PIN_HIGH);
	MSYSTICK_voidSetBusyWait_us(2);
	MGPIO_voidSetPinValue(S2P_PORT,S2P_STRG_CLK_PIN,GPIO_PIN_LOW);
	MSYSTICK_voidSetBusyWait_us(2);
}

void HS2P_voidSendBit(u8 Copy_u8Data,u8 Copy_u8Bitnumber)
{
	u8 Local_u8BitValue;
	// Set the value of every single bit each time
	Local_u8BitValue = GET_BIT(Copy_u8Data,Copy_u8Bitnumber);
	MGPIO_voidSetPinValue(S2P_PORT,S2P_DS_PIN,Local_u8BitValue);
	//Send Pulse to shift register to synchronise
	MGPIO_voidSetPinValue(S2P_PORT,S2P_SH_CLK_PIN,GPIO_PIN_HIGH);
	MSYSTICK_voidSetBusyWait_us(2);
	MGPIO_voidSetPinValue(S2P_PORT,S2P_SH_CLK_PIN,GPIO_PIN_LOW);
	MSYSTICK_voidSetBusyWait_us(2);
}



void HS2P_voidChipEnableDisable(ChipState_t copy_ChState)
{
	switch(copy_ChState)
	{
	case DISABLED:
		MGPIO_voidSetPinValue(S2P_PORT,S2P_ENABLE_PIN,GPIO_PIN_HIGH);
		break;
	case ENABLED:
		MGPIO_voidSetPinValue(S2P_PORT,S2P_ENABLE_PIN,GPIO_PIN_LOW);
		break;

	}

}

void HS2P_voidChipReset(void)
{
	MGPIO_voidSetPinValue(S2P_PORT,S2P_RST_PIN,GPIO_PIN_LOW);
	MSYSTICK_voidSetBusyWait_ms(100);
	MGPIO_voidSetPinValue(S2P_PORT,S2P_RST_PIN,GPIO_PIN_HIGH);
}

#endif


#if S2P2_ENABLE_SELECT == ENABLED
void HS2P2_voidInit(void)
{
	//Make the Direction of S2P2 pins Output
	MGPIO_voidSetPinMode(S2P2_PORT,S2P2_DS_PIN,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(S2P2_PORT,S2P2_DS_PIN,GPIO_PUSH_PULL,GPIO_MEDIUM_SPEED);

	MGPIO_voidSetPinMode(S2P2_PORT,S2P2_SH_CLK_PIN,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(S2P2_PORT,S2P2_SH_CLK_PIN,GPIO_PUSH_PULL,GPIO_MEDIUM_SPEED);

	MGPIO_voidSetPinMode(S2P2_PORT,S2P2_STRG_CLK_PIN,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(S2P2_PORT,S2P2_STRG_CLK_PIN,GPIO_PUSH_PULL,GPIO_MEDIUM_SPEED);

#if S2P2_SELECT == S2P2_16_BIT

	MGPIO_voidSetPinMode(S2P2_PORT,S2P2_RST_PIN,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(S2P2_PORT,S2P2_RST_PIN,GPIO_PUSH_PULL,GPIO_MEDIUM_SPEED);

	MGPIO_voidSetPinMode(S2P2_PORT,S2P2_ENABLE_PIN,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(S2P2_PORT,S2P2_ENABLE_PIN,GPIO_PUSH_PULL,GPIO_MEDIUM_SPEED);

#endif


}

void HS2P2_voidSendByte(u8 Copy_u8Data)
{
	s8 Local_u8Counter;
	u8 Local_u8BitValue;
	for(Local_u8Counter=7;Local_u8Counter>=0;Local_u8Counter--)
	{
		// Set the value of every single bit each time
		Local_u8BitValue = GET_BIT(Copy_u8Data,Local_u8Counter);
		MGPIO_voidSetPinValue(S2P2_PORT,S2P2_DS_PIN,Local_u8BitValue);
		//Send Pulse to shift register to synchronise
		MGPIO_voidSetPinValue(S2P2_PORT,S2P2_SH_CLK_PIN,GPIO_PIN_HIGH);
		MSYSTICK_voidSetBusyWait_us(2);
		MGPIO_voidSetPinValue(S2P2_PORT,S2P2_SH_CLK_PIN,GPIO_PIN_LOW);
		MSYSTICK_voidSetBusyWait_us(2);
	}
	//Send Pulse to storage register to synchronise
	MGPIO_voidSetPinValue(S2P2_PORT,S2P2_STRG_CLK_PIN,GPIO_PIN_HIGH);
	MSYSTICK_voidSetBusyWait_us(2);
	MGPIO_voidSetPinValue(S2P2_PORT,S2P2_STRG_CLK_PIN,GPIO_PIN_LOW);
	MSYSTICK_voidSetBusyWait_us(2);
}

void HS2P2_voidSendData(u16 Copy_u8Data)
{
	s8 Local_u8Counter;
	u8 Local_u8BitValue;
	for(Local_u8Counter=15;Local_u8Counter>=0;Local_u8Counter--)
	{
		// Set the value of every single bit each time
		Local_u8BitValue = GET_BIT(Copy_u8Data,Local_u8Counter);
		MGPIO_voidSetPinValue(S2P2_PORT,S2P2_DS_PIN,Local_u8BitValue);
		//Send Pulse to shift register to synchronise
		MGPIO_voidSetPinValue(S2P2_PORT,S2P2_SH_CLK_PIN,GPIO_PIN_HIGH);
		MSYSTICK_voidSetBusyWait_us(2);
		MGPIO_voidSetPinValue(S2P2_PORT,S2P2_SH_CLK_PIN,GPIO_PIN_LOW);
		MSYSTICK_voidSetBusyWait_us(2);
	}
	//Send Pulse to storage register to synchronise
	MGPIO_voidSetPinValue(S2P2_PORT,S2P2_STRG_CLK_PIN,GPIO_PIN_HIGH);
	MSYSTICK_voidSetBusyWait_us(2);
	MGPIO_voidSetPinValue(S2P2_PORT,S2P2_STRG_CLK_PIN,GPIO_PIN_LOW);
	MSYSTICK_voidSetBusyWait_us(2);
}

void HS2P2_voidSendBit(u8 Copy_u8Data,u8 Copy_u8Bitnumber)
{
	u8 Local_u8BitValue;
	// Set the value of every single bit each time
	Local_u8BitValue = GET_BIT(Copy_u8Data,Copy_u8Bitnumber);
	MGPIO_voidSetPinValue(S2P2_PORT,S2P2_DS_PIN,Local_u8BitValue);
	//Send Pulse to shift register to synchronise
	MGPIO_voidSetPinValue(S2P2_PORT,S2P2_SH_CLK_PIN,GPIO_PIN_HIGH);
	MSYSTICK_voidSetBusyWait_us(2);
	MGPIO_voidSetPinValue(S2P2_PORT,S2P2_SH_CLK_PIN,GPIO_PIN_LOW);
	MSYSTICK_voidSetBusyWait_us(2);
}



void HS2P2_voidChipEnableDisable(ChipState_t copy_ChState)
{
	switch(copy_ChState)
	{
	case DISABLED:
		MGPIO_voidSetPinValue(S2P2_PORT,S2P2_ENABLE_PIN,GPIO_PIN_HIGH);
		break;
	case ENABLED:
		MGPIO_voidSetPinValue(S2P2_PORT,S2P2_ENABLE_PIN,GPIO_PIN_LOW);
		break;

	}

}

void HS2P2_voidChipReset(void)
{
	MGPIO_voidSetPinValue(S2P2_PORT,S2P2_RST_PIN,GPIO_PIN_LOW);
	MSYSTICK_voidSetBusyWait_ms(100);
	MGPIO_voidSetPinValue(S2P2_PORT,S2P2_RST_PIN,GPIO_PIN_HIGH);
}

#endif








/****************************** Services *************************************/
static void HS2P_voidSendByte_NoPulse(u8 Copy_u8Data)
{
	s8 Local_u8Counter;
	u8 Local_u8BitValue;
	for(Local_u8Counter=7;Local_u8Counter>=0;Local_u8Counter--)
	{
		// Set the value of every single bit each time
		Local_u8BitValue = GET_BIT(Copy_u8Data,Local_u8Counter);
		MGPIO_voidSetPinValue(S2P_PORT,S2P_DS_PIN,Local_u8BitValue);
		//Send Pulse to shift register to synchronise
		MGPIO_voidSetPinValue(S2P_PORT,S2P_SH_CLK_PIN,GPIO_PIN_HIGH);
		MSYSTICK_voidSetBusyWait_us(2);
		MGPIO_voidSetPinValue(S2P_PORT,S2P_SH_CLK_PIN,GPIO_PIN_LOW);
		MSYSTICK_voidSetBusyWait_us(2);
	}
}


static void HS2P_voidSendPulse(void)
{
	//Send Pulse to storage register to synchronise
	MGPIO_voidSetPinValue(S2P_PORT,S2P_STRG_CLK_PIN,GPIO_PIN_HIGH);
	MSYSTICK_voidSetBusyWait_us(2);
	MGPIO_voidSetPinValue(S2P_PORT,S2P_STRG_CLK_PIN,GPIO_PIN_LOW);
	MSYSTICK_voidSetBusyWait_us(2);
}

void HS2P_voidSendPattern_LDMX(u8* copy_u8ptrtoData)
{
	u8 Local_u8Col=0 , Local_u8Row=0 ,Local_u8PinValue=0,Local_u8Counter,Local_u8ColumnsValue=0;
	//Make the Value of pins Reset
	for( Local_u8Col= 0 ; Local_u8Col < 7 +1 ; Local_u8Col++ )
	{
		HS2P_voidSendByte(DISABLE_COLUMNS);
		for( Local_u8Row= 0 ; Local_u8Row <7 +1 ; Local_u8Row ++ )
		{
			HS2P_voidSendBit(copy_u8ptrtoData[Local_u8Col],Local_u8Row);
		}
		Local_u8ColumnsValue= 0xff & (~(1<<Local_u8Col));
		HS2P_voidSendByte_NoPulse(Local_u8ColumnsValue);
		HS2P_voidSendPulse();
		// Make the busywait time for 1 columns = 312 us :  for 8 coloums 312*8  = 2500 us
		MSYSTICK_voidSetBusyWait_us(312);
	}
}

void HS2P_voidSendPattern_LDMX_Motion(u8* copy_u8ptrtoData,u8 copy_u8MotionCounter)
{
	u8 Local_u8Col=0 , Local_u8Row=0 ,Local_u8PinValue=0,Local_u8Counter,Local_u8ColumnsValue=0;
	//Make the Value of pins Reset
	for( Local_u8Col= 0 ; Local_u8Col < 7 +1 ; Local_u8Col++ )
	{
		HS2P_voidSendByte(DISABLE_COLUMNS);
		for( Local_u8Row= 0 ; Local_u8Row <7 +1 ; Local_u8Row ++ )
		{
			HS2P_voidSendBit(copy_u8ptrtoData[Local_u8Col],Local_u8Row+copy_u8MotionCounter);
		}
		Local_u8ColumnsValue= 0xff & (~(1<<Local_u8Col));
		HS2P_voidSendByte_NoPulse(Local_u8ColumnsValue);
		HS2P_voidSendPulse();
		// Make the busywait time for 1 columns = 312 us :  for 8 coloums 312*8  = 2500 us
		MSYSTICK_voidSetBusyWait_us(312);
	}
}


