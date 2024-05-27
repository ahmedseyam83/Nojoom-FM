
/*										FILE INCLUSION											*/
/************************************************************************************************/
/***********************LIB*************************/
#include "../include/LIB/Std_Types.h"
#include "../include/LIB/BIT_Math.h"
#include "../include/MCAL/MSPI/MSPI_Config.h"
#include "../include/MCAL/MSPI/MSPI_Interface.h"
#include "../include/MCAL/MSPI/MSPI_Private.h"


/***********************Global Variable*************************/
/*Global variable to carry the Transmit Data*/
static u8 * SPI_pu8TData = NULL ;

/*Global variable to carry the Receive Data*/
static u8 * SPI_pu8RData = NULL ;

/*Global variable to carry the buffer size*/
static u8 SPI_u8BufferSize;

/*Global variable to indicate for the current Data index of the buffer*/
static u8 SPI_u8Index;

/*Global pointer to function to carry the notification function called by ISR*/
static void (* SPI_pvNotificationFunc)(void)= NULL;

/*Global flag for the SPI Busy State*/
static u8 SPI_u8State= IDLE ;



/************************************************************************/
/*						   FUNCTIONS DEFINITIONS						*/
/************************************************************************/
void MSPI_VoidInit(void){

	u32 Local_u32CR1_Temp=0, Local_u32CR2_Temp=0;


	/*Data Frame Format*/
#if SPI_DATA_SIZE == SPI_DATA_8_BIT
	CLR_BIT(Local_u32CR1_Temp,SPI_CR1_DFF) ;
#elif SPI_DATA_SIZE == SPI_DATA_16_BIT
	SET_BIT(Local_u32CR1_Temp, SPI_CR1_DFF) ;
#else
#error "wrong SPI_DATA_ORDER config"
#endif

	/*Data LSB/MSB*/
#if SPI_DATA_ORDER == SPI_DATA_LSB_FIRST
	SET_BIT(Local_u32CR1_Temp,SPI_CR1_LSB) ;
#elif SPI_DATA_ORDER == SPI_DATA_MSP_FIRST
	CLR_BIT(Local_u32CR1_Temp,SPI_CR1_LSB) ;
#else
#error "wrong SPI_DATA_ORDER config"
#endif

	/*Clock Polarity*/
#if SPI_CLOCK_POLARITY == SPI_RISING_LEADING_FALLING_TRAILING
	CLR_BIT(Local_u32CR1_Temp,SPI_CR1_CPOL) ;
#elif SPI_CLOCK_POLARITY == SPI_FALLING_LEADING_RISING_TRAILING
	SET_BIT(Local_u32CR1_Temp,SPI_CR1_CPOL) ;
#else
#error "wrong SPI_CLOCK_POLARITY config"
#endif

	/*Clock Phase*/
#if SPI_CLOCK_PHASE == SPI_SAMPLE_LEADING_SETUP_TRAILING
	CLR_BIT(Local_u32CR1_Temp ,SPI_CR1_CPHA) ;
#elif SPI_CLOCK_PHASE == SPI_SETUP_LEADING_SAMPLE_TRAILING
	SET_BIT(Local_u32CR1_Temp , SPI_CR1_CPHA) ;
#else
#error "wrong SPI_CLOCK_PHASE config"
#endif


	/*Master/Slave Select*/
#if SPI_MASTER_SLAVE_SELECT == SPI_MASTER
	SET_BIT(Local_u32CR1_Temp, SPI_CR1_MSTR) ;
#if SPI_MASTER_MODE_SELECT == SPI_MODE_FULL_DUPLEX
	CLR_BIT(Local_u32CR1_Temp, SPI_CR1_BIDI_MODE);
	CLR_BIT(Local_u32CR1_Temp, SPI_CR1_RX_ONLY);
#elif SPI_MASTER_MODE_SELECT == SPI_MODE_HALF_DUPLEX_RX
	SET_BIT(Local_u32CR1_Temp, SPI_CR1_BIDI_MODE);
	CLR_BIT(Local_u32CR1_Temp, SPI_CR1_BIDI_OE);
#elif SPI_MASTER_MODE_SELECT == SPI_MODE_HALF_DUPLEX_TX
	SET_BIT(Local_u32CR1_Temp, SPI_CR1_BIDI_MODE);
	SET_BIT(Local_u32CR1_Temp, SPI_CR1_BIDI_OE);
#elif SPI_MASTER_MODE_SELECT == SPI_MODE_SIMPLEX_RX
	CLR_BIT(Local_u32CR1_Temp, SPI_CR1_BIDI_MODE);
	SET_BIT(Local_u32CR1_Temp, SPI_CR1_RX_ONLY);
#else
#error "wrong SPI_MASTER_MODE_SELECT config"
#endif

#if SPI_SOFTWARE_SLAVE_MANAGEMENT == SPI_SSM_DISABLED
	CLR_BIT(Local_u32CR1_Temp, SPI_CR1_SSM);
#elif SPI_SOFTWARE_SLAVE_MANAGEMENT == SPI_SSM_ENABLED
	SET_BIT(Local_u32CR1_Temp, SPI_CR1_SSM);
	SET_BIT(Local_u32CR1_Temp, SPI_CR1_SSI);
#else
#error "wrong SPI_SOFTWARE_SLAVE_MANAGEMENT config"
#endif

	/*Clock Rate*/
	Local_u32CR1_Temp &= ~(THREE_BIT_MASK<<SPI_CR1_BR);
	Local_u32CR1_Temp |= SPI_CLOCK_RATE<<SPI_CR1_BR;

#if SPI_MASTER_SS_PIN_MODE == SPI_SS_OUTPUT_MULTIMASTER_DISABLED
	SET_BIT(Local_u32CR2_Temp,SPI_CR2_SSOE);
#elif SPI_MASTER_SS_PIN_MODE == SPI_SS_INPUT_MULTIMASTER_ENABLED
	CLR_BIT(Local_u32CR2_Temp,SPI_CR2_SSOE);
#else
#error "wrong SPI_MASTER_SS_PIN_MODE config"
#endif

#elif SPI_MASTER_SLAVE_SELECT == SPI_SLAVE
	CLR_BIT(Local_u32CR1_Temp, SPI_CR1_MSTR) ;

#if SPI_SOFTWARE_SLAVE_MANAGEMENT == SPI_SSM_DISABLED
	CLR_BIT(Local_u32CR1_Temp, SPI_CR1_SSM);
#elif SPI_SOFTWARE_SLAVE_MANAGEMENT == SPI_SSM_ENABLED
	SET_BIT(Local_u32CR1_Temp, SPI_CR1_SSM);
	CLR_BIT(Local_u32CR1_Temp, SPI_CR1_SSI);
#else
#error "wrong SPI_SOFTWARE_SLAVE_MANAGEMENT config"
#endif

#else
#error "wrong SPI_MASTER_SLAVE_SELECT config"
#endif

	/*SPI TXE Interrupt Enable*/
#if SPI_TXE_INTERRUPT_ENABLE_MODE == SPI_TXE_INTERRUPT_DISABLE
	CLR_BIT(Local_u32CR2_Temp,SPI_CR2_TXEIE) ;
#elif SPI_TXE_INTERRUPT_ENABLE_MODE == SPI_TXE_INTERRUPT_ENABLE
	SET_BIT(Local_u32CR2_Temp,SPI_CR2_TXEIE) ;
#else
#error "wrong SPI_TX_INTERRUPT_ENABLE_MODE config"
#endif

	/*SPI RXNE Interrupt Enable*/
#if SPI_RXNE_INTERRUPT_ENABLE_MODE == SPI_RXNE_INTERRUPT_DISABLE
	CLR_BIT(Local_u32CR2_Temp,SPI_CR2_RXNEIE) ;
#elif SPI_RXNE_INTERRUPT_ENABLE_MODE == SPI_RXNE_INTERRUPT_ENABLE
	SET_BIT(Local_u32CR2_Temp,SPI_CR2_RXNEIE) ;
#else
#error "wrong SPI_TX_INTERRUPT_ENABLE_MODE config"
#endif

	/*SPI Enable*/


#if SPI_ENABLE_SELECT == SPI1_ENABLE
	SPI1->CR2 = Local_u32CR2_Temp;
	SPI1->CR1 = Local_u32CR1_Temp;
	#if SPI_ENABLE_MODE == SPI_DISABLE
		CLR_BIT(SPI1->CR1 ,SPI_CR1_SPE) ;
	#elif SPI_ENABLE_MODE == SPI_ENABLE
		SET_BIT(SPI1->CR1 ,SPI_CR1_SPE) ;
	#else
	#error "wrong SPI_ENABLE_MODE config"
	#endif

#elif SPI_ENABLE_SELECT == SPI2_ENABLE
	SPI2->CR2 = Local_u32CR2_Temp;
	SPI2->CR1 = Local_u32CR1_Temp;
	#if SPI_ENABLE_MODE == SPI_DISABLE
		CLR_BIT(SPI2->CR1 ,SPI_CR1_SPE) ;
	#elif SPI_ENABLE_MODE == SPI_ENABLE
		SET_BIT(SPI2->CR1 ,SPI_CR1_SPE) ;
	#else
	#error "wrong SPI_ENABLE_MODE config"
	#endif

#elif SPI_ENABLE_SELECT == SPI3_ENABLE
	SPI3->CR2 = Local_u32CR2_Temp;
	SPI3->CR1 = Local_u32CR1_Temp;
	#if SPI_ENABLE_MODE == SPI_DISABLE
		CLR_BIT(SPI3->CR1 ,SPI_CR1_SPE) ;
	#elif SPI_ENABLE_MODE == SPI_ENABLE
		SET_BIT(SPI3->CR1 ,SPI_CR1_SPE) ;
	#else
	#error "wrong SPI_ENABLE_MODE config"
	#endif
#else
#error "wrong SPI_ENABLE_SELECT config"
#endif
}


