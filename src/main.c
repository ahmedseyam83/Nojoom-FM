/************************************************************************************************/
/*										FILE INCLUSION											*/
/************************************************************************************************/

/***********************LIB*************************/
#include "../include/LIB/Std_Types.h"
#include "../include/LIB/BIT_MATH.h"

/************************MCAL***********************/
#include "../include/MCAL/MRCC/MRCC_Interface.h"
#include "../include/MCAL/MNVIC/MNVIC_Interface.h"
#include "../include/MCAL/MGPIO/MGPIO_Interface.h"
#include "../include/MCAL/MSYSTICK/MSYSTICK_Interface.h"

/************************HAL************************/
#include "../include/HAL/HIR/HIR_Interface.h"
#include "../include/HAL/HDAC/HDAC_Interface.h"
#include "../include/HAL/HDAC/HDAC_SoundFile.h"
#include "../include/HAL/HS2P/HS2P_Interface.h"
#include "../include/HAL/HTFT/HTFT_Interface.h"
#include "../include/HAL/HTFT/HTFT_Image.h"
/**********************MACROS************************/

/*HIR MACROS*/
#define FIRST_CHANNEL		68
#define SECOND_CHANNEL		64
#define POWER_BUTTON		69
#define PLAY_BUTTON			82
#define NEXT_BUTTON			66
#define PAST_BUTTON			74

/*LED MATRIX MACROS*/
#define SINGER_MAX_NO		2
#define INDEX_MAX_NO		64
#define DISABLE_COLUMNS		0xFF

/*DAC MACROS*/
#define AMR_DIAB_MAX_INDEX	40488
#define FAYROUZ_MAX_INDEX	44066



/********************Global Variables****************/
/*Variable*/

u8 Global_u8Channel=0;

u8 SINGERS_NAMES[2][INDEX_MAX_NO]=
{
		{/*AMR DIAB*/
				255, 9, 9, 9, 9, 9, 9, 255, 			//A
				255, 1, 2, 4, 4, 2, 1, 255, 			//M
				255, 9, 25, 41, 73, 137, 9, 15, 		//R
				255, 129, 129, 129, 129, 129, 66, 60, 	//D
				129, 129, 129, 255, 255, 129, 129, 129, //I
				255, 9, 9, 9, 9, 9, 9, 255,				//A
				255, 137, 137, 137, 137, 137, 137, 126,	//B
				0,0,0,0
		},
		{ /*FAYROUZ*/
				255, 9, 9, 9, 9, 1, 1, 1,				//F
				255, 9, 9, 9, 9, 9, 9, 255,				//A
				1, 2, 4, 248, 248, 4, 2, 1,				//Y
				255, 9, 25, 41, 73, 137, 9, 15,			//R
				255, 129, 129, 129, 129, 129, 129, 255,	//O
				255, 128, 128, 128, 128, 128, 128, 255,	//U
				129, 193, 161, 145, 137, 133, 131, 129,	//Z
				0,0,0,0
		},
};



/************************************************************************/
/*							FUNCTIONS DECLARATION						*/
/************************************************************************/
void PLAY_PAUSE_MODE(void);
void PWR_ON_MODE(void);
void CHANNEL_1_MODE(void);
void CHANNEL_2_MODE(void);
/************************************************************************/
/*							ENTRY POINT <main>							*/
/************************************************************************/
void main(void)
{
	/***********************Local Variable*************************/
	u8 Local_HIRRead=0;
	/***********************Clock initialisation*************************/
	/* Enable RCC */
	MRCC_voidInit();

	/* Clocks to usage Peripherals Enable (use RCC) */
	MRCC_voidEnablePeripheral(RCC_APB2,RCC_APB2_SPI1);
	MRCC_voidEnablePeripheral(RCC_APB2,RCC_APB2_SYSCFG);
	MRCC_voidEnablePeripheral(RCC_AHB1,RCC_AHB1_GPIOA);
	MRCC_voidEnablePeripheral(RCC_AHB1,RCC_AHB1_GPIOB);

	/**********************Pins initialisation**************************/
	/**********************Peripherals initialisation**************************/
	MSYSTICK_voidInit();
	HTFT_voidInit();
	HDAC_voidInit();
//	HS2P2_voidInit();
//	HS2P_voidInit();
	HIR_voidInit();
	/**********************Operation Code*****************************/


	while(1)
	{
		HIR_u8GetValue(&Local_HIRRead);

		switch(Local_HIRRead){
		case POWER_BUTTON:
			PWR_ON_MODE();
			Local_HIRRead=0;
			Global_u8Channel=0;
			break;
		case FIRST_CHANNEL:
			CHANNEL_1_MODE();
			Local_HIRRead=0;
			Global_u8Channel=1;
			break;
		case SECOND_CHANNEL:
			CHANNEL_2_MODE();
			Local_HIRRead=0;
			Global_u8Channel=2;
			break;
		case NEXT_BUTTON:
			if(Global_u8Channel==1)
			{
				CHANNEL_2_MODE();
				Global_u8Channel=2;
			}
			else if(Global_u8Channel==2)
			{
				CHANNEL_1_MODE();
				Global_u8Channel=1;
			}
			break;
		case PAST_BUTTON:
			if(Global_u8Channel==1)
			{
				CHANNEL_2_MODE();
				Global_u8Channel=2;
			}
			else if(Global_u8Channel==2)
			{
				CHANNEL_1_MODE();
				Global_u8Channel=1;
			}
			break;
		case PLAY_BUTTON:
			PLAY_PAUSE_MODE();
			break;
		}

	}
}

