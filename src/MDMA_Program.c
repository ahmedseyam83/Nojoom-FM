/*
 * MDMA_Program.c
 *
 *  Created on: 15 May 2024
 *      Author: User
 */

/************************************************************************************************/
/*										FILE INCLUSION											*/
/************************************************************************************************/
/***********************LIB*************************/
#include "../include/LIB/Std_Types.h"
#include "../include/LIB/BIT_Math.h"
/***********************MCAL*************************/
#include "../include/MCAL/MDMA/MDMA_Interface.h"
#include "../include/MCAL/MDMA/MDMA_Private.h"
#include "../include/MCAL/MDMA/MDMA_Config.h"

static PtrToFunc_void DMA2_setCallBack[8];
static PtrToFunc_void DMA1_setCallBack[8];

#if	DMA1_ENABLE == DMA_ENABLED

void DMA1_voidStreamEnableCircMode(u8 copy_u8StrID,u8 copy_u8StrMode ,u8 copy_u8StrPriority)
{
	u32 Local_u32TempCR = 0;
	if(copy_u8StrMode== DMA_P2M_MODE)
	{
		// Choose Mode
		Local_u32TempCR &= ~((1<<DMA_SxCR_DIR)|(1<<(DMA_SxCR_DIR+1)));

		// Choose PINC & MINC mode
		Local_u32TempCR |= (1<<DMA_SxCR_MINC);
		Local_u32TempCR &= ~(1<<DMA_SxCR_PINC);
	}
	else if(copy_u8StrMode == DMA_M2P_MODE)
	{
		// Choose Mode
		Local_u32TempCR |= (1<<DMA_SxCR_DIR);
		Local_u32TempCR &= ~(1<<(DMA_SxCR_DIR+1));
		// Choose PINC & MINC mode
		Local_u32TempCR &= ~(1<<DMA_SxCR_MINC);
		Local_u32TempCR |= (1<<DMA_SxCR_PINC);
	}
	//Configure Priority
	if(copy_u8StrPriority == DMA_LOW_PRIORITY)
	{
		Local_u32TempCR &= ~(1<<DMA_SxCR_PL);
		Local_u32TempCR &= ~(1<<(DMA_SxCR_PL+1));
	}
	else if(copy_u8StrPriority == DMA_MEDIUM_PRIORITY)
	{
		Local_u32TempCR |= (1<<DMA_SxCR_PL);
		Local_u32TempCR &= ~(1<<(DMA_SxCR_PL+1));
	}
	else if(copy_u8StrPriority == DMA_HIGH_PRIORITY)
	{
		Local_u32TempCR &= ~(1<<DMA_SxCR_PL);
		Local_u32TempCR |= (1<<(DMA_SxCR_PL+1));
	}
	else if(copy_u8StrPriority == DMA_VERY_HIGH_PRIORITY)
	{
		Local_u32TempCR |= (1<<DMA_SxCR_PL);
		Local_u32TempCR |= (1<<(DMA_SxCR_PL+1));
	}

	//Enable Circular
	Local_u32TempCR |= (1<<DMA_SxCR_CIRC);

	DMA1->DMA_STREAM[copy_u8StrID].CR |= Local_u32TempCR;

	//Enable DMA
	DMA1->DMA_STREAM[copy_u8StrID].CR |= (1<<DMA_SxCR_EN);
}