void MSPI_voidTranceive (u8 Copy_u8TransmitData , u8 * Copy_u8ReceiveData)
{
	if (SPI_u8State == IDLE)
	{
		SPI_u8State = BUSY;
	#if SPI_ENABLE_SELECT == SPI1_ENABLE
		//Wait till TX is set
		while(GET_BIT(SPI1->SR,SPI_SR_TXE) == 0);
		SPI1->DR = Copy_u8TransmitData ;
		//Wait till RXNE is set
		while(GET_BIT(SPI1->SR,SPI_SR_RXNE) == 0);
		* Copy_u8ReceiveData = SPI1->DR ;
	#elif SPI_ENABLE_SELECT == SPI2_ENABLE
		SPI2->DR = Copy_u8TransmitData ;
		while (((GET_BIT(SPI2->SR , SPI_SR_BSY)) == 1) && (Local_uint32TimeoutCounter < SPI_uint32TIMEOUT))
		{
			Local_uint32TimeoutCounter++ ;
		}
		* Copy_u8ReceiveData = SPI2->DR ;
	#elif SPI_ENABLE_SELECT == SPI3_ENABLE
		SPI3->DR = Copy_u8TransmitData ;
		while (((GET_BIT(SPI3->SR , SPI_SR_BSY)) == 1) && (Local_uint32TimeoutCounter < SPI_uint32TIMEOUT))
		{
			Local_uint32TimeoutCounter++ ;
		}
		* Copy_u8ReceiveData = SPI3->DR ;
	#else
	#error "wrong SPI_ENABLE_SELECT config"
	#endif

		SPI_u8State = IDLE ;
	}
}

