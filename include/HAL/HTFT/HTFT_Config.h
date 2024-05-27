/*
 * HTFT_Config.h
 *
 *  Created on: 14 May 2024
 *      Author: User
 */

#ifndef HTFT_CONFIG_H_
#define HTFT_CONFIG_H_



#define TFT_PORT		GPIO_PORTA
#define A0_PIN			GPIO_PIN3
#define RST_PIN			GPIO_PIN2

#define X_AXIS_INIT		0
#define X_AXIS_END		127
#define Y_AXIS_INIT		0
#define Y_AXIS_END		159


#define PIXELS_MAX_NO				20480

/*Set SPI Enable
 * choose between
 * 1. SPI1_ENABLE
 * 2. SPI2_ENABLE
 */
#define SPI_ENABLE_SELECT					SPI1_ENABLE



#endif /* HTFT_CONFIG_H_ */