void DMA1_voidStreamEnable(u8 copy_u8StrID,u8 copy_u8StrMode ,u8 copy_u8StrPriority)
{
	u32 Local_u32TempCR = 0;
	if(copy_u8StrMode== DMA_P2M_MODE)
	{
		// Choose Mode
		Local_u32TempCR &= ~((1<<DMA_SxCR_DIR)|(1<<(DMA_SxCR_DIR+1)));

		// Choose PINC & MINC mode
		Local_u32TempCR |= (1<<DMA_SxCR_MINC);
		Local_u32TempCR &= ~(1<<DMA_SxCR_PINC);
	}
	else if(copy_u8StrMode == DMA_M2P_MODE)
	{
		// Choose Mode
		Local_u32TempCR |= (1<<DMA_SxCR_DIR);
		Local_u32TempCR &= ~(1<<(DMA_SxCR_DIR+1));
		// Choose PINC & MINC mode
		Local_u32TempCR &= ~(1<<DMA_SxCR_MINC);
		Local_u32TempCR |= (1<<DMA_SxCR_PINC);
	}

	//Configure Priority
	if(copy_u8StrPriority == DMA_LOW_PRIORITY)
	{
		Local_u32TempCR &= ~(1<<DMA_SxCR_PL);
		Local_u32TempCR &= ~(1<<(DMA_SxCR_PL+1));
	}
	else if(copy_u8StrPriority == DMA_MEDIUM_PRIORITY)
	{
		Local_u32TempCR |= (1<<DMA_SxCR_PL);
		Local_u32TempCR &= ~(1<<(DMA_SxCR_PL+1));
	}
	else if(copy_u8StrPriority == DMA_HIGH_PRIORITY)
	{
		Local_u32TempCR &= ~(1<<DMA_SxCR_PL);
		Local_u32TempCR |= (1<<(DMA_SxCR_PL+1));
	}
	else if(copy_u8StrPriority == DMA_VERY_HIGH_PRIORITY)
	{
		Local_u32TempCR |= (1<<DMA_SxCR_PL);
		Local_u32TempCR |= (1<<(DMA_SxCR_PL+1));
	}

	DMA1->DMA_STREAM[copy_u8StrID].CR |= Local_u32TempCR;

	//Enable DMA
	DMA1->DMA_STREAM[copy_u8StrID].CR |= (1<<DMA_SxCR_EN);
}

void DMA1_voidSetStreamConfiguration(u8 copy_u8StrID,u8 copy_u8ChID,u32* copy_u32SrcAdd,u32* copy_u32DistAdd,u8 copy_u8SrcElementSize,u8 copy_u8DistElementSize,u16 copy_u16BlockSize)
{

	DMA1->DMA_STREAM[copy_u8StrID].CR = (copy_u8ChID<<DMA_SxCR_CHSEL);

	// Choose Source Word Size
	if(copy_u8SrcElementSize == DMA_BYTE_SIZE)
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(copy_u8SrcElementSize<<DMA_SxCR_PSIZE);
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(copy_u8SrcElementSize<<(DMA_SxCR_PSIZE+1));
	}
	else if(copy_u8SrcElementSize == DMA_HWORD_SIZE)
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR |= (copy_u8SrcElementSize<<DMA_SxCR_PSIZE);
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(copy_u8SrcElementSize<<(DMA_SxCR_PSIZE+1));
	}
	else if(copy_u8SrcElementSize == DMA_WORD_SIZE)
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(copy_u8SrcElementSize<<DMA_SxCR_PSIZE);
		DMA1->DMA_STREAM[copy_u8StrID].CR |= (copy_u8SrcElementSize<<(DMA_SxCR_PSIZE+1));
	}

	// Choose Word Size
	if(copy_u8DistElementSize == DMA_BYTE_SIZE)
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(copy_u8SrcElementSize<<DMA_SxCR_MSIZE);
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(copy_u8SrcElementSize<<(DMA_SxCR_MSIZE+1));
	}
	else if(copy_u8DistElementSize == DMA_HWORD_SIZE)
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR |= (copy_u8SrcElementSize<<DMA_SxCR_MSIZE);
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(copy_u8SrcElementSize<<(DMA_SxCR_MSIZE+1));
	}
	else if(copy_u8DistElementSize == DMA_WORD_SIZE)
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(copy_u8SrcElementSize<<DMA_SxCR_MSIZE);
		DMA1->DMA_STREAM[copy_u8StrID].CR |= (copy_u8SrcElementSize<<(DMA_SxCR_MSIZE+1));
	}

	//Disabled by Circular Default
	DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(1<<DMA_SxCR_CIRC);

	//Enable Direct Mode By default
	DMA1->DMA_STREAM[copy_u8StrID].FCR &= ~(1<<DMA_SxFCR_DMDIS);

	// Memory to memory
	//Set Source Address memory 1
	DMA1->DMA_STREAM[copy_u8StrID].M0AR = copy_u32SrcAdd;
	//Set Destination Address memory 2
	DMA1->DMA_STREAM[copy_u8StrID].M1AR = copy_u32DistAdd;
	// BlockSize
	DMA1->DMA_STREAM[copy_u8StrID].NDTR = copy_u16BlockSize;
}