void SPI_u8BufferTranceiverSynch (u8 * Copy_u8TData , u8 * Copy_u8RData , u8 Copy_u8BufferSize)
{

	u8 Local_u8Counter = 0 ;
	if ((Copy_u8TData != NULL) && (Copy_u8RData != NULL))
	{
		while (Local_u8Counter < Copy_u8BufferSize)
		{
			MSPI_voidTranceive(Copy_u8TData[Local_u8Counter] , &Copy_u8RData[Local_u8Counter]) ;
			Local_u8Counter++ ;
		}
	}
}


void SPI_u8BufferTranceiverAsynch (u8 * Copy_u8TData , u8 * Copy_u8RData, u8 Copy_u8BufferSize)
{
	if (SPI_u8State == IDLE)
	{
		if ( (Copy_u8TData != NULL) && ( Copy_u8RData != NULL))
		{
			/*SPI is now Busy*/
			SPI_u8State = BUSY ;

			/*Assign the SPI data globally*/
			SPI_pu8TData = Copy_u8TData ;
			SPI_pu8RData = Copy_u8RData ;
			SPI_u8BufferSize = Copy_u8BufferSize ;

			/*Set Index to first element*/
			SPI_u8Index = 0 ;

			/*Transmit first Data */

			#if SPI_ENABLE_SELECT == SPI1_ENABLE
				SPI1->DR = SPI_pu8TData[SPI_u8Index] ;
				/*SPI Interrupt Enable*/
				SET_BIT(SPI1->CR2,SPI_CR2_TXEIE) ;
			#elif SPI_ENABLE_SELECT == SPI2_ENABLE
				SPI2->DR = SPI_pu8TData[SPI_u8Index] ;
				SET_BIT(SPI2->CR2,SPI_CR2_TXEIE) ;
			#elif SPI_ENABLE_SELECT == SPI3_ENABLE
				SPI3->DR = SPI_pu8TData[SPI_u8Index] ;
				SET_BIT(SPI3->CR2,SPI_CR2_TXEIE) ;
			#else
			#error "wrong SPI_ENABLE_SELECT config"
			#endif
		}
	}
}



