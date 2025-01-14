/*
 * MNVIC_program.c
 *
 *  Created on: Dec 12, 2024
 *      Author: ZBOOK
 */


#include <LIB/Bit_Math.h>
#include <LIB/STD_Types.h>
#include <MCAL/MNVIC/MNVIC_interface.h>
#include <MCAL/MNVIC/MNVIC_private.h>

u8 Copy_u8Global=0;

void MNVIC_void_Enable(u8 Copy_u8IntPosition)
{
	NVIC->NVIC_ISER[Copy_u8IntPosition/Reg_Div] |=(1<<(Copy_u8IntPosition%Reg_Div));
}

void MNVIC_void_Disable(u8 Copy_u8IntPosition)
{
	NVIC->NVIC_ICER[Copy_u8IntPosition/Reg_Div] |=(1<<(Copy_u8IntPosition%Reg_Div));
}

void MNVIC_void_PendingEnable(u8 Copy_u8IntPosition)
{
	NVIC->NVIC_ISPR[Copy_u8IntPosition/Reg_Div] |=(1<<(Copy_u8IntPosition%Reg_Div));
}

void MNVIC_void_PendingDisable(u8 Copy_u8IntPosition)
{
	NVIC->NVIC_ICPR[Copy_u8IntPosition/Reg_Div] |=(1<<(Copy_u8IntPosition%Reg_Div));
}

u8   MNVIC_u8_ReadingActiveState(u8 Copy_u8IntPosition)
{
	return Get_Bit(NVIC->NVIC_IAPR[Copy_u8IntPosition/Reg_Div],(Copy_u8IntPosition%Reg_Div));
}

void MNVIC_void_SetInterruptGroupmode(MNVIC_Group_t Copy_uddtGroupMode)
{
	Copy_u8Global=Copy_uddtGroupMode;
	u32 Copy_u32LOC=0;
	Copy_u32LOC=VectKey | (Copy_uddtGroupMode<<8);
	SCB_AIRCR=Copy_u32LOC;
}

void MNVIC_void_SetInterruptPriority(u8 Copy_u8IntPosition,u8 Copy_u8Group,u8 Copy_u8SubGroub)
{
	switch (Copy_u8Global) {
	case Group16Sub0:
		NVIC->NVIC_IPR[Copy_u8IntPosition] =Copy_u8Group<<4;
		break;
	case Group8Sub2:
		NVIC->NVIC_IPR[Copy_u8IntPosition] =Copy_u8Group<<5 | Copy_u8SubGroub<<4;
		break;
	case Group4Sub4:
		NVIC->NVIC_IPR[Copy_u8IntPosition] =Copy_u8Group<<6 | Copy_u8SubGroub<<4;
		break;
	case Group2Sub8:
		NVIC->NVIC_IPR[Copy_u8IntPosition] =Copy_u8Group<<7 | Copy_u8SubGroub<<4;
		break;
	case Group0Sub16:
		NVIC->NVIC_IPR[Copy_u8IntPosition] =Copy_u8SubGroub<<4;
		break;
	default:
		break;
	}
}