void DMA1_voidStreamInterruptConfiguration(u8 copy_u8StrID,u8 copy_u8TCIE,u8 copy_u8HTIE,u8 copy_u8DMEIE,u8 copy_u8TEIE)
{
	if(copy_u8TCIE == ENABLED)
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR |= (1<<DMA_SxCR_TCIE);
	}
	else
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(1<<DMA_SxCR_TCIE);
	}

	if(copy_u8HTIE == ENABLED)
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR |= (1<<DMA_SxCR_HTIE);
	}
	else
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(1<<DMA_SxCR_HTIE);
	}

	if(copy_u8DMEIE == ENABLED)
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR |= (1<<DMA_SxCR_DMEIE);
	}
	else
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(1<<DMA_SxCR_DMEIE);
	}

	if(copy_u8TEIE == ENABLED)
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR |= (1<<DMA_SxCR_TEIE);
	}
	else
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(1<<DMA_SxCR_TEIE);
	}
}

void DMA1_voidSetStreamFIFOConfiguration(u8 copy_u8StrID,u8 copy_u8FifoThreshold,u8 copy_SrcBurstSize,u8 copy_DestBurstSize,u8 copy_u8FifoInterruptEnable)
{
	// Set Threshold
	DMA1->DMA_STREAM[copy_u8StrID].FCR = copy_u8FifoThreshold;

	//Disable Direct Mode
	DMA1->DMA_STREAM[copy_u8StrID].FCR |= (1<<DMA_SxFCR_DMDIS);

	if(copy_u8FifoInterruptEnable == ENABLED)
	{
		DMA1->DMA_STREAM[copy_u8StrID].FCR |= (1<<DMA_SxFCR_FEIE);
	}
	else
	{
		DMA1->DMA_STREAM[copy_u8StrID].FCR &= ~(1<<DMA_SxFCR_FEIE);
	}

	if(copy_SrcBurstSize == DMA_INC_BY_1)
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(copy_SrcBurstSize<<DMA_SxCR_PBURST);
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(copy_SrcBurstSize<<(DMA_SxCR_PBURST+1));
	}
	else if(copy_SrcBurstSize == DMA_INC_BY_4)
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR |= (copy_SrcBurstSize<<DMA_SxCR_PBURST);
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(copy_SrcBurstSize<<(DMA_SxCR_PBURST+1));
	}
	else if(copy_SrcBurstSize == DMA_INC_BY_8)
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(copy_SrcBurstSize<<DMA_SxCR_PBURST);
		DMA1->DMA_STREAM[copy_u8StrID].CR |= (copy_SrcBurstSize<<(DMA_SxCR_PBURST+1));
	}
	else if(copy_SrcBurstSize == DMA_INC_BY_16)
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR |= (copy_SrcBurstSize<<DMA_SxCR_MBURST);
		DMA1->DMA_STREAM[copy_u8StrID].CR |= (copy_SrcBurstSize<<(DMA_SxCR_MBURST+1));
	}

	if(copy_DestBurstSize == DMA_INC_BY_1)
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(copy_SrcBurstSize<<DMA_SxCR_MBURST);
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(copy_SrcBurstSize<<(DMA_SxCR_MBURST+1));
	}
	else if(copy_DestBurstSize == DMA_INC_BY_4)
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR |= (copy_SrcBurstSize<<DMA_SxCR_MBURST);
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(copy_SrcBurstSize<<(DMA_SxCR_MBURST+1));
	}
	else if(copy_DestBurstSize == DMA_INC_BY_8)
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR &= ~(copy_SrcBurstSize<<DMA_SxCR_MBURST);
		DMA1->DMA_STREAM[copy_u8StrID].CR |= (copy_SrcBurstSize<<(DMA_SxCR_MBURST+1));
	}
	else if(copy_DestBurstSize == DMA_INC_BY_16)
	{
		DMA1->DMA_STREAM[copy_u8StrID].CR |= (copy_SrcBurstSize<<DMA_SxCR_MBURST);
		DMA1->DMA_STREAM[copy_u8StrID].CR |= (copy_SrcBurstSize<<(DMA_SxCR_MBURST+1));
	}
}

