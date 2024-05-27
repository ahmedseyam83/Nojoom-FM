/*
 * SRTOS_Program.c
 *
 *  Created on: 30 Apr 2024
 *      Author: User
 */

/*
/************************************************************************************************/
/*										FILE INCLUSION											*/
/************************************************************************************************/
/***********************LIB*************************/
#include <LIB/Std_Types.h>
#include "../include/LIB/BIT_Math.h"
#include "../include/SERVICES/SRTOS/SRTOS_Config.h"
#include "../include/SERVICES/SRTOS/SRTOS_Interface.h"
#include "../include/SERVICES/SRTOS/SRTOS_Private.h"
#include "../include/MCAL/MSYSTICK/MSYSTICK_Interface.h"



TCB_t TasksArray[MAX_TASK_NUM] = {{}};

/************************************************************************/
/*						   FUNCTIONS DEFINITIONS						*/
/************************************************************************/

static void SRTOS_voidSchedular(void)
{
	u8 Local_u8Iterator;
	for(Local_u8Iterator=0;Local_u8Iterator<MAX_TASK_NUM;Local_u8Iterator++)
	{
		if(TasksArray[Local_u8Iterator].Task_Func != NULL)
		{
			if((TasksArray[Local_u8Iterator].Task_State) != SUSPENDED)
			{
				if((TasksArray[Local_u8Iterator].Task_FirstDelay) == 0)
				{
					TasksArray[Local_u8Iterator].Task_State= READY;
				}

				if((TasksArray[Local_u8Iterator].Task_State) == READY)
				{
					//Invoke Task
					TasksArray[Local_u8Iterator].Task_Func();
					//Update Periodicity
					TasksArray[Local_u8Iterator].Task_FirstDelay = TasksArray[Local_u8Iterator].Task_periodicity-1;
					TasksArray[Local_u8Iterator].Task_State= BLOCKED;
				}
				else
				{
					TasksArray[Local_u8Iterator].Task_FirstDelay --;
				}
			}
			else
			{
				/*DO NOTHING*/
			}
		}
	}
}



void SRTOS_voidInit(void)
{
	// optionally: enable Systick Interrupt (to insure that it is enable)

	// Initialize the timer
	MSYSTICK_voidInit();

}

void SRTOS_voidStartSchedular(void)
{
	//Enable timer with the System ticks you want
	MSYSTICK_voidSetPeriodicInterval_ms(RTOS_TICK_TIME,&SRTOS_voidSchedular);
}

ReturnType_State_t SRTOS_u8CreateTask(u8 copy_u8TaskPriority,u32 copy_u32Periodicity,u32 copy_u32FirstDelay,u8 copy_u8TaskState,PtrToFunc_void copy_TaskFunc)
{
	u8 Local_ErrorState = E_OK;
	if(copy_u8TaskPriority <= MAX_TASK_NUM)
	{
		if(TasksArray[copy_u8TaskPriority].Task_Func == NULL)
		{
			TasksArray[copy_u8TaskPriority].Task_State=copy_u8TaskState;
			TasksArray[copy_u8TaskPriority].Task_periodicity=copy_u32Periodicity;
			TasksArray[copy_u8TaskPriority].Task_FirstDelay = copy_u32FirstDelay;
			TasksArray[copy_u8TaskPriority].Task_Func = copy_TaskFunc;
		}
		else
		{
			Local_ErrorState = E_NOK;
		}
	}
	else
	{
		Local_ErrorState = E_NOK_OUT_OF_RANGE;
	}
	return Local_ErrorState;
}

ReturnType_State_t SRTOS_u8DeleteTask(u8 copy_u8TaskPriority)
{
	u8 Local_ErrorState = E_OK;
	if(TasksArray[copy_u8TaskPriority].Task_Func != NULL)
	{
		TasksArray[copy_u8TaskPriority].Task_Func = NULL;
	}
	else
	{
		Local_ErrorState = E_NOK_NULL_PTR;
	}
	return Local_ErrorState;
}

ReturnType_State_t SRTOS_u8ResumeTask(u8 copy_u8TaskPriority)
{
	u8 Local_ErrorState = E_OK;
	if(TasksArray[copy_u8TaskPriority].Task_Func != NULL)
	{
		TasksArray[copy_u8TaskPriority].Task_State = BLOCKED;
	}
	else
	{
		Local_ErrorState = E_NOK_NULL_PTR;
	}
	return Local_ErrorState;
}

ReturnType_State_t SRTOS_u8SuspendTask(u8 copy_u8TaskPriority)
{
	u8 Local_ErrorState = E_OK;
	if(TasksArray[copy_u8TaskPriority].Task_Func != NULL)
	{
		TasksArray[copy_u8TaskPriority].Task_State = SUSPENDED;
	}
	else
	{
		Local_ErrorState = E_NOK_NULL_PTR;
	}
	return Local_ErrorState;

}
