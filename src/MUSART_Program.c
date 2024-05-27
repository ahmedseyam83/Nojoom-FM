/*
 * MUSART_Program.c
 *
 *  Created on: 8 May 2024
 *      Author: User
 */


/************************************************************************/
/*							FILES INCLUSIONS							*/
/************************************************************************/
/*******************************LIB**************************************/
#include "../include/LIB/STD_Types.h"
#include "../include/LIB/BIT_Math.h"
#include "../include/MCAL/MRCC/MRCC_Interface.h"
#include "../include/MCAL/MUSART/MUSART_Interface.h"
#include "../include/MCAL/MUSART/MUSART_Private.h"
#include "../include/MCAL/MUSART/MUSART_Config.h"

/*******************Global Variables***************/
/*Global variable to carry the send Data*/
static const u8* USART_pu8SendData = NULL;

/*Global variable to carry the Receive Data*/
static u8* USART_pu8ReceiveData = NULL;

/*Global variable to carry the buffer size*/
static u8 USART_u8BufferSize;

/*Global variable to indicate for the current Data index of the buffer*/
static u8 USART_u8Index;

/*Global pointer to function to carry the notification function called by ISR*/
static void (* USART_pvNotificationFunc)(void)= NULL;

/*Global flag for the USART Busy State*/
static u8 USART_u8State= IDLE ;



/************************************************************************/
/*						   FUNCTIONS DEFINITIONS						*/
/************************************************************************/

static void MUSART_voidSetBaudRate(void)
{
	u8 AHB_Prescaler,APB_Prescaler;
	u16 Local_u16MPart,Local_u16FPart;
	u32 Local_u32BR,APB_Clock,AHB_Clock;
#if ( (USART_ENABLE_SELECT == USART1_ENABLE) || (USART_ENABLE_SELECT == USART6_ENABLE) )
	AHB_Prescaler = MRCC_voidGetAHBPrescaler();
	AHB_Clock= SYSTEM_FREQUENCY / AHB_Prescaler;
	APB_Prescaler = MRCC_voidGetAPB2Prescaler();
	APB_Clock= AHB_Clock / APB_Prescaler;
#elif USART_ENABLE_SELECT == USART2_ENABLE
	AHB_Prescaler = MRCC_voidGetAHBPrescaler();
	AHB_Clock= SYSTEM_FREQUENCY / AHB_Prescaler;
	APB_Prescaler = MRCC_voidGetAPB1Prescaler();
	APB_Clock= AHB_Clock / APB_Prescaler;
#else
#error
	"WRONG USART_ENABLE_SELECT configuration parameters"
#endif

	/* Calculate the baud rate from the equation*/
	Local_u32BR= ( (25*APB_Clock) / (2*(2-OVER_SAMPLE)*(USART_BAUD_RATE)));
	Local_u16MPart = ((Local_u32BR) / 100) ;
	Local_u16FPart = (((Local_u32BR -(Local_u16MPart * 100))*16) + 50)/100;

	if(Local_u16FPart > 15)
	{
		Local_u16FPart = 0;
		Local_u16MPart += 1;
	}

#if	(USART_ENABLE_SELECT == USART1_ENABLE )
	USART1->BRR = Local_u16MPart<< USART_BRR_DIV_Mantissa | Local_u16FPart<< USART_BRR_DIV_Fraction;
#elif (USART_ENABLE_SELECT == USART6_ENABLE)
	USART6->BRR = Local_u16MPart<< USART_BRR_DIV_Mantissa | Local_u16FPart<< USART_BRR_DIV_Fraction;
#elif USART_ENABLE_SELECT == USART2_ENABLE
	USART2->BRR = Local_u16MPart<< USART_BRR_DIV_Mantissa | Local_u16FPart<< USART_BRR_DIV_Fraction;
#else
#error
	"WRONG USART_ENABLE_SELECT configuration parameters"
#endif
}