void DMA1_voidStreamSetCallBack(PtrToFunc_void copy_SetCallBackFunc,u8 copy_u8StrID)
{
	if(copy_SetCallBackFunc != NULL)
	{
		DMA1_setCallBack[copy_u8StrID]= copy_SetCallBackFunc;
	}
	else
	{
		//Do Nothing
	}
}




void DMA1_Stream0_IRQHandler(void)
{
	if(DMA1_setCallBack[0]!=NULL)
	{
		DMA1_setCallBack[0]();
	}
	else
	{
		//Do Nothing
	}
}

void DMA1_Stream1_IRQHandler(void)
{
	if(DMA1_setCallBack[1]!=NULL)
	{
		DMA1_setCallBack[1]();
	}
	else
	{
		//Do Nothing
	}
}

void DMA1_Stream2_IRQHandler(void)
{
	if(DMA1_setCallBack[2]!=NULL)
	{
		DMA1_setCallBack[2]();
	}
	else
	{
		//Do Nothing
	}
}

void DMA1_Stream3_IRQHandler(void)
{
	if(DMA1_setCallBack[3]!=NULL)
	{
		DMA1_setCallBack[3]();
	}
	else
	{
		//Do Nothing
	}
}

void DMA1_Stream4_IRQHandler(void)
{
	if(DMA1_setCallBack[4]!=NULL)
	{
		DMA1_setCallBack[4]();
	}
	else
	{
		//Do Nothing
	}
}

void DMA1_Stream5_IRQHandler(void)
{
	if(DMA1_setCallBack[5]!=NULL)
	{
		DMA1_setCallBack[5]();
	}
	else
	{
		//Do Nothing
	}
}

void DMA1_Stream6_IRQHandler(void)
{
	if(DMA1_setCallBack[6]!=NULL)
	{
		DMA1_setCallBack[6]();
	}
	else
	{
		//Do Nothing
	}
}

void DMA1_Stream7_IRQHandler(void)
{
	if(DMA1_setCallBack[7]!=NULL)
	{
		DMA1_setCallBack[7]();
	}
	else
	{
		//Do Nothing
	}
}




#elif DMA2_ENABLE == DMA_ENABLED

void DMA2_voidStreamEnableCircMode(u8 copy_u8StrID,u8 copy_u8StrMode ,u8 copy_u8StrPriority)
{
	u32 Local_u32TempCR = 0;
	if(copy_u8StrMode== DMA_P2M_MODE)
	{
		// Choose Mode
		Local_u32TempCR &= ~((1<<DMA_SxCR_DIR)|(1<<(DMA_SxCR_DIR+1)));

		// Choose PINC & MINC mode
		Local_u32TempCR |= (1<<DMA_SxCR_MINC);
		Local_u32TempCR &= ~(1<<DMA_SxCR_PINC);
	}
	else if(copy_u8StrMode == DMA_M2P_MODE)
	{
		// Choose Mode
		Local_u32TempCR |= (1<<DMA_SxCR_DIR);
		Local_u32TempCR &= ~(1<<(DMA_SxCR_DIR+1));
		// Choose PINC & MINC mode
		Local_u32TempCR &= ~(1<<DMA_SxCR_MINC);
		Local_u32TempCR |= (1<<DMA_SxCR_PINC);
	}
	//Configure Priority
	if(copy_u8StrPriority == DMA_LOW_PRIORITY)
	{
		Local_u32TempCR &= ~(1<<DMA_SxCR_PL);
		Local_u32TempCR &= ~(1<<(DMA_SxCR_PL+1));
	}
	else if(copy_u8StrPriority == DMA_MEDIUM_PRIORITY)
	{
		Local_u32TempCR |= (1<<DMA_SxCR_PL);
		Local_u32TempCR &= ~(1<<(DMA_SxCR_PL+1));
	}
	else if(copy_u8StrPriority == DMA_HIGH_PRIORITY)
	{
		Local_u32TempCR &= ~(1<<DMA_SxCR_PL);
		Local_u32TempCR |= (1<<(DMA_SxCR_PL+1));
	}
	else if(copy_u8StrPriority == DMA_VERY_HIGH_PRIORITY)
	{
		Local_u32TempCR |= (1<<DMA_SxCR_PL);
		Local_u32TempCR |= (1<<(DMA_SxCR_PL+1));
	}

	//Enable Circular
	Local_u32TempCR |= (1<<DMA_SxCR_CIRC);

	DMA2->DMA_STREAM[copy_u8StrID].CR |= Local_u32TempCR;

	//Enable DMA
	DMA2->DMA_STREAM[copy_u8StrID].CR |= (1<<DMA_SxCR_EN);
}