void PWR_ON_MODE(void)
{
	/*Display Nojoom Image on TFT*/
	HTFT_voidDisplayImg(0,0,0,0,Nojoom);
}

void PLAY_PAUSE_MODE(void)
{
	static u8 Local_u8PLAY=0;
	if(Local_u8PLAY == 1)
	{
		if(Global_u8Channel==1)
		{
			CHANNEL_1_MODE();
		}
		else if(Global_u8Channel==2)
		{
			CHANNEL_2_MODE();
		}
		Local_u8PLAY=0;
	}
	else if(Local_u8PLAY == 0)
	{
		if(Global_u8Channel==1)
		{
			/*Display Amr Diab Image on TFT*/
			HTFT_voidDisplayImg(0,0,0,0,AMR_DIAB_IMG);

		}
		else if(Global_u8Channel==2)
		{
			/*Display Fayrouz Image on TFT*/
			HTFT_voidDisplayImg(0,0,0,0,FAYROUZ_IMG);

		}
		Local_u8PLAY=1;
	}



}

void CHANNEL_1_MODE(void)
{
	u8 Local_u8MotionCounter,Local_u8Counter,Local_u8LettersCounter;

	/*Display Amr Diab Image on TFT*/
	HTFT_voidDisplayImg(0,0,0,0,AMR_DIAB_IMG);

	for(Local_u8MotionCounter=0;Local_u8MotionCounter<INDEX_MAX_NO;Local_u8MotionCounter++)
		{
			/* Delay for LED Matrix Display */
			for(Local_u8Counter=0;Local_u8Counter<15;Local_u8Counter++)
			{
				/*Display values of array*/
				for (Local_u8LettersCounter=0;Local_u8LettersCounter<8;Local_u8LettersCounter++)
				{
					/* DISABLE LED Matrix Columns Through Serial-To-Parallel */
					HS2P2_voidSendByte(DISABLE_COLUMNS);

					/* Set LEDMatrix Rows value Through Serial-To-Parallel */
					HS2P_voidSendByte(SINGERS_NAMES[0][Local_u8LettersCounter+Local_u8MotionCounter]);

					/* Set Column to zero */
					HS2P2_voidSendByte(~(1<<Local_u8LettersCounter));

				}
			}
		}

	/*Set Sound Track to played*/
	HDAC_voidSet(AMR_DIAB_SONG,AMR_DIAB_MAX_INDEX);

	/*Start Playing*/
	HDAC_voidStart();

	/*Loop For Motion View Display*/




}

void CHANNEL_2_MODE(void)
{
	u8 Local_u8MotionCounter,Local_u8Counter,Local_u8LettersCounter;

	/*Display Fayrouz Image on TFT*/
	HTFT_voidDisplayImg(0,0,0,0,FAYROUZ_IMG);

	for(Local_u8MotionCounter=0;Local_u8MotionCounter<INDEX_MAX_NO;Local_u8MotionCounter++)
	{
		/* Delay for LED Matrix Display */
		for(Local_u8Counter=0;Local_u8Counter<15;Local_u8Counter++)
		{
			/*Display values of array*/
			for (Local_u8LettersCounter=0;Local_u8LettersCounter<8;Local_u8LettersCounter++)
			{
				/* DISABLE LED Matrix Columns Through Serial-To-Parallel */
				HS2P2_voidSendByte(DISABLE_COLUMNS);

				/* Set LEDMatrix Rows value Through Serial-To-Parallel */
				HS2P_voidSendByte(SINGERS_NAMES[1][Local_u8LettersCounter+Local_u8MotionCounter]);

				/* Set Column to zero */
				HS2P2_voidSendByte(~(1<<Local_u8LettersCounter));

			}
		}
	}

	/*Set Sound Track to played*/
	HDAC_voidSet(FAYROUZ_SONG_NAME,FAYROUZ_MAX_INDEX);
	/*Start Playing*/
	HDAC_voidStart();



}