void MUSART_voidInit(void)
{
	u32 Local_u32UCR1=0,Local_u32UCR2=0,Local_u32UCR3=0;
	/* Set Baud Rate */
	MUSART_voidSetBaudRate();
	/************* Check 3 Modes ***************/
	/*Set Stop Bits*/
	Local_u32UCR2 = USART_STOP_BIT<<USART_CR2_STOP;

	/*Set USART_MODE*/
#if USART_MODE == ASYNCHRONOUS
	CLR_BIT(Local_u32UCR2,USART_CR2_CLKEN);
#elif USART_MODE == SYNCHRONOUS
	/*Enable Clock*/
	SET_BIT(Local_u32UCR2,USART_CR2_CLKEN);
	/*Set CPOL*/
#if	USART_CLOCK_POLARITY == XCK_RISING_TX_XCH_FALLING_RX
	CLR_BIT(Local_u32UCR2,USART_CR2_CPOL);
#elif USART_CLOCK_POLARITY == XCK_RISING_RX_XCH_FALLING_TX
	SET_BIT(Local_u32UCR2,USART_CR2_CPOL);
#else
#error "WRONG USART_CLOCK_POLARITY configuration parameters"
#endif

	/*Set CPHA*/
#if	USART_CLOCK_PHASE == CAPTURE_LEADING_SAMPLE_TRAILING
	CLR_BIT(Local_u32UCR2,USART_CR2_CPHA);
#elif USART_CLOCK_PHASE == SAMPLE_LEADING_CAPTURE_TRAILING
	SET_BIT(Local_u32UCR2,USART_CR2_CPHA);
#else
#error "WRONG USART_CLOCK_POLARITY configuration parameters"
#endif



#else
#error "WRONG USART_MODE configuration parameters"
#endif

#if USART_HARWARE_CONTROL == DISABLE
	CLR_BIT(Local_u32UCR3,USART_CR3_CTSE);
	CLR_BIT(Local_u32UCR3,USART_CR3_RTSE);
#elif USART_HARWARE_CONTROL == ENABLE
	SET_BIT(Local_u32UCR3,USART_CR3_CTSE);
	SET_BIT(Local_u32UCR3,USART_CR3_RTSE);

#else
#error "WRONG USART_MODE configuration parameters"
#endif


	/*Set Parity mode*/
#if USART_PARITY_MODE == DISABLE
	CLR_BIT(Local_u32UCR1,USART_CR1_PCE);
#elif USART_PARITY_MODE == EVEN_PARITY
	SET_BIT(Local_u32UCR1,USART_CR1_PCE);
	CLR_BIT(Local_u32UCR1,USART_CR1_PS);
#elif USART_PARITY_MODE == ODD_PARITY
	SET_BIT(Local_u32UCR1,USART_CR1_PCE);
	SET_BIT(Local_u32UCR1,USART_CR1_PS);
#else
#error "WRONG USART_PARITY_MODE configuration parameters"
#endif

#if USART_ADRESS_MODE == DISABLE
	CLR_BIT(Local_u32UCR1,USART_CR1_WAKE);
#elif USART_ADRESS_MODE == ENABLE
	/*Set WAKE BIT*/
	SET_BIT(Local_u32UCR1,USART_CR1_WAKE);
	/*Set Device Address*/
	Local_u32UCR2 |= USART_ADDRESS<<USART_CR2_ADD;
#else
#error "WRONG USART_TX_COMPLETE_INTERRUPT configuration parameters"
#endif

	/*Set Data Size*/
#if USART_DATA_SIZE == DATA_SIZE_8_BIT
	CLR_BIT(Local_u32UCR1,USART_CR1_M);
#elif USART_DATA_SIZE == DATA_SIZE_9_BIT
	SET_BIT(Local_u32UCR1,USART_CR1_M);
#else
#error "WRONG UART_DATA_SIZE configuration parameters"
#endif




#if USART_CTS_INTERRUPT == DISABLE
	CLR_BIT(Local_u32UCR3,USART_CR3_CTSIE);
#elif USART_CTS_INTERRUPT == ENABLE
	SET_BIT(Local_u32UCR3,USART_CR3_CTSIE);
#else
#error "WRONG USART_RX_COMPLETE_INTERRUPT configuration parameters"
#endif

	/* Store the local variable in UCSRC Register*/

#if USART_TX_COMPLETE_INTERRUPT == DISABLE
	CLR_BIT(Local_u32UCR1,USART_CR1_TCIE);
#elif USART_TX_COMPLETE_INTERRUPT == ENABLE
	SET_BIT(Local_u32UCR1,USART_CR1_TCIE);
#else
#error "WRONG USART_TX_COMPLETE_INTERRUPT configuration parameters"
#endif

#if USART_TX_BUFFER_EMPTY_INTERRUPT == DISABLE
	CLR_BIT(Local_u32UCR1,USART_CR1_TXEIE);
#elif USART_TX_BUFFER_EMPTY_INTERRUPT == ENABLE
	SET_BIT(Local_u32UCR1,USART_CR1_TXEIE);
#else
#error "WRONG USART_TX_COMPLETE_INTERRUPT configuration parameters"
#endif


#if USART_RX_COMPLETE_INTERRUPT == DISABLE
	CLR_BIT(Local_u32UCR1,USART_CR1_RXNEIE);
#elif USART_RX_COMPLETE_INTERRUPT == ENABLE
	SET_BIT(Local_u32UCR1,USART_CR1_RXNEIE);
#else
#error "WRONG USART_RX_COMPLETE_INTERRUPT configuration parameters"
#endif




#if USART_RECEIVER_ENABLE == DISABLE
	CLR_BIT(Local_u32UCR1,USART_CR1_RE);
#elif USART_RECEIVER_ENABLE == ENABLE
	SET_BIT(Local_u32UCR1,USART_CR1_RE);
#else
#error "WRONG USART_RECEIVER_ENABLE configuration parameters"
#endif

#if USART_TRANSMITTER_ENABLE == DISABLE
	CLR_BIT(Local_u32UCR1,USART_CR1_TE);
#elif USART_TRANSMITTER_ENABLE == ENABLE
	SET_BIT(Local_u32UCR1,USART_CR1_TE);
#else
#error "WRONG USART_TRANSMITTER_ENABLE configuration parameters"
#endif


#if	(USART_ENABLE_SELECT == USART1_ENABLE )
	USART1->CR1 = Local_u32UCR1;
	USART1->CR2 = Local_u32UCR2;
	USART1->CR3 = Local_u32UCR3;

	SET_BIT(USART1->CR1,USART_CR1_UE);
#elif (USART_ENABLE_SELECT == USART6_ENABLE)
	USART6->CR1 = Local_u32UCR1;
	USART6->CR2 = Local_u32UCR2;
	USART6->CR3 = Local_u32UCR3;
	SET_BIT(USART6->CR1,USART_CR1_UE);
#elif USART_ENABLE_SELECT == USART2_ENABLE
	USART2->CR1 = Local_u32UCR1;
	USART2->CR2 = Local_u32UCR2;
	USART2->CR3 = Local_u32UCR3;
	SET_BIT(USART3->CR1,USART_CR1_UE);
#else
#error
	"WRONG USART_ENABLE_SELECT configuration parameters"
#endif

}

