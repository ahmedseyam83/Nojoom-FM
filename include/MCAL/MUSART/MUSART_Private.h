/*
 * MUSART_Private.h
 *
 *  Created on: 8 May 2024
 *      Author: User
 */

#ifndef MUSART_PRIVATE_H_
#define MUSART_PRIVATE_H_

/****************************************************************************/
/*						PERIPHERALS BASE ADDRESS							*/
#define USART1_BASE			0x40011000
#define USART2_BASE			0x40004400
#define USART6_BASE			0x40011400


/****************************************************************************/
/*						REGISTERS STRUCTURE									*/
/****************************************************************************/

typedef struct
{
  u32  SR;
  u32  DR;
  u32  BRR;
  u32  CR1;
  u32  CR2;
  u32  CR3;
  u32  GTPR;
} USART_t;


/****************************************************************************/
/*								PERIPHERALS 								*/
/****************************************************************************/
#define USART1              ((volatile USART_t *) USART1_BASE)
#define USART2              ((volatile USART_t *) USART2_BASE)
#define USART6              ((volatile USART_t *) USART6_BASE)

/*******************  Bit definition for USART_SR register  *******************/
#define  USART_SR_PE				0
#define  USART_SR_FE				1
#define  USART_SR_NE				2
#define  USART_SR_ORE				3
#define  USART_SR_IDLE				4
#define  USART_SR_RXNE				5
#define  USART_SR_TC				6
#define  USART_SR_TXE				7
#define  USART_SR_LBD				8
#define  USART_SR_CTS				9

/******************  Bit definition for USART_BRR register  *******************/
#define  USART_BRR_DIV_Fraction		0
#define  USART_BRR_DIV_Mantissa		4

/******************  Bit definition for USART_CR1 register  *******************/
#define  USART_CR1_SBK              0
#define  USART_CR1_RWU              1
#define  USART_CR1_RE               2
#define  USART_CR1_TE               3
#define  USART_CR1_IDLEIE           4
#define  USART_CR1_RXNEIE           5
#define  USART_CR1_TCIE             6
#define  USART_CR1_TXEIE            7
#define  USART_CR1_PEIE             8
#define  USART_CR1_PS               9
#define  USART_CR1_PCE              10
#define  USART_CR1_WAKE             11
#define  USART_CR1_M                12
#define  USART_CR1_UE               13
#define  USART_CR1_OVER8            15


/******************  Bit definition for USART_CR2 register  *******************/
#define  USART_CR2_ADD				0
#define  USART_CR2_LBDL			 	5
#define  USART_CR2_LBDIE			6
#define  USART_CR2_LBCL				8
#define  USART_CR2_CPHA				9
#define  USART_CR2_CPOL				10
#define  USART_CR2_CLKEN			11
#define  USART_CR2_STOP				12
#define  USART_CR2_LINEN			14

/******************  Bit definition for USART_CR3 register  *******************/
#define  USART_CR3_EIE				0
#define  USART_CR3_IREN				1
#define  USART_CR3_IRLP				2
#define  USART_CR3_HDSEL			3
#define  USART_CR3_NACK				4
#define  USART_CR3_SCEN				5
#define  USART_CR3_DMAR				6
#define  USART_CR3_DMAT				7
#define  USART_CR3_RTSE				8
#define  USART_CR3_CTSE				9
#define  USART_CR3_CTSIE			10
#define  USART_CR3_ONEBIT			11

/******************  Bit definition for USART_GTPR register  ******************/
#define  USART_GTPR_PSC				0
#define  USART_GTPR_GT				8


/****************************************************************************/
/*						       PRIVATE MACROS								*/
/****************************************************************************/

#define DISABLE				                    1
#define ENABLE				                    2

#define USART1_ENABLE 			                1
#define USART2_ENABLE 			                2
#define USART6_ENABLE							3

#define ASYNCHRONOUS		                    1
#define SYNCHRONOUS 		                    2

#define EVEN_PARITY			                    1
#define ODD_PARITY 			                    2

#define STOP_BIT_1			                    0
#define STOP_BIT_0_5		                    1
#define STOP_BIT_2			                    2
#define STOP_BIT_1_5		                    3

#define OVER_SAMPLE16							0
#define OVER_SAMPLE8							1


#define DATA_SIZE_8_BIT		                    1
#define DATA_SIZE_9_BIT		                    2

#define XCK_RISING_TX_XCH_FALLING_RX			1
#define XCK_RISING_RX_XCH_FALLING_TX			2

#define CAPTURE_LEADING_SAMPLE_TRAILING			1
#define SAMPLE_LEADING_CAPTURE_TRAILING			2

#define RESET									0
#define SET										1


#endif /* MUSART_PRIVATE_H_ */
