/*
 * HTFT_Private.h
 *
 *  Created on: 14 May 2024
 *      Author: User
 */

#ifndef HTFT_PRIVATE_H_
#define HTFT_PRIVATE_H_




/*************************Private Macros*********************************/
#define Power_Control_1 			0xC0
#define Power_Control_2 			0xC1
#define VCOM_Control_1				0xC5
#define VCOM_Control_2 				0xC7
#define Memory_Access_Control 		0x36
#define Pixel_Format_Set 			0x3A
#define Frame_Rate_Control 			0xB1
#define Display_Function_Control 	0xB6
#define Column_Address_Set 			0x2A
#define Row_Address_Set 			0x2B
#define Gamma_Set 					0x26
#define Positive_Gamma_Correction 	0xE0
#define Negative_Gamma_Correction 	0xE1
#define Sleep_Out 					0x11
#define Display_ON 					0x29
#define Memory_Write 				0x2C




/**********************************************************/
#define SPI1_ENABLE 							1
#define SPI2_ENABLE 							2
#define SPI3_ENABLE 							3


#if SPI_ENABLE_SELECT == SPI1_ENABLE
#define SPI_PORT		GPIO_PORTA
#define SDK_PIN			GPIO_PIN7
#define SCK_PIN			GPIO_PIN5
#define NSS_PIN			GPIO_PIN4
#elif SPI_ENABLE_SELECT == SPI2_ENABLE
#define SPI_PORT		GPIO_PORTB
#define SDK_PIN			GPIO_PIN15
#define SCK_PIN			GPIO_PIN13
#define NSS_PIN			GPIO_PIN12
#endif



#endif /* HTFT_PRIVATE_H_ */
