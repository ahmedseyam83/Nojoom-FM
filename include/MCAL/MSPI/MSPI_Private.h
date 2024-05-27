/*
 * MSPI_Private.h
 *
 *  Created on: 3 May 2024
 *      Author: User
 */

#ifndef MSPI_PRIVATE_H_
#define MSPI_PRIVATE_H_

/****************************************************************************/
/*						PERIPHERALS BASE ADDRESS							*/
/****************************************************************************/
#define SPI1_BASE_ADDRESS 	0x40013000
#define SPI2_BASE_ADDRESS	0x40013400
#define SPI3_BASE_ADDRESS	0x40003C00



/****************************************************************************/
/*						REGISTERS STRUCTURE									*/
/****************************************************************************/
typedef struct
{
	u32 CR1;
	u32 CR2;
	u32 SR;
	u32 DR;
	u32 CRCPR;
	u32 RXCRCR;
	u32 TXCRCR;
	u32 I2SCFGR;
	u32 I2SPR;
}SPI_t;


#define SPI1	((volatile SPI_t*) SPI1_BASE_ADDRESS)
#define SPI2	((volatile SPI_t*) SPI2_BASE_ADDRESS)
#define SPI3	((volatile SPI_t*) SPI3_BASE_ADDRESS)



/********************REGISTERS BITS*****************************/

/* SPI_CR1 */
#define SPI_CR1_CPHA		0
#define SPI_CR1_CPOL		1
#define SPI_CR1_MSTR		2
#define SPI_CR1_BR			3
#define SPI_CR1_BR0			3
#define SPI_CR1_BR1			4
#define SPI_CR1_BR2			5
#define SPI_CR1_SPE			6
#define SPI_CR1_LSB			7
#define SPI_CR1_SSI			8
#define SPI_CR1_SSM			9
#define SPI_CR1_RX_ONLY		10
#define SPI_CR1_DFF			11
#define SPI_CR1_CRC_NEXT	12
#define SPI_CR1_CRC_EN		13
#define SPI_CR1_BIDI_OE		14
#define SPI_CR1_BIDI_MODE	15

/* SPI_CR2 */
#define SPI_CR2_RXDMAEN		0
#define SPI_CR2_TXDMAEN		1
#define SPI_CR2_SSOE		2
#define SPI_CR2_FRF			4
#define SPI_CR2_ERRIE		5
#define SPI_CR2_RXNEIE		6
#define SPI_CR2_TXEIE		7

/* SPI_SR */
#define SPI_SR_RXNE			0
#define SPI_SR_TXE			1
#define SPI_SR_CHSIDE		2
#define SPI_SR_UDR			3
#define SPI_SR_CRC_ERR		4
#define SPI_SR_MODF			5
#define SPI_SR_OVR			6
#define SPI_SR_BSY			7
#define SPI_SR_FRE			8

/* SPI_I2SCFGR */
#define SPI_I2SCFGR_CHLEN	0
#define SPI_I2SCFGR_DATLEN	1
#define SPI_I2SCFGR_CKPOL	3
#define SPI_I2SCFGR_I2SSTD	4
#define SPI_I2SCFGR_PCMSYNC	7
#define SPI_I2SCFGR_I2SCFG	8
#define SPI_I2SCFGR_I2SE	10
#define SPI_I2SCFGR_I2SMOD	11

/* SPI_I2SPR */
#define SPI_I2SPR_I2SDIV	0
#define SPI_I2SPR_ODD		8
#define SPI_I2SPR_MCKOE		9



/********************PRIVATE MACROS****************************/

/**********************************************************/
#define	SPI_MASTER		1
#define SPI_SLAVE		2
/**********************************************************/
#define SPI_MODE_FULL_DUPLEX 		1
#define SPI_MODE_HALF_DUPLEX_RX	 	2
#define SPI_MODE_HALF_DUPLEX_TX	 	3
#define SPI_MODE_SIMPLEX_RX	 		4
/**********************************************************/
#define SPI_SSM_DISABLED			1
#define SPI_SSM_ENABLED				2
/**********************************************************/
#define SPI_SS_OUTPUT_MULTIMASTER_DISABLED	1
#define SPI_SS_INPUT_MULTIMASTER_ENABLED	2
/**********************************************************/
#define SPI_DATA_8_BIT 						1
#define SPI_DATA_16_BIT 					2
/**********************************************************/
#define SPI_DATA_LSB_FIRST 						1
#define SPI_DATA_MSP_FIRST 						2
/**********************************************************/
#define SPI_FREQ_DIVIDED_BY_2					0
#define SPI_FREQ_DIVIDED_BY_4					1
#define SPI_FREQ_DIVIDED_BY_8					2
#define SPI_FREQ_DIVIDED_BY_16					3
#define SPI_FREQ_DIVIDED_BY_32					4
#define SPI_FREQ_DIVIDED_BY_64					5
#define SPI_FREQ_DIVIDED_BY_128				    6
#define SPI_FREQ_DIVIDED_BY_256				    7
/**********************************************************/
#define SPI_DISABLE								1
#define SPI_ENABLE 								2
/**********************************************************/
#define SPI_TXE_INTERRUPT_DISABLE				1
#define SPI_TXE_INTERRUPT_ENABLE 				2
/**********************************************************/
#define SPI_RXNE_INTERRUPT_DISABLE				1
#define SPI_RXNE_INTERRUPT_ENABLE 				2
/**********************************************************/
#define SPI_RISING_LEADING_FALLING_TRAILING 	1
#define SPI_FALLING_LEADING_RISING_TRAILING		2
/**********************************************************/
#define SPI_SAMPLE_LEADING_SETUP_TRAILING 		1
#define SPI_SETUP_LEADING_SAMPLE_TRAILING		2
/**********************************************************/
#define SPI1_ENABLE 							1
#define SPI2_ENABLE 							2
#define SPI3_ENABLE 							3

#define THREE_BIT_MASK   						0b111


#endif /* MSPI_PRIVATE_H_ */
