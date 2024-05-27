
/************************************************************************/
/*							FILES INCLUSIONS							*/
/************************************************************************/
/*******************************LIB**************************************/
#include <LIB/Std_Types.h>
#include "../include/LIB/BIT_Math.h"
#include "../include/MCAL/MNVIC/MNVIC_Interface.h"
#include "../include/MCAL/MNVIC/MNVIC_private.h"
#include "../include/MCAL/MNVIC/MNVIC_Config.h"

static MNVIC_Group_t sglobal_NVIC_Group_t_Mode;

/************************************************************************/
/*						   FUNCTIONS DEFINITIONS						*/
/************************************************************************/

void MNVIC_voidEnablePeripheralInterrupt(u8 copy_u8Peripheral)
{

	SET_BIT(NVIC->ISER[copy_u8Peripheral/ BITS_IN_REGISTER],(copy_u8Peripheral% BITS_IN_REGISTER));

}

void MNVIC_voidDisablePeripheralInterrupt(u8 copy_u8Peripheral)
{
	SET_BIT(NVIC->ICER[copy_u8Peripheral/ BITS_IN_REGISTER],(copy_u8Peripheral% BITS_IN_REGISTER));
}

void MNVIC_voidEnablePeripheralInterruptPending(u8 copy_u8Peripheral)
{
	SET_BIT(NVIC->ISPR[copy_u8Peripheral/ BITS_IN_REGISTER],(copy_u8Peripheral% BITS_IN_REGISTER));
}

void MNVIC_voidDisablePeripheralInterruptPending(u8 copy_u8Peripheral)
{
	SET_BIT(NVIC->ICPR[copy_u8Peripheral/ BITS_IN_REGISTER],(copy_u8Peripheral% BITS_IN_REGISTER));
}

void MNVIC_voidGetInterruptState(u8 copy_u8Peripheral, u8 *p_Read)
{
	*p_Read = GET_BIT(NVIC->IABR[copy_u8Peripheral/ BITS_IN_REGISTER],(copy_u8Peripheral% BITS_IN_REGISTER));
}



void MNVIC_voidSetInterruptGroupMode(MNVIC_Group_t MNVIC_GroupMode)
{
	sglobal_NVIC_Group_t_Mode = MNVIC_GroupMode;
	SCB_AIRCR = (SCB_WRITE_VECTKEY | (MNVIC_GroupMode<<AICIR_PROIGROUP_B0));
}

void MNVIC_voidSetInterruptPriority(u8 copy_u8Peripheral,u8 copy_u8GroupNumber, u8 copy_u8SubGroupNumber)
{
	switch(sglobal_NVIC_Group_t_Mode)
	{
	case Group16_NoSub:
		NVIC->IPR[copy_u8Peripheral] = (copy_u8GroupNumber <<4);
		break;
	case Groups8_Sub2:
		NVIC->IPR[copy_u8Peripheral] = ((copy_u8GroupNumber <<5)|(copy_u8SubGroupNumber<<4));
		break;
	case Groups4_Sub4:
		NVIC->IPR[copy_u8Peripheral] = ((copy_u8GroupNumber <<6)|(copy_u8SubGroupNumber<<4));
		break;
	case Groups2_Sub8:
		NVIC->IPR[copy_u8Peripheral] = ((copy_u8GroupNumber <<7)|(copy_u8SubGroupNumber<<4));
		break;
	case NoGroup_Sub16:
		NVIC->IPR[copy_u8Peripheral] = ((copy_u8SubGroupNumber<<4));
		break;
	default:
		break;
	}
}
