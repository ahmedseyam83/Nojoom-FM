/************************************************************************************************/
/*										FILE INCLUSION											*/
/************************************************************************************************/
/***********************LIB*************************/
#include <LIB/Std_Types.h>
#include "../include/LIB/BIT_Math.h"
#include "../include/MCAL/MEXTI/MEXTI_Config.h"
#include "../include/MCAL/MEXTI/MEXTI_Interface.h"
#include "../include/MCAL/MEXTI/MEXTI_Private.h"


extern MEXTI_Configurations MEXTI_Config[MEXTI_NUMBER];
static PtrToFunc_void MEXTI_callBack[MEXTI_TOTAL_NUMBER];

void MEXTI_voidInit(void)
{
	u8 Local_u8Iterator=0;
	/*Intialize an Iterator to iterate on the EXTIs in configuration source file*/
	for(Local_u8Iterator=0 ; Local_u8Iterator < MEXTI_NUMBER; Local_u8Iterator++)
	{
		/*Set Port*/
		MEXTI_voidSelectPort(MEXTI_Config[Local_u8Iterator].Line,MEXTI_Config[Local_u8Iterator].Port);

		/*Set Mode*/
		MEXTI_voidSetMode(MEXTI_Config[Local_u8Iterator].Line,MEXTI_Config[Local_u8Iterator].Mode);

		/* Set State*/
		if(MEXTI_Config[Local_u8Iterator].State == MEXTI_ENABLED)
		{
			MEXTI_voidEnableEXTILine(MEXTI_Config[Local_u8Iterator].Line);
		}
		else
		{
			MEXTI_voidDisableEXTILine(MEXTI_Config[Local_u8Iterator].Line);
		}

	}

}

void MEXTI_voidEnableEXTILine(MEXTI_Line copy_MEXTI_Line)
{
	/*Set the corresponding bit to enable the entered EXTI*/
	SET_BIT(EXTI->IMR,copy_MEXTI_Line);

}
void MEXTI_voidDisableEXTILine(MEXTI_Line copy_MEXTI_Line)
{
	/*Clear the corresponding bit to disable the entered EXTI*/
	CLR_BIT(EXTI->IMR,copy_MEXTI_Line);
}

void MEXTI_voidSetCallBack(MEXTI_Line copy_MEXTI_Line ,PtrToFunc_void copy_callBackFunc)
{
	/*C the entered function to the entered EXTI CallBack function pointer*/
	MEXTI_callBack[copy_MEXTI_Line] = copy_callBackFunc;
}

void MEXTI_voidSoftwareInterruptRequest(MEXTI_Line copy_MEXTI_Line)
{
	/*Set the corresponding bit to enable software interrupt on EXTI line*/
	SET_BIT(EXTI->SWIER,copy_MEXTI_Line);
}

void MEXTI_voidClearPendingFlag(MEXTI_Line copy_MEXTI_Line)
{
	/*Set the corresponding bit to clear the pending flag of EXTI*/
	SET_BIT(EXTI->PR,copy_MEXTI_Line);
}

u8 MEXTI_u8GetPendingFlagStatus(MEXTI_Line copy_MEXTI_Line)
{
	/*Get the corresponding bit to read the pending flag of EXTI*/
	return GET_BIT(EXTI->PR,copy_MEXTI_Line);
}

void MEXTI_voidSelectPort(MEXTI_Line copy_MEXTI_Line ,MEXTI_Port copy_MEXTI_Port)
{
	/*Set those bits based on the entered port and EXTI*/
	SYSCFG->EXTICR[(copy_MEXTI_Line/4)] &= ~(FOUR_BIT_MASK <<((copy_MEXTI_Line%4)*4));
	SYSCFG->EXTICR[(copy_MEXTI_Line/4)] |= (copy_MEXTI_Port <<((copy_MEXTI_Line%4)*4));
}

void MEXTI_voidSetMode(MEXTI_Line copy_MEXTI_Line ,MEXTI_Mode copy_MEXTI_Mode)
{
	/*Set those bits based on the entered mode and EXTI*/
	if(copy_MEXTI_Mode == MEXTI_FALLING_EDGE)
	{
		SET_BIT(EXTI->FTSR,copy_MEXTI_Line);
		CLR_BIT(EXTI->RTSR,copy_MEXTI_Line);

	}
	else if(copy_MEXTI_Mode == MEXTI_RISING_EDGE)
	{
		CLR_BIT(EXTI->FTSR,copy_MEXTI_Line);
		SET_BIT(EXTI->RTSR,copy_MEXTI_Line);
	}
	else
	{
		SET_BIT(EXTI->FTSR,copy_MEXTI_Line);
		SET_BIT(EXTI->RTSR,copy_MEXTI_Line);
	}

}

