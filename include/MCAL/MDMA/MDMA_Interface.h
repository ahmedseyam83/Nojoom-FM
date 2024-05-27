/*
 * MDMA_Interface.h
 *
 *  Created on: 15 May 2024
 *      Author: User
 */

#ifndef MDMA_INTERFACE_H_
#define MDMA_INTERFACE_H_




/*********************STREAM*****************************/

#define DMA_STREAM0 					0
#define DMA_STREAM1 					1
#define DMA_STREAM2 					2
#define DMA_STREAM3 					3
#define DMA_STREAM4 					4
#define DMA_STREAM5 					5
#define DMA_STREAM6 					6
#define DMA_STREAM7 					7

/**************DMA1 CHANNELS********************/
/************STREAM0***********/
#define DMA_ST0_CH_SPI3_RX 					0
#define DMA_ST0_CH_I2C1_RX 					1
#define DMA_ST0_CH_TIM4_CH1	 				2
#define DMA_ST0_CH_I2S3_EXT_RX 				3
#define DMA_ST0_CH_TIM5_CH3	 				6
#define DMA_ST0_CH_TIM5_UP		 			6

/************STREAM1***********/
#define DMA_ST1_CH_I2C3_RX					1
#define DMA_ST1_CH_TIM2_UP					3
#define DMA_ST1_CH_TIM2_CH3					3
#define DMA_ST1_CH_TIM5_CH4					6
#define DMA_ST1_CH_TIM5_UP					6

/************STREAM2***********/
#define DMA_ST2_CH_SPI3_RX					0
#define DMA_ST2_CH_I2S3_EXT_RX				2
#define DMA_ST2_CH_I2C3_RX					3
#define DMA_ST2_CH_TIM3_CH4					5
#define DMA_ST2_CH_TIM3_UP					5
#define DMA_ST2_CH_TIM5_CH1					6
#define DMA_ST2_CH_I2C2_RX					7

/************STREAM3***********/
#define DMA_ST3_CH_SPI2_RX					0
#define DMA_ST3_CH_TIM4_CH2					2
#define DMA_ST3_CH_I2S2_EXT_RX				3
#define DMA_ST3_CH_TIM5_CH4					6
#define DMA_ST3_CH_TIM5_TRIG				6
#define DMA_ST3_CH_TIM5_CH1					6
#define DMA_ST3_CH_I2C2_RX					7

/************STREAM4***********/
#define DMA_ST4_CH_SPI2_TX					0
#define DMA_ST4_CH_I2S2_EXT_TX				2
#define DMA_ST4_CH_I2C3_TX					3
#define DMA_ST4_CH_TIM3_CH1					5
#define DMA_ST4_CH_TIM3_TRIG				5
#define DMA_ST4_CH_TIM5_CH2					6

/************STREAM5***********/
#define DMA_ST5_CH_SPI3_TX					0
#define DMA_ST5_CH_I2C1_RX					1
#define DMA_ST5_CH_I2S3_EXT_TX				2
#define DMA_ST5_CH_TIM2_CH1					3
#define DMA_ST5_CH_USART2_RX				4
#define DMA_ST5_CH_TIM3_CH2					5
#define DMA_ST5_CH_I2C3_TX					6

/************STREAM6***********/
#define DMA_ST6_CH_I2C1_TX					1
#define DMA_ST6_CH_TIM4_UP					2
#define DMA_ST6_CH_TIM2_CH2					3
#define DMA_ST6_CH_TIM2_CH4					3
#define DMA_ST6_CH_USART2_TX				4
#define DMA_ST6_CH_TIM5_UP					6

/************STREAM7***********/
#define DMA_ST7_CH_SPI3_TX					0
#define DMA_ST7_CH_I2C1_TX					1
#define DMA_ST7_CH_TIM4_CH3					2
#define DMA_ST7_CH_TIM2_UP					3
#define DMA_ST7_CH_TIM2_CH4					3
#define DMA_ST7_CH_TIM3_CH3					6
#define DMA_ST7_CH_I2C2_TX					7


/**************DMA2 CHANNELS********************/
/************STREAM0***********/
#define DMA_ST0_CH_ADC1						0
#define DMA_ST0_CH_SPI1_RX					3
#define DMA_ST0_CH_SPI4_RX					4
#define DMA_ST0_CH_TIM1_TRIG				6

/************STREAM1***********/
#define DMA_ST1_CH_SPI4_TX					4
#define DMA_ST1_CH_USART6_RX				5
#define DMA_ST1_CH_TIM1_CH1					6

/************STREAM2***********/
#define DMA_ST2_CH_SPI1_RX					3
#define DMA_ST2_CH_USART1_RX				4
#define DMA_ST2_CH_USART6_RX				5
#define DMA_ST2_CH_TIM1_CH2					6

