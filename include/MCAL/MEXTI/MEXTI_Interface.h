/*
 * MEXTI_Interface.h
 *
 *  Created on: 24 Apr 2024
 *      Author: User
 */

#ifndef MEXTI_INTERFACE_H_
#define MEXTI_INTERFACE_H_

/*************************EXTI ENUMS******************************/
/*********EXTI Lines*******/

typedef enum{
	MEXTI_LINE0	=0	,
	MEXTI_LINE1		,
	MEXTI_LINE2		,
	MEXTI_LINE3		,
	MEXTI_LINE4		,
	MEXTI_LINE5		,
	MEXTI_LINE6		,
	MEXTI_LINE7		,
	MEXTI_LINE8		,
	MEXTI_LINE9		,
	MEXTI_LINE10	,
	MEXTI_LINE11	,
	MEXTI_LINE12	,
	MEXTI_LINE13	,
	MEXTI_LINE14	,
	MEXTI_LINE15
}MEXTI_Line;

/*********EXTI Ports*******/
typedef enum{
	MEXTI_PORTA	=0	,
	MEXTI_PORTB		,
	MEXTI_PORTC		,
	MEXTI_PORTD		,
	MEXTI_PORTE		,
	MEXTI_PORTH =7
}MEXTI_Port;

/*********EXTI Modes*******/
typedef enum{
	MEXTI_RISING_EDGE	,
	MEXTI_FALLING_EDGE	,
	MEXTI_ON_CHANGE
}MEXTI_Mode;

/*********EXTI STATES*******/
typedef enum{
	MEXTI_DISABLED=0,
	MEXTI_ENABLED
}MEXTI_State;

/************************************************************************************************/
/*									FUNCTIONS API's												*/
/************************************************************************************************/

void MEXTI_voidInit(void);

void MEXTI_voidEnableEXTILine(MEXTI_Line copy_MEXTI_Line);
void MEXTI_voidDisableEXTILine(MEXTI_Line copy_MEXTI_Line);

void MEXTI_voidSetCallBack(MEXTI_Line copy_MEXTI_Line ,PtrToFunc_void copy_callBackFunc);

void MEXTI_voidSoftwareInterruptRequest(MEXTI_Line copy_MEXTI_Line);
u8 MEXTI_u8GetPendingFlagStatus(MEXTI_Line copy_MEXTI_Line);
void MEXTI_voidClearPendingFlag(MEXTI_Line copy_MEXTI_Line);

void MEXTI_voidSelectPort(MEXTI_Line copy_MEXTI_Line ,MEXTI_Port copy_MEXTI_Port);
void MEXTI_voidSetMode(MEXTI_Line copy_MEXTI_Line ,MEXTI_Mode copy_MEXTI_Mode);


#endif /* MEXTI_INTERFACE_H_ */
