#ifndef HAL_KPD_KPD_CONFIG_H_
#define HAL_KPD_KPD_CONFIG_H_



char KPD_u8Buttons[4][4]= { {'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'?','0','=','+'} };


#define KPD_ROW_INIT	GPIO_PIN5
#define KPD_ROW_END		GPIO_PIN8

#define	KPD_COL_INIT	GPIO_PIN12
#define	KPD_COL_END		GPIO_PIN15

#define KPD_PORT		GPIO_PORTB

#define KPD_R0			GPIO_PIN5
#define KPD_R1			GPIO_PIN6
#define KPD_R2			GPIO_PIN7
#define KPD_R3			GPIO_PIN8

#define KPD_C0			GPIO_PIN12
#define KPD_C1			GPIO_PIN13
#define KPD_C2			GPIO_PIN14
#define KPD_C3			GPIO_PIN15




#endif /* HAL_KPD_KPD_CONFIG_H_ */
