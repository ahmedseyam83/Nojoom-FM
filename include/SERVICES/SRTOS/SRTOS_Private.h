/*
 * SRTOS_Private.h
 *
 *  Created on: 30 Apr 2024
 *      Author: User
 */

#ifndef SRTOS_PRIVATE_H_
#define SRTOS_PRIVATE_H_


/****************************************************************************/
/*						TASK STRUCTURE									*/
/****************************************************************************/

typedef struct{
	u8 Task_State				;
	u32 Task_FirstDelay			;
	u32 Task_periodicity		;
	PtrToFunc_void Task_Func	;
}TCB_t;



/************************************************************************************************/
/*									PRIVATE FUNCTIONS 											*/
/************************************************************************************************/

static void SRTOS_voidSchedular(void);




#endif /* SRTOS_PRIVATE_H_ */
