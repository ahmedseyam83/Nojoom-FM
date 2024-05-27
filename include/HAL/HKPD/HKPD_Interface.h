/*
 * KPD.h
 *
 *  Created on: 20 Mar 2024
 *      Author: User
 */

#ifndef HAL_KPD_KPD_INTERFACE_H_
#define HAL_KPD_KPD_INTERFACE_H_




#define NOTPRESSED		0xFF


void HKPD_Init(void);
u8	HKPD_u8GetPressed(void);


#endif /* HAL_KPD_KPD_INTERFACE_H_ */