/**************************************************************************************************/

void SPI1_IRQHandler(void)
{
	/*Receive Data*/
	SPI_pu8RData[SPI_u8Index] = SPI1->DR ;

	/*Increment Data index of the buffer*/
	SPI_u8Index++ ;

	if (SPI_u8Index == SPI_u8BufferSize)
	{
		/*Buffer Complete*/

		/*SPI is now IDLE*/
		SPI_u8State = IDLE ;

		/*SPI Interrupt Disable*/
		CLR_BIT(SPI1->CR2,SPI_CR2_TXEIE) ;

		/*Call Notification Function*/
		SPI_pvNotificationFunc() ;
	}
	else
	{
		/*Buffer not Complete*/

		/*Transmit next Data*/
		SPI1->DR  = SPI_pu8TData[SPI_u8Index] ;
	}
}

void SPI2_IRQHandler(void)
{
	/*Receive Data*/
	SPI_pu8RData[SPI_u8Index] = SPI2->DR ;

	/*Increment Data index of the buffer*/
	SPI_u8Index++ ;

	if (SPI_u8Index == SPI_u8BufferSize)
	{
		/*Buffer Complete*/

		/*SPI is now IDLE*/
		SPI_u8State = IDLE ;

		/*SPI Interrupt Disable*/
		CLR_BIT(SPI2->CR2,SPI_CR2_TXEIE) ;

		/*Call Notification Function*/
		SPI_pvNotificationFunc() ;
	}
	else
	{
		/*Buffer not Complete*/

		/*Transmit next Data*/
		SPI2->DR  = SPI_pu8TData[SPI_u8Index] ;
	}
}

void SPI3_IRQHandler(void)
{
	/*Receive Data*/
	SPI_pu8RData[SPI_u8Index] = SPI3->DR ;

	/*Increment Data index of the buffer*/
	SPI_u8Index++ ;

	if (SPI_u8Index == SPI_u8BufferSize)
	{
		/*Buffer Complete*/

		/*SPI is now IDLE*/
		SPI_u8State = IDLE ;

		/*SPI Interrupt Disable*/
		CLR_BIT(SPI3->CR2,SPI_CR2_TXEIE) ;

		/*Call Notification Function*/
		SPI_pvNotificationFunc() ;
	}
	else
	{
		/*Buffer not Complete*/

		/*Transmit next Data*/
		SPI3->DR  = SPI_pu8TData[SPI_u8Index] ;
	}
}