void MUSART_voidSendByteSynch(u8 copy_u8Data)
{
	while(GET_BIT(USART1->SR,USART_SR_TXE)==RESET);

#if	(USART_ENABLE_SELECT == USART1_ENABLE )
	USART1->DR= copy_u8Data;
#elif (USART_ENABLE_SELECT == USART6_ENABLE)
	USART6->DR= copy_u8Data;
#elif USART_ENABLE_SELECT == USART2_ENABLE
	USART2->DR= copy_u8Data;
#else
#error
	"WRONG USART_ENABLE_SELECT configuration parameters"
#endif
}

void MUSART_voidReceiveByte(u8* copy_u8Data)
{
	while(GET_BIT(USART1->SR,USART_SR_RXNE)==RESET);

#if	(USART_ENABLE_SELECT == USART1_ENABLE )
	*copy_u8Data =  USART1->DR;
#elif (USART_ENABLE_SELECT == USART6_ENABLE)
	*copy_u8Data =  USART6->DR;
#elif USART_ENABLE_SELECT == USART2_ENABLE
	*copy_u8Data =  USART2->DR;
#else
#error
	"WRONG USART_ENABLE_SELECT configuration parameters"
#endif
}
void MUSART_voidEnable(void)
{

#if	(USART_ENABLE_SELECT == USART1_ENABLE )
	SET_BIT(USART1->CR1,USART_CR1_UE);
#elif (USART_ENABLE_SELECT == USART6_ENABLE)
	SET_BIT(USART6->CR1,USART_CR1_UE);
#elif USART_ENABLE_SELECT == USART2_ENABLE
	SET_BIT(USART3->CR1,USART_CR1_UE);
#else
#error
	"WRONG USART_ENABLE_SELECT configuration parameters"
#endif
}

