/************************************************************************************************/
/*										FILE INCLUSION											*/
/************************************************************************************************/
/***********************LIB*************************/
#include "../include/LIB/Std_Types.h"
#include "../include/LIB/BIT_Math.h"
#include "../include/MCAL/MGPIO/MGPIO_Interface.h"
#include "../include/MCAL/MSPI/MSPI_Interface.h"
#include "../include/MCAL/MSYSTICK/MSYSTICK_Interface.h"
/****************************HAL***************************/
#include "../include/HAL/HTFT/HTFT_Config.h"
#include "../include/HAL/HTFT/HTFT_Interface.h"
#include "../include/HAL/HTFT/HTFT_Private.h"


/************************************************************************/
/*						   FUNCTIONS DEFINITIONS						*/
/************************************************************************/
static void HTFT_voidSPIInit (void)
{
	MGPIO_voidSetPinMode(SPI_PORT,SDK_PIN,GPIO_ALT_FUNC);
	MGPIO_voidSetPinAlternateFunctionMode(SPI_PORT,SDK_PIN,GPIO_SPI1_AF);

	MGPIO_voidSetPinMode(SPI_PORT,SCK_PIN,GPIO_ALT_FUNC);
	MGPIO_voidSetPinAlternateFunctionMode(SPI_PORT,SCK_PIN,GPIO_SPI1_AF);

	MGPIO_voidSetPinMode(SPI_PORT,NSS_PIN,GPIO_ALT_FUNC);
	MGPIO_voidSetPinAlternateFunctionMode(SPI_PORT,NSS_PIN,GPIO_SPI1_AF);

	MSPI_VoidInit();
}

static void HTFT_voidPinInit (void)
{
		MGPIO_voidSetPinMode(TFT_PORT,A0_PIN,GPIO_OUTPUT);
		MGPIO_voidSetPinOutputMode(TFT_PORT,A0_PIN,GPIO_PUSH_PULL,GPIO_MEDIUM_SPEED);
		MGPIO_voidSetPinMode(TFT_PORT,RST_PIN,GPIO_OUTPUT);
		MGPIO_voidSetPinOutputMode(TFT_PORT,RST_PIN,GPIO_PUSH_PULL,GPIO_MEDIUM_SPEED);
}

static void HTFT_voidSendCommand (u8 copy_u8Cmd)
{
	u8 Local_pu8Dummy=0;
	MGPIO_voidSetPinValue(TFT_PORT,A0_PIN,GPIO_PIN_LOW);
	MSPI_voidTranceive(copy_u8Cmd,&Local_pu8Dummy);
}

static void HTFT_voidSendData(u8 copy_u8Data)
{
	u8 Local_pu8Dummy=0;
	MGPIO_voidSetPinValue(TFT_PORT,A0_PIN,GPIO_PIN_HIGH);
	MSPI_voidTranceive(copy_u8Data,&Local_pu8Dummy);
}

static void HTFT_voidSendResetSequence(void)
{
	MGPIO_voidSetPinValue(TFT_PORT,RST_PIN,GPIO_PIN_HIGH);
	MSYSTICK_voidSetBusyWait_us(100);
	MGPIO_voidSetPinValue(TFT_PORT,RST_PIN,GPIO_PIN_LOW);
	MSYSTICK_voidSetBusyWait_us(1);

	MGPIO_voidSetPinValue(TFT_PORT,RST_PIN,GPIO_PIN_HIGH);
	MSYSTICK_voidSetBusyWait_us(100);
	MGPIO_voidSetPinValue(TFT_PORT,RST_PIN,GPIO_PIN_LOW);
	MSYSTICK_voidSetBusyWait_us(100);

	MGPIO_voidSetPinValue(TFT_PORT,RST_PIN,GPIO_PIN_HIGH);
	MSYSTICK_voidSetBusyWait_ms(120);
}

void HTFT_voidInit(void)
{
	HTFT_voidPinInit();
	//Initialise SPI
	HTFT_voidSPIInit();

	//Do Reset Sequence
	HTFT_voidSendResetSequence();

	/*Colour Selection*/
	HTFT_voidSendCommand(Pixel_Format_Set);
	HTFT_voidSendData(0x55);

	//Sleep Out mode
	HTFT_voidSendCommand(Sleep_Out);
	MSYSTICK_voidSetBusyWait_ms(10);

	//Enter Display On Mode
	HTFT_voidSendCommand(Display_ON);
}

void HTFT_voidDisplayImg(u8 copy_u8LeftPad,u8 copy_u8RightPad,u8 copy_u8TopPad,u8 copy_u8BottomPad,const u16  *copy_pu16Data)
{
	u16 Local_u8Counter;
	u8 Local_u8LowByte,Local_u8HighByte;
	/*Set X-Axis Range*/
	HTFT_voidSendCommand(Column_Address_Set);
	HTFT_voidSendData(0);
	HTFT_voidSendData(X_AXIS_INIT+copy_u8LeftPad);
	HTFT_voidSendData(0);
	HTFT_voidSendData(X_AXIS_END-copy_u8RightPad);

	/*Set Y-Axis Range*/
	HTFT_voidSendCommand(Row_Address_Set);
	HTFT_voidSendData(0);
	HTFT_voidSendData(Y_AXIS_INIT+copy_u8BottomPad);
	HTFT_voidSendData(0);
	HTFT_voidSendData(Y_AXIS_END-copy_u8TopPad);

	/*Set RAM Address*/
	HTFT_voidSendCommand(Memory_Write);
	for(Local_u8Counter=0;Local_u8Counter<PIXELS_MAX_NO;Local_u8Counter++)
	{
		Local_u8LowByte = (u8) copy_pu16Data[Local_u8Counter];
		Local_u8HighByte = (u8) (copy_pu16Data[Local_u8Counter] >> 8);
		HTFT_voidSendData(Local_u8HighByte);
		HTFT_voidSendData(Local_u8LowByte);
	}
}

void HTFT_voidDisplayImgSetConfiguration_DMA(u8 copy_u8LeftPad,u8 copy_u8RightPad,u8 copy_u8TopPad,u8 copy_u8BottomPad)
{
	/*Set X-Axis Range*/
	HTFT_voidSendCommand(Column_Address_Set);
	HTFT_voidSendData(0);
	HTFT_voidSendData(X_AXIS_INIT+copy_u8LeftPad);
	HTFT_voidSendData(0);
	HTFT_voidSendData(X_AXIS_END-copy_u8RightPad);

	/*Set Y-Axis Range*/
	HTFT_voidSendCommand(Row_Address_Set);
	HTFT_voidSendData(0);
	HTFT_voidSendData(Y_AXIS_INIT+copy_u8BottomPad);
	HTFT_voidSendData(0);
	HTFT_voidSendData(Y_AXIS_END-copy_u8TopPad);

	/*Set RAM Address*/
	HTFT_voidSendCommand(Memory_Write);
}