/************STREAM3***********/
#define DMA_ST3_CH_SPI1_TX					3
#define DMA_ST3_CH_SDIO						4
#define DMA_ST3_CH_SPI4_RX					5
#define DMA_ST3_CH_TIM1_CH4					6
#define DMA_ST3_CH_TIM1_TRIG				6
#define DMA_ST3_CH_TIM1_COM					6

/************STREAM6***********/
#define DMA_ST6_CH_TIM1_CH01				0
#define DMA_ST6_CH_TIM1_CH02				0
#define DMA_ST6_CH_TIM1_CH03				0
#define DMA_ST6_CH_SDIO						4
#define DMA_ST6_CH_USART1_TX				5
#define DMA_ST6_CH_TIM1_CH3					6

/************STREAM7***********/
#define DMA_ST7_CH_USART1_TX				4
#define DMA_ST7_CH_USART6_TX				5

/***************************************************************************************/
/*********************Data Size*****************************/
#define DMA_BYTE_SIZE					0
#define DMA_HWORD_SIZE					1
#define DMA_WORD_SIZE					2

/*********************FIFO THRESHOLD*****************************/
#define DMA_FIFO_1_4					0
#define DMA_FIFO_1_2					1
#define DMA_FIFO_3_4					2
#define DMA_FIFO_FULL					3

/********************Priority Level***********************************/
#define DMA_LOW_PRIORITY				0
#define DMA_MEDIUM_PRIORITY				1
#define DMA_HIGH_PRIORITY				2
#define DMA_VERY_HIGH_PRIORITY			3

/*********************Data Transfer Direction*****************************/
#define	DMA_P2M_MODE					0
#define	DMA_M2P_MODE					1
#define	DMA_M2M_MODE					2

/*********************Burst Increment*****************************/
#define DMA_INC_BY_1					0
#define DMA_INC_BY_4					1
#define DMA_INC_BY_8					2
#define DMA_INC_BY_16					3

/*****************************************************************/
#define DISABLED						0
#define ENABLED							1

/************************************************************************************************/
/*									FUNCTIONS API's												*/
/************************************************************************************************/

/************************************ DMA 1 API's **************************************/
void DMA1_voidSetStreamFIFOConfiguration(u8 copy_u8StrID,u8 copy_u8FifoThreshold,u8 copy_SrcBurstSize,u8 copy_DestBurstSize,u8 copy_u8FifoInterruptEnable);
void DMA1_voidStreamInterruptConfiguration(u8 copy_u8StrID,u8 copy_u8TCIE,u8 copy_u8HTIE,u8 copy_u8DMEIE,u8 copy_u8TEIE);
void DMA1_voidSetStreamConfiguration(u8 copy_u8StrID,u8 copy_u8ChID,u32* copy_u32SrcAdd,u32* copy_u32DistAdd,u8 copy_u8SrcElementSize,u8 copy_u8DistElementSize,u16 copy_u16BlockSize);

void DMA1_voidStreamSetCallBack(PtrToFunc_void copy_SetCallBackFunc,u8 copy_u8StrID);

void DMA1_voidStreamEnable(u8 copy_u8StrID,u8 copy_u8StrMode ,u8 copy_u8StrPriority);
void DMA1_voidStreamEnableCircMode(u8 copy_u8StrID,u8 copy_u8StrMode ,u8 copy_u8StrPriority);


/*****************************************************************************************************************************************************************************************/

/************************************ DMA 2 API's **************************************/
void DMA2_voidSetStreamFIFOConfiguration(u8 copy_u8StrID,u8 copy_u8FifoThreshold,u8 copy_SrcBurstSize,u8 copy_DestBurstSize,u8 copy_u8FifoInterruptEnable);
void DMA2_voidStreamInterruptConfiguration(u8 copy_u8StrID,u8 copy_u8TCIE,u8 copy_u8HTIE,u8 copy_u8DMEIE,u8 copy_u8TEIE);
void DMA2_voidSetStreamConfiguration(u8 copy_u8StrID,u8 copy_u8ChID,u32* copy_u32SrcAdd,u32* copy_u32DistAdd,u8 copy_u8SrcElementSize,u8 copy_u8DistElementSize,u16 copy_u16BlockSize);

void DMA2_voidStreamSetCallBack(PtrToFunc_void copy_SetCallBackFunc,u8 copy_u8StrID);

void DMA2_voidStreamEnable(u8 copy_u8StrID,u8 copy_u8StrMode ,u8 copy_u8StrPriority);
void DMA2_voidStreamEnableCircMode(u8 copy_u8StrID,u8 copy_u8StrMode ,u8 copy_u8StrPriority);






#endif /* MDMA_INTERFACE_H_ */
