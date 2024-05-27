/*
 * MUSART_Interface.h
 *
 *  Created on: 8 May 2024
 *      Author: User
 */

#ifndef MUSART_INTERFACE_H_
#define MUSART_INTERFACE_H_
/************************************************************************************************/
/*									FUNCTIONS API's												*/
/************************************************************************************************/


void MUSART_voidInit(void);
void MUSART_voidEnable(void);
void MUSART_voidDisable(void);

void MUSART_voidSendByteSynch(u8 copy_u8Data);
void MUSART_voidReceiveByte(u8* copy_u8Data);

void MUSART_voidSendString(u8* copy_u8Data);
void MUSART_voidReceiveString(u8* copy_u8Data);

void MUSART_voidSendStringAsynch(const u8 * Copy_pchString , void (* NotificationFunc)(void));
void MUSART_voidReceiveBufferAsynch(u8 * Copy_pchString , u32 Copy_u32BufferSize , void (* NotificationFunc)(void));

#endif /* MUSART_INTERFACE_H_ */