void DMA2_voidStreamEnable(u8 copy_u8StrID,u8 copy_u8StrMode ,u8 copy_u8StrPriority)
{
	u32 Local_u32TempCR = 0;
	if(copy_u8StrMode== DMA_P2M_MODE)
	{
		// Choose Mode
		Local_u32TempCR &= ~((1<<DMA_SxCR_DIR)|(1<<(DMA_SxCR_DIR+1)));

		// Choose PINC & MINC mode
		Local_u32TempCR |= (1<<DMA_SxCR_MINC);
		Local_u32TempCR &= ~(1<<DMA_SxCR_PINC);
	}
	else if(copy_u8StrMode == DMA_M2P_MODE)
	{
		// Choose Mode
		Local_u32TempCR |= (1<<DMA_SxCR_DIR);
		Local_u32TempCR &= ~(1<<(DMA_SxCR_DIR+1));
		// Choose PINC & MINC mode
		Local_u32TempCR &= ~(1<<DMA_SxCR_MINC);
		Local_u32TempCR |= (1<<DMA_SxCR_PINC);
	}
	else if(copy_u8StrMode == DMA_M2M_MODE)
	{
		// Choose Mode

		Local_u32TempCR &= ~(1<<DMA_SxCR_DIR);
		Local_u32TempCR |= (1<<(DMA_SxCR_DIR+1));
		// Choose PINC & MINC mode
		Local_u32TempCR |= (1<<DMA_SxCR_PINC)|(1<<DMA_SxCR_MINC);
	}

	//Configure Priority
	if(copy_u8StrPriority == DMA_LOW_PRIORITY)
	{
		Local_u32TempCR &= ~(1<<DMA_SxCR_PL);
		Local_u32TempCR &= ~(1<<(DMA_SxCR_PL+1));
	}
	else if(copy_u8StrPriority == DMA_MEDIUM_PRIORITY)
	{
		Local_u32TempCR |= (1<<DMA_SxCR_PL);
		Local_u32TempCR &= ~(1<<(DMA_SxCR_PL+1));
	}
	else if(copy_u8StrPriority == DMA_HIGH_PRIORITY)
	{
		Local_u32TempCR &= ~(1<<DMA_SxCR_PL);
		Local_u32TempCR |= (1<<(DMA_SxCR_PL+1));
	}
	else if(copy_u8StrPriority == DMA_VERY_HIGH_PRIORITY)
	{
		Local_u32TempCR |= (1<<DMA_SxCR_PL);
		Local_u32TempCR |= (1<<(DMA_SxCR_PL+1));
	}

	DMA2->DMA_STREAM[copy_u8StrID].CR |= Local_u32TempCR;

	//Enable DMA
	DMA2->DMA_STREAM[copy_u8StrID].CR |= (1<<DMA_SxCR_EN);
}

