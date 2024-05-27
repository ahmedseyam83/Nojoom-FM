/*
 * HS2P_Config.h
 *
 *  Created on: 12 May 2024
 *      Author: User
 */

#ifndef HS2P_CONFIG_H_
#define HS2P_CONFIG_H_


/* S2P 1 Enable Selection
 * 1. ENABLED
 * 2. DISABLED
 */
#define S2P1_ENABLE_SELECT	ENABLED

#define S2P_PORT			GPIO_PORTB


#define S2P_DS_PIN			GPIO_PIN15
#define S2P_SH_CLK_PIN		GPIO_PIN13
#define S2P_STRG_CLK_PIN	GPIO_PIN14

/*if S2P_16_BIT Enabled*/
#define S2P_RST_PIN			GPIO_PIN3
#define S2P_ENABLE_PIN		GPIO_PIN4

/* Select the number of output bit
 * 1. S2P_16_BIT
 * 2. S2P_8_BIT
 */
#define S2P_SELECT S2P_8_BIT

/* S2P 1 Enable Selection
 * 1. ENABLED
 * 2. DISABLED
 */
#define S2P2_ENABLE_SELECT	ENABLED

#define S2P2_PORT			GPIO_PORTB


#define S2P2_DS_PIN			GPIO_PIN12
#define S2P2_SH_CLK_PIN		GPIO_PIN13
#define S2P2_STRG_CLK_PIN	GPIO_PIN14

/*if S2P_16_BIT Enabled*/
#define S2P2_RST_PIN		GPIO_PIN3
#define S2P2_ENABLE_PIN		GPIO_PIN4

/* Select the number of output bit
 * 1. S2P_16_BIT
 * 2. S2P_8_BIT
 */
#define S2P2_SELECT S2P_8_BIT

#endif /* HS2P_CONFIG_H_ */
