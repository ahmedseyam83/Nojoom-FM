
#ifndef HS2P_INTERCFACE_H_
#define HS2P_INTERCFACE_H_

typedef enum{
	DISABLED=0,
	ENABLED
}ChipState_t;

/************************************************************************************************/
/*									FUNCTIONS API's												*/
/************************************************************************************************/

void HS2P_voidInit(void);
void HS2P2_voidSendBit(u8 Copy_u8Data,u8 Copy_u8Bitnumber);
void HS2P_voidSendByte(u8 Copy_u8Data);
void HS2P_voidSendData(u16 Copy_u8Data);
void HS2P_voidChipEnableDisable(ChipState_t copy_ChState);
void HS2P_voidChipReset(void);

void HS2P2_voidInit(void);
void HS2P22_voidSendBit(u8 Copy_u8Data,u8 Copy_u8Bitnumber);
void HS2P2_voidSendByte(u8 Copy_u8Data);
void HS2P2_voidSendData(u16 Copy_u8Data);
void HS2P2_voidChipEnableDisable(ChipState_t copy_ChState);
void HS2P2_voidChipReset(void);

void HS2P_voidSendPattern_LDMX(u8* copy_u8ptrtoData);

#endif /* HS2P_INTERCFACE_H_ */
