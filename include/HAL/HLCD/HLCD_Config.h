/*
 * LCD_Config.h
 *
 *  Created on: Mar 19, 2024
 *      Author: Ibrahim
 */

#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_


#define LCD_DATA_PORT		GPIO_PORTA
#define LCD_CTRL_PORT		GPIO_PORTC

#define LCD_EN_PIN			GPIO_PIN13
#define LCD_RW_PIN			GPIO_PIN14
#define LCD_RS_PIN			GPIO_PIN15

#define LCD_D0_PIN			GPIO_PIN0
#define LCD_D1_PIN			GPIO_PIN1
#define LCD_D2_PIN			GPIO_PIN2
#define LCD_D3_PIN			GPIO_PIN3
#define LCD_D4_PIN			GPIO_PIN4
#define LCD_D5_PIN			GPIO_PIN5
#define LCD_D6_PIN			GPIO_PIN6
#define LCD_D7_PIN			GPIO_PIN7


#define LCD_MODE			LCD_EIGHT_BIT


#endif /* HAL_LCD_LCD_CONFIG_H_ */