void MUSART_voidDisable(void)
{
#if	(USART_ENABLE_SELECT == USART1_ENABLE )
	CLR_BIT(USART1->CR1,USART_CR1_UE);
#elif (USART_ENABLE_SELECT == USART6_ENABLE)
	CLR_BIT(USART6->CR1,USART_CR1_UE);
#elif USART_ENABLE_SELECT == USART2_ENABLE
	CLR_BIT(USART3->CR1,USART_CR1_UE);
#else
#error
	"WRONG USART_ENABLE_SELECT configuration parameters"
#endif
}

void MUSART_voidSendString(u8* copy_u8Data)
{
	u16 local_u8Counter =0;
	while(copy_u8Data[local_u8Counter]!='\0')
	{
		MUSART_voidSendByteSynch(copy_u8Data[local_u8Counter]);
		local_u8Counter++;
	}
	MUSART_voidSendByteSynch('\0');
}

void MUSART_voidReceiveString(u8* copy_u8Data)
{
	u16 local_u8Counter = 0;
	while(copy_u8Data[local_u8Counter]!='\0')
	{
		MUSART_voidReceiveByte((u8*)copy_u8Data[local_u8Counter]);
		local_u8Counter++;
	}
	MUSART_voidReceiveByte((u8*)copy_u8Data[local_u8Counter]);
}

void MUSART_voidSendStringAsynch(const u8 * Copy_pchString , void (* NotificationFunc)(void))
{

	if (USART_u8State == IDLE)
	{
		if ((Copy_pchString != NULL) && (NotificationFunc != NULL))
		{
			/*USART is now Busy*/
			USART_u8State = BUSY ;

			/*Assign the USART data globally*/
			USART_pu8SendData = Copy_pchString ;
			USART_pvNotificationFunc = NotificationFunc ;

			/*Set Index to first element*/
			USART_u8Index = 0 ;


		#if	(USART_ENABLE_SELECT == USART1_ENABLE )
			/*USART Transmit Interrupt Enable*/
			SET_BIT(USART1->CR1,USART_CR1_TXEIE);
			/*Send first Data */
			USART1->DR= USART_pu8SendData[USART_u8Index];



		#elif (USART_ENABLE_SELECT == USART6_ENABLE)
			USART6->DR= USART_pu8SendData[USART_u8Index];
			SET_BIT(USART6->CR1,USART_CR1_TXEIE);
		#elif USART_ENABLE_SELECT == USART2_ENABLE
			USART2->DR= USART_pu8SendData[USART_u8Index];
			SET_BIT(USART2->CR1,USART_CR1_TXEIE);
		#else
		#error
			"WRONG USART_ENABLE_SELECT configuration parameters"
		#endif


		}
		else
		{
			/*Do Nothing*/
		}
	}
}

void MUSART_voidReceiveBufferAsynch(u8 * Copy_pchString , u32 Copy_u32BufferSize , void (* NotificationFunc)(void))
{

	if (USART_u8State == IDLE)
	{
		if ((Copy_pchString != NULL) && (NotificationFunc != NULL))
		{
			/*USART is now Busy*/
			USART_u8State = BUSY ;

			/*Assign the USART data globally*/
			USART_pu8ReceiveData = Copy_pchString ;
			USART_pvNotificationFunc = NotificationFunc ;
			USART_u8BufferSize = Copy_u32BufferSize;

			/*Set Index to first element*/
			USART_u8Index = 0 ;

			/*USART Recieve Interrupt Enable */
			#if	(USART_ENABLE_SELECT == USART1_ENABLE )
				SET_BIT(USART1->CR1,USART_CR1_RXNEIE);
			#elif (USART_ENABLE_SELECT == USART6_ENABLE)
				SET_BIT(USART6->CR1,USART_CR1_RXNEIE);
			#elif USART_ENABLE_SELECT == USART2_ENABLE
				SET_BIT(USART2->CR1,USART_CR1_RXNEIE);
			#else
			#error
				"WRONG USART_ENABLE_SELECT configuration parameters"
			#endif

		}
		else
		{
			/*Do Nothing*/
		}
	}
}

