
/*										FILE INCLUSION											*/
/************************************************************************************************/
/***********************LIB*************************/
#include <LIB/Std_Types.h>
#include "../include/LIB/BIT_Math.h"
#include "../include/MCAL/MGPIO/MGPIO_Interface.h"
#include "../include/MCAL/MSYSTICK/MSYSTICK_Interface.h"

/****************************HAL***************************/
#include "../include/HAL/HKPD/HKPD_Config.h"
#include "../include/HAL/HKPD/HKPD_Interface.h"
#include "../include/HAL/HKPD/HKPD_Private.h"



void HKPD_Init(void)
{
	//Connect pull up for the rows pins
	MGPIO_voidSetPinMode(KPD_PORT,KPD_R0,GPIO_INPUT);
	MGPIO_voidSetPinInputMode(KPD_PORT,KPD_R0,GPIO_PULLUP);

	MGPIO_voidSetPinMode(KPD_PORT,KPD_R1,GPIO_INPUT);
	MGPIO_voidSetPinInputMode(KPD_PORT,KPD_R1,GPIO_PULLUP);

	MGPIO_voidSetPinMode(KPD_PORT,KPD_R2,GPIO_INPUT);
	MGPIO_voidSetPinInputMode(KPD_PORT,KPD_R2,GPIO_PULLUP);

	MGPIO_voidSetPinMode(KPD_PORT,KPD_R3,GPIO_INPUT);
	MGPIO_voidSetPinInputMode(KPD_PORT,KPD_R3,GPIO_PULLUP);

	//Make the Direction of Column pins Output

	MGPIO_voidSetPinMode(KPD_PORT,KPD_C0,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(KPD_PORT,KPD_C0,GPIO_PUSH_PULL,GPIO_LOW_SPEED);


	MGPIO_voidSetPinMode(KPD_PORT,KPD_C1,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(KPD_PORT,KPD_C1,GPIO_PUSH_PULL,GPIO_LOW_SPEED);


	MGPIO_voidSetPinMode(KPD_PORT,KPD_C2,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(KPD_PORT,KPD_C2,GPIO_PUSH_PULL,GPIO_LOW_SPEED);


	MGPIO_voidSetPinMode(KPD_PORT,KPD_C3,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(KPD_PORT,KPD_C3,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	//Make the Value of Column pins High
	MGPIO_voidSetPinValue(KPD_PORT,KPD_C0,GPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(KPD_PORT,KPD_C1,GPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(KPD_PORT,KPD_C2,GPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(KPD_PORT,KPD_C3,GPIO_PIN_HIGH);
}


u8	HKPD_u8GetPressed(void)
{
	u8 Local_u8Col , Local_u8Row , Local_u8ReturnData = NOTPRESSED , LocaL_u8GetPressed=1 ;
	for( Local_u8Col= KPD_COL_INIT ; Local_u8Col < KPD_COL_END +1 ; Local_u8Col++ )
	{
		MGPIO_voidSetPinValue(KPD_PORT,Local_u8Col,GPIO_PIN_LOW);
		for( Local_u8Row= KPD_ROW_INIT ; Local_u8Row <KPD_ROW_END +1 ; Local_u8Row ++ )
		{
			MGPIO_voidGetPinValue(KPD_PORT,Local_u8Row,&LocaL_u8GetPressed);
			if( LocaL_u8GetPressed == GPIO_PIN_LOW )
			{
				MSYSTICK_voidSetBusyWait_ms(50);

				MGPIO_voidGetPinValue(KPD_PORT,Local_u8Row,&LocaL_u8GetPressed);
				if(LocaL_u8GetPressed == GPIO_PIN_LOW)
				{
					Local_u8ReturnData = KPD_u8Buttons[Local_u8Row - KPD_ROW_INIT][Local_u8Col - KPD_COL_INIT];

					while(LocaL_u8GetPressed == 0)
					{
						MGPIO_voidGetPinValue(KPD_PORT,Local_u8Row,&LocaL_u8GetPressed);
					}
					break;
				}
			}
		}
		MGPIO_voidSetPinValue(KPD_PORT,Local_u8Col,GPIO_PIN_HIGH);
	}
	return Local_u8ReturnData;
}