void EXTI0_IRQHandler(void)
{
	if(MEXTI_callBack[0] != NULL)
	{
		MEXTI_callBack[0]();
	}
	MEXTI_voidClearPendingFlag(MEXTI_LINE0);
}


void EXTI1_IRQHandler(void)
{
	if(MEXTI_callBack[1] != NULL)
	{
		MEXTI_callBack[1]();
	}
	MEXTI_voidClearPendingFlag(MEXTI_LINE1);
}


void EXTI2_IRQHandler(void)
{
	if(MEXTI_callBack[2] != NULL)
	{
		MEXTI_callBack[2]();
	}
	MEXTI_voidClearPendingFlag(MEXTI_LINE2);
}


void EXTI3_IRQHandler(void)
{
	if(MEXTI_callBack[3] != NULL)
	{
		MEXTI_callBack[3]();
	}
	MEXTI_voidClearPendingFlag(MEXTI_LINE3);
}

void EXTI4_IRQHandler(void)
{
	if(MEXTI_callBack[4] != NULL)
	{
		MEXTI_callBack[4]();
	}
	MEXTI_voidClearPendingFlag(MEXTI_LINE4);
}

void EXTI9_5_IRQHandler(void)
{
	if(MEXTI_u8GetPendingFlagStatus(MEXTI_LINE5) == INTERRUPT_OCCURED)
	{
		if(MEXTI_callBack[5] != NULL)
		{
			MEXTI_callBack[5]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_LINE5);
	}

	else if(MEXTI_u8GetPendingFlagStatus(MEXTI_LINE6) == INTERRUPT_OCCURED)
	{
		if(MEXTI_callBack[6] != NULL)
		{
			MEXTI_callBack[6]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_LINE6);
	}

	else if(MEXTI_u8GetPendingFlagStatus(MEXTI_LINE7) == INTERRUPT_OCCURED)
	{
		if(MEXTI_callBack[7] != NULL)
		{
			MEXTI_callBack[7]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_LINE7);
	}

	else if(MEXTI_u8GetPendingFlagStatus(MEXTI_LINE8) == INTERRUPT_OCCURED)
	{
		if(MEXTI_callBack[8] != NULL)
		{
			MEXTI_callBack[8]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_LINE8);
	}


	else if(MEXTI_u8GetPendingFlagStatus(MEXTI_LINE9) == INTERRUPT_OCCURED)
	{
		if(MEXTI_callBack[9] != NULL)
		{
			MEXTI_callBack[9]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_LINE9);
	}

}


void EXTI15_10_IRQHandler(void)
{

	if(MEXTI_u8GetPendingFlagStatus(MEXTI_LINE10) == INTERRUPT_OCCURED)
	{
		if(MEXTI_callBack[10] != NULL)
		{
			MEXTI_callBack[10]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_LINE10);
	}
	else if(MEXTI_u8GetPendingFlagStatus(MEXTI_LINE11) == INTERRUPT_OCCURED)
	{
		if(MEXTI_callBack[11] != NULL)
		{
			MEXTI_callBack[11]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_LINE11);
	}
	else if(MEXTI_u8GetPendingFlagStatus(MEXTI_LINE12) == INTERRUPT_OCCURED)
	{
		if(MEXTI_callBack[12] != NULL)
		{
			MEXTI_callBack[12]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_LINE12);
	}
	else if(MEXTI_u8GetPendingFlagStatus(MEXTI_LINE13) == INTERRUPT_OCCURED)
	{
		if(MEXTI_callBack[13] != NULL)
		{
			MEXTI_callBack[13]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_LINE13);
	}
	else if(MEXTI_u8GetPendingFlagStatus(MEXTI_LINE14) == INTERRUPT_OCCURED)
	{
		if(MEXTI_callBack[14] != NULL)
		{
			MEXTI_callBack[14]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_LINE14);
	}
	else if(MEXTI_u8GetPendingFlagStatus(MEXTI_LINE15) == INTERRUPT_OCCURED)
	{
		if(MEXTI_callBack[15] != NULL)
		{
			MEXTI_callBack[15]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_LINE15);
	}
}