void DMA2_voidSetStreamConfiguration(u8 copy_u8StrID,u8 copy_u8ChID,u32* copy_u32SrcAdd,u32* copy_u32DistAdd,u8 copy_u8SrcElementSize,u8 copy_u8DistElementSize,u16 copy_u16BlockSize)
{

	DMA2->DMA_STREAM[copy_u8StrID].CR = (copy_u8ChID<<DMA_SxCR_CHSEL);

	// Choose Source Word Size
	if(copy_u8SrcElementSize == DMA_BYTE_SIZE)
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<DMA_SxCR_PSIZE);
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<(DMA_SxCR_PSIZE+1));
	}
	else if(copy_u8SrcElementSize == DMA_HWORD_SIZE)
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR |= (1<<DMA_SxCR_PSIZE);
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<(DMA_SxCR_PSIZE+1));
	}
	else if(copy_u8SrcElementSize == DMA_WORD_SIZE)
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<DMA_SxCR_PSIZE);
		DMA2->DMA_STREAM[copy_u8StrID].CR |= (1<<(DMA_SxCR_PSIZE+1));
	}

	// Choose Word Size
	if(copy_u8DistElementSize == DMA_BYTE_SIZE)
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<DMA_SxCR_MSIZE);
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<(DMA_SxCR_MSIZE+1));
	}
	else if(copy_u8DistElementSize == DMA_HWORD_SIZE)
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR |= (1<<DMA_SxCR_MSIZE);
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<(DMA_SxCR_MSIZE+1));
	}
	else if(copy_u8DistElementSize == DMA_WORD_SIZE)
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<DMA_SxCR_MSIZE);
		DMA2->DMA_STREAM[copy_u8StrID].CR |= (1<<(DMA_SxCR_MSIZE+1));
	}

	//Disabled by Circular Default
	DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<DMA_SxCR_CIRC);

	//Enable Direct Mode By default
	DMA2->DMA_STREAM[copy_u8StrID].FCR &= ~(1<<DMA_SxFCR_DMDIS);

	// Memory to memory
	//Set Source Address memory 1
	DMA2->DMA_STREAM[copy_u8StrID].PAR =(u32)copy_u32SrcAdd;
	//Set Destination Address memory 2
	DMA2->DMA_STREAM[copy_u8StrID].M0AR =(u32)copy_u32DistAdd;
	// BlockSize
	DMA2->DMA_STREAM[copy_u8StrID].NDTR = copy_u16BlockSize;
}

void DMA2_voidStreamInterruptConfiguration(u8 copy_u8StrID,u8 copy_u8TCIE,u8 copy_u8HTIE,u8 copy_u8DMEIE,u8 copy_u8TEIE)
{
	if(copy_u8TCIE == ENABLED)
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR |= (1<<DMA_SxCR_TCIE);
	}
	else
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<DMA_SxCR_TCIE);
	}

	if(copy_u8HTIE == ENABLED)
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR |= (1<<DMA_SxCR_HTIE);
	}
	else
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<DMA_SxCR_HTIE);
	}

	if(copy_u8DMEIE == ENABLED)
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR |= (1<<DMA_SxCR_DMEIE);
	}
	else
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<DMA_SxCR_DMEIE);
	}

	if(copy_u8TEIE == ENABLED)
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR |= (1<<DMA_SxCR_TEIE);
	}
	else
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<DMA_SxCR_TEIE);
	}
}

