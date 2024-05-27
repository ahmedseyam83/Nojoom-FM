/*
 * HDAC_Config.h
 *
 *  Created on: 3 May 2024
 *      Author: User
 */

#ifndef HDAC_CONFIG_H_
#define HDAC_CONFIG_H_

#define DAC_PORT			GPIO_PORTB

#define DAC_PINS_INIT		0
#define DAC_PINS_END		7

#define DAC_R0				GPIO_PIN0
#define DAC_R1              GPIO_PIN1
#define DAC_R2              GPIO_PIN2
#define DAC_R3              GPIO_PIN5
#define DAC_R4              GPIO_PIN6
#define DAC_R5              GPIO_PIN7
#define DAC_R6              GPIO_PIN8
#define DAC_R7              GPIO_PIN9


/*
 * SAMPLE_RATE_8000
 * SAMPLE_RATE_16000
 * SAMPLE_RATE_32000
 * SAMPLE_RATE_44100
 * SAMPLE_RATE_48000
 * SAMPLE_RATE_96000
 */

#define SAMPLE_RATE		SAMPLE_RATE_8000


const u8 DAC_Pins[8] = {DAC_R0, DAC_R1, DAC_R2, DAC_R3, DAC_R4, DAC_R5, DAC_R6, DAC_R7};

#endif /* HDAC_CONFIG_H_ */