void USART1_IRQHandler(void)
{
	if(GET_BIT(USART1->SR,USART_SR_TXE)== SET)
	{
		/*Increment Data index of the buffer*/
		USART_u8Index++ ;

		if (USART_pu8SendData[USART_u8Index] == '\0')
		{
			/*Receive Data Complete*/
			USART_u8Index=0;

			/*USART is now IDLE*/
			USART_u8State = IDLE ;

			/*Call Notification Function*/
			USART_pvNotificationFunc() ;

			/*USART Transmit Interrupt Disable*/
			CLR_BIT(USART1->CR1,USART_CR1_TXEIE);

		}
		else
		{
			/*Send Data not Complete*/
			/*Send next Data*/
			USART1->CR1 = USART_pu8SendData[USART_u8Index] ;
		}
	}
	else if(GET_BIT(USART1->SR,USART_SR_RXNE)== SET)
	{
		/*Receive next Data*/
		USART_pu8ReceiveData[USART_u8Index] = USART1->DR ;

		/*Increment Data index of the buffer*/
		USART_u8Index++ ;

		if (USART_u8Index == USART_u8BufferSize)
		{
			/*Send Data Complete*/

			USART_u8Index=0;

			/*USART is now IDLE*/
			USART_u8State = IDLE ;

			/*Call Notification Function*/
			USART_pvNotificationFunc() ;

			/*USART Recieve Interrupt Disable*/
			CLR_BIT(USART1->CR1,USART_CR1_RXNEIE) ;
		}
		else
		{
			/*Do Nothing*/
		}

	}
}

void USART2_IRQHandler(void)
{
	if(GET_BIT(USART2->SR,USART_SR_TXE)== SET)
	{
		/*Increment Data index of the buffer*/
		USART_u8Index++ ;

		if (USART_pu8SendData[USART_u8Index] == '\0')
		{
			/*Receive Data Complete*/
			USART_u8Index=0;

			/*USART is now IDLE*/
			USART_u8State = IDLE ;

			/*Call Notification Function*/
			USART_pvNotificationFunc() ;

			/*USART Transmit Interrupt Disable*/
			CLR_BIT(USART2->CR1,USART_CR1_TXEIE);

		}
		else
		{
			/*Send Data not Complete*/
			/*Send next Data*/
			USART2->CR1 = USART_pu8SendData[USART_u8Index] ;


		}
	}
	else if(GET_BIT(USART2->SR,USART_SR_RXNE)== SET)
	{
		/*Receive next Data*/
		USART_pu8ReceiveData[USART_u8Index] = USART2->DR ;

		/*Increment Data index of the buffer*/
		USART_u8Index++ ;

		if (USART_u8Index == USART_u8BufferSize)
		{
			/*Send Data Complete*/

			USART_u8Index=0;
			/*USART is now IDLE*/
			USART_u8State = IDLE ;

			/*Call Notification Function*/
			USART_pvNotificationFunc() ;

			/*USART Recieve Interrupt Disable*/
			CLR_BIT(USART2->CR1,USART_CR1_RXNEIE) ;
		}
		else
		{
			/*Do Noting*/
		}

	}

}

void USART6_IRQHandler(void)
{
	if(GET_BIT(USART6->SR,USART_SR_TXE)== SET)
	{
		/*Increment Data index of the buffer*/
		USART_u8Index++ ;

		if (USART_pu8SendData[USART_u8Index] == '\0')
		{
			/*Receive Data Complete*/
			USART_u8Index=0;

			/*USART is now IDLE*/
			USART_u8State = IDLE ;

			/*Call Notification Function*/
			USART_pvNotificationFunc() ;

			/*USART Transmit Interrupt Disable*/
			CLR_BIT(USART6->CR1,USART_CR1_TXEIE);

		}
		else
		{
			/*Send Data not Complete*/
			/*Send next Data*/
			USART6->CR1 = USART_pu8SendData[USART_u8Index] ;


		}
	}
	else if(GET_BIT(USART6->SR,USART_SR_RXNE)== SET)
	{
		/*Receive next Data*/
		USART_pu8ReceiveData[USART_u8Index] = USART6->DR ;

		/*Increment Data index of the buffer*/
		USART_u8Index++ ;

		if (USART_u8Index == USART_u8BufferSize)
		{
			/*Send Data Complete*/

			USART_u8Index=0;
			/*USART is now IDLE*/
			USART_u8State = IDLE ;

			/*Call Notification Function*/
			USART_pvNotificationFunc() ;

			/*USART Recieve Interrupt Disable*/
			CLR_BIT(USART6->CR1,USART_CR1_RXNEIE) ;
		}
		else
		{
			/*Do Noting*/
		}

	}

}
