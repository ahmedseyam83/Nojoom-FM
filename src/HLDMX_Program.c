
/*										FILE INCLUSION											*/
/************************************************************************************************/
/***********************LIB*************************/
#include "../include/LIB/Std_Types.h"
#include "../include/LIB/BIT_Math.h"
#include "../include/MCAL/MGPIO/MGPIO_Interface.h"
#include "../include/MCAL/MSYSTICK/MSYSTICK_Interface.h"
/****************************HAL***************************/
#include "../include/HAL/HLDMX/HLDMX_Config.h"
#include "../include/HAL/HLDMX/HLDMX_Interface.h"
#include "../include/HAL/HLDMX/HLDMX_Private.h"

u8 LDMX_RowPins[8]={};
u8 LDMX_ColPins[8]={};

static void LDMX_voidDisableColoumns(void)
{
	MGPIO_voidSetPinValue(LDMX_COL_PORT,LDMX_C0,GPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(LDMX_COL_PORT,LDMX_C1,GPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(LDMX_COL_PORT,LDMX_C2,GPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(LDMX_COL_PORT,LDMX_C3,GPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(LDMX_COL_PORT,LDMX_C4,GPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(LDMX_COL_PORT,LDMX_C5,GPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(LDMX_COL_PORT,LDMX_C6,GPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(LDMX_COL_PORT,LDMX_C7,GPIO_PIN_HIGH);

}

static void LDMX_voidDisableRows(void)
{
	MGPIO_voidSetPinValue(LDMX_ROW_PORT,LDMX_R0,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(LDMX_ROW_PORT,LDMX_R1,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(LDMX_ROW_PORT,LDMX_R2,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(LDMX_ROW_PORT,LDMX_R3,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(LDMX_ROW_PORT,LDMX_R4,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(LDMX_ROW_PORT,LDMX_R5,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(LDMX_ROW_PORT,LDMX_R6,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(LDMX_ROW_PORT,LDMX_R7,GPIO_PIN_LOW);

}

void HLDMX_voidInit(void)
{
	//Make the Direction of ROW pins Output
	MGPIO_voidSetPinMode(LDMX_ROW_PORT,LDMX_R0,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LDMX_ROW_PORT,LDMX_R0,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(LDMX_ROW_PORT,LDMX_R1,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LDMX_ROW_PORT,LDMX_R1,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(LDMX_ROW_PORT,LDMX_R2,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LDMX_ROW_PORT,LDMX_R2,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(LDMX_ROW_PORT,LDMX_R3,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LDMX_ROW_PORT,LDMX_R3,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(LDMX_ROW_PORT,LDMX_R4,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LDMX_ROW_PORT,LDMX_R4,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(LDMX_ROW_PORT,LDMX_R5,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LDMX_ROW_PORT,LDMX_R5,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(LDMX_ROW_PORT,LDMX_R6,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LDMX_ROW_PORT,LDMX_R6,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(LDMX_ROW_PORT,LDMX_R7,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LDMX_ROW_PORT,LDMX_R7,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	//Make the Direction of Column pins Output

	MGPIO_voidSetPinMode(LDMX_COL_PORT,LDMX_C0,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LDMX_COL_PORT,LDMX_C0,GPIO_PUSH_PULL,GPIO_LOW_SPEED);


	MGPIO_voidSetPinMode(LDMX_COL_PORT,LDMX_C1,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LDMX_COL_PORT,LDMX_C1,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(LDMX_COL_PORT,LDMX_C2,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LDMX_COL_PORT,LDMX_C2,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(LDMX_COL_PORT,LDMX_C3,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LDMX_COL_PORT,LDMX_C3,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(LDMX_COL_PORT,LDMX_C4,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LDMX_COL_PORT,LDMX_C4,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(LDMX_COL_PORT,LDMX_C5,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LDMX_COL_PORT,LDMX_C5,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(LDMX_COL_PORT,LDMX_C6,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LDMX_COL_PORT,LDMX_C6,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(LDMX_COL_PORT,LDMX_C7,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(LDMX_COL_PORT,LDMX_C7,GPIO_PUSH_PULL,GPIO_LOW_SPEED);

	LDMX_RowPins[0]=LDMX_R0;
	LDMX_RowPins[1]=LDMX_R1;
	LDMX_RowPins[2]=LDMX_R2;
	LDMX_RowPins[3]=LDMX_R3;
	LDMX_RowPins[4]=LDMX_R4;
	LDMX_RowPins[5]=LDMX_R5;
	LDMX_RowPins[6]=LDMX_R6;
	LDMX_RowPins[7]=LDMX_R7;

	LDMX_ColPins[0]=LDMX_C0;
	LDMX_ColPins[1]=LDMX_C1;
	LDMX_ColPins[2]=LDMX_C2;
	LDMX_ColPins[3]=LDMX_C3;
	LDMX_ColPins[4]=LDMX_C4;
	LDMX_ColPins[5]=LDMX_C5;
	LDMX_ColPins[6]=LDMX_C6;
	LDMX_ColPins[7]=LDMX_C7;

	//Make the Value of pins Reset
	LDMX_voidDisableRows();
	LDMX_voidDisableColoumns();
}


void HLDMX_voidSendPattern(u8* copy_u8ptrtoData)
{
	u8 Local_u8Col=0 , Local_u8Row=0 ,Local_u8PinValue=0;
	//Make the Value of pins Reset
	for( Local_u8Col= INIT_VALUE ; Local_u8Col < END_VALUE +1 ; Local_u8Col++ )
	{
		LDMX_voidDisableColoumns();
		for( Local_u8Row= INIT_VALUE ; Local_u8Row <END_VALUE +1 ; Local_u8Row ++ )
		{
			Local_u8PinValue=GET_BIT(copy_u8ptrtoData[Local_u8Col],Local_u8Row);
			MGPIO_voidSetPinValue(LDMX_ROW_PORT,LDMX_RowPins[Local_u8Row],Local_u8PinValue);
		}
		MGPIO_voidSetPinValue(LDMX_COL_PORT,LDMX_ColPins[Local_u8Col],GPIO_PIN_LOW);
		// Make the busywait time for 1 columns = 312 us :  for 8 coloums 312*8  = 2500 us
		MSYSTICK_voidSetBusyWait_us(312);

	}
}


