/*
 * HIR_Program.c
 *
 *  Created on: 8 May 2024
 *      Author: User
 */

/***********************LIB*************************/
#include <LIB/Std_Types.h>
#include "../include/LIB/BIT_Math.h"
#include "../include/MCAL/MGPIO/MGPIO_Interface.h"
#include "../include/MCAL/MSYSTICK/MSYSTICK_Interface.h"

/****************************HAL***************************/
#include "../include/HAL/HIR/HIR_Config.h"
#include "../include/HAL/HIR/HIR_Interface.h"
#include "../include/HAL/HIR/HIR_Private.h"
#include "../include/MCAL/MNVIC/MNVIC_Interface.h"
#include "../include/MCAL/MEXTI/MEXTI_Interface.h"


u8 Global_u8StartFlag=0,Global_u8Counter=0;
volatile u8 Global_u8ReturnData=0,Global_u8ReturnAddress=0;
volatile u32 Global_IRData[50]={0};



static void HIR_voidSetValue(void)
{
	u8 Local_u8Counter=0;
	for(Local_u8Counter=0;Local_u8Counter<8;Local_u8Counter++)
	{
		if((Global_IRData[Local_u8Counter+DATA_INDEX] >= 15000) && (Global_IRData[Local_u8Counter+DATA_INDEX])<=20000)
		{
			CLR_BIT(Global_u8ReturnData,Local_u8Counter);
		}
		else if((Global_IRData[Local_u8Counter+DATA_INDEX] >= 35000) && (Global_IRData[Local_u8Counter+DATA_INDEX])<=40000)
		{
			SET_BIT(Global_u8ReturnData,Local_u8Counter);
		}
	}
	Global_u8Counter=0;
	Global_u8StartFlag=0;
}


static void HIR_voidOperate(void)
{
	if(Global_u8StartFlag==0)
	{
		MSYSTICK_voidCounterReset();
		MSYSTICK_voidSetSingleInterval_ms(1000,HIR_voidSetValue);
		Global_u8StartFlag=1;
	}
	else
	{
		Global_IRData[Global_u8Counter]= MSYSTICK_u32GetElapsedTime();
		MSYSTICK_voidCounterReset();
		MSYSTICK_voidSetSingleInterval_ms(1000,HIR_voidSetValue);

		Global_u8Counter++;
	}

}


void HIR_voidInit(void)
{
	MNVIC_voidEnablePeripheralInterrupt(INTERRUPT_PERIPHERAL);
	MEXTI_voidSetCallBack(INTERRUPT_LINE,HIR_voidOperate);
	MEXTI_voidInit();
}




void HIR_u8GetValue(u8* copy_u8ReturnData)
{
	*copy_u8ReturnData=Global_u8ReturnData;
	Global_u8ReturnData = 0;
}

void HIR_u8GetAddress(u8* copy_u8ReturnAddress)
{
	*copy_u8ReturnAddress=Global_u8ReturnAddress;
}