void DMA2_voidSetStreamFIFOConfiguration(u8 copy_u8StrID,u8 copy_u8FifoThreshold,u8 copy_SrcBurstSize,u8 copy_DestBurstSize,u8 copy_u8FifoInterruptEnable)
{
	// Set Threshold
	DMA2->DMA_STREAM[copy_u8StrID].FCR = copy_u8FifoThreshold;

	//Disable Direct Mode
	DMA2->DMA_STREAM[copy_u8StrID].FCR |= (1<<DMA_SxFCR_DMDIS);

	if(copy_u8FifoInterruptEnable == ENABLED)
	{
		DMA2->DMA_STREAM[copy_u8StrID].FCR |= (1<<DMA_SxFCR_FEIE);
	}
	else
	{
		DMA2->DMA_STREAM[copy_u8StrID].FCR &= ~(1<<DMA_SxFCR_FEIE);
	}

	if(copy_SrcBurstSize == DMA_INC_BY_1)
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<DMA_SxCR_PBURST);
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<(DMA_SxCR_PBURST+1));
	}
	else if(copy_SrcBurstSize == DMA_INC_BY_4)
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR |= (1<<DMA_SxCR_PBURST);
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<(DMA_SxCR_PBURST+1));
	}
	else if(copy_SrcBurstSize == DMA_INC_BY_8)
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<DMA_SxCR_PBURST);
		DMA2->DMA_STREAM[copy_u8StrID].CR |= (1<<(DMA_SxCR_PBURST+1));
	}
	else if(copy_SrcBurstSize == DMA_INC_BY_16)
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR |= (1<<DMA_SxCR_MBURST);
		DMA2->DMA_STREAM[copy_u8StrID].CR |= (1<<(DMA_SxCR_MBURST+1));
	}

	if(copy_DestBurstSize == DMA_INC_BY_1)
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<DMA_SxCR_MBURST);
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<(DMA_SxCR_MBURST+1));
	}
	else if(copy_DestBurstSize == DMA_INC_BY_4)
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR |= (1<<DMA_SxCR_MBURST);
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<(DMA_SxCR_MBURST+1));
	}
	else if(copy_DestBurstSize == DMA_INC_BY_8)
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR &= ~(1<<DMA_SxCR_MBURST);
		DMA2->DMA_STREAM[copy_u8StrID].CR |= (1<<(DMA_SxCR_MBURST+1));
	}
	else if(copy_DestBurstSize == DMA_INC_BY_16)
	{
		DMA2->DMA_STREAM[copy_u8StrID].CR |= (1<<DMA_SxCR_MBURST);
		DMA2->DMA_STREAM[copy_u8StrID].CR |= (1<<(DMA_SxCR_MBURST+1));
	}
}

void DMA2_voidStreamSetCallBack(PtrToFunc_void copy_SetCallBackFunc,u8 copy_u8StrID)
{
	if(copy_SetCallBackFunc != NULL)
	{
		DMA2_setCallBack[copy_u8StrID]= copy_SetCallBackFunc;
	}
	else
	{
		//Do Nothing
	}
}




void DMA2_Stream0_IRQHandler(void)
{
	if(DMA2_setCallBack[0]!=NULL)
	{
		DMA2_setCallBack[0]();
	}
	else
	{
		//Do Nothing
	}
}

void DMA2_Stream1_IRQHandler(void)
{
	if(DMA2_setCallBack[1]!=NULL)
	{
		DMA2_setCallBack[1]();
	}
	else
	{
		//Do Nothing
	}
}

void DMA2_Stream2_IRQHandler(void)
{
	if(DMA2_setCallBack[2]!=NULL)
	{
		DMA2_setCallBack[2]();
	}
	else
	{
		//Do Nothing
	}
}

void DMA2_Stream3_IRQHandler(void)
{
	if(DMA2_setCallBack[3]!=NULL)
	{
		DMA2_setCallBack[3]();
	}
	else
	{
		//Do Nothing
	}
}

#endif


void DMA2_Stream4_IRQHandler(void)
{
	if(DMA2_setCallBack[4]!=NULL)
	{
		DMA2_setCallBack[4]();
	}
	else
	{
		//Do Nothing
	}
}

void DMA2_Stream5_IRQHandler(void)
{
	if(DMA2_setCallBack[5]!=NULL)
	{
		DMA2_setCallBack[5]();
	}
	else
	{
		//Do Nothing
	}
}

void DMA2_Stream6_IRQHandler(void)
{
	if(DMA2_setCallBack[6]!=NULL)
	{
		DMA2_setCallBack[6]();
	}
	else
	{
		//Do Nothing
	}
}

void DMA2_Stream7_IRQHandler(void)
{
	if(DMA2_setCallBack[7]!=NULL)
	{
		DMA2_setCallBack[7]();
	}
	else
	{
		//Do Nothing
	}
}


