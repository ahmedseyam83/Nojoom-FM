/*
 * HTFT_Interface.h
 *
 *  Created on: 14 May 2024
 *      Author: User
 */

#ifndef HTFT_INTERFACE_H_
#define HTFT_INTERFACE_H_


void HTFT_voidInit(void);
void HTFT_voidDisplayImg(u8 copy_u8LeftPad,u8 copy_u8RightPad,u8 copy_u8TopPad,u8 copy_u8BottomPad,const u16  *copy_pu16Data);
void HTFT_voidDisplayImgSetConfiguration_DMA(u8 copy_u8LeftPad,u8 copy_u8RightPad,u8 copy_u8TopPad,u8 copy_u8BottomPad);



#endif /* HTFT_INTERFACE_H_ */
