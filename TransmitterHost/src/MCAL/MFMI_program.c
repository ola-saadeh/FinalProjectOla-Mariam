///*
// * MFMI_program.c
//
// *
// *  Created on: Jan 7, 2025
// *      Author: ZBOOK
// */
//#include "STD_Types.h"
//#include "Bit_Math.h"
//#include "MFMI_interface.h"
//#include "MFMI_private.h"
//
//
//void MFMI_voidMassErase(void){
//	while(Get_Bit(FMI->SR,BSY)==1);
//	if(Get_Bit())
//}
//void MFMI_voidSectorErase(Sector Copy_uddtSectorNumber){
//
//}
//void MFMI_voidFlashWrite(u32 Copy_u32Adress, u16* Copy_pu16Ptr,u8 Copy_u8DataLength){
//
//}
//
//
//
#include <LIB/Bit_Math.h>
#include <LIB/STD_Types.h>
#include <MCAL/MFMI/MFMI_interface.h>
#include <MCAL/MFMI/MFMI_private.h>


void MFMI_voidMassErase(void)
{
	while(Get_Bit(FMI->SR,BSY)==1);

	if(Get_Bit(FMI->CR,LOCK)==1)
	{
		FMI->KEYR =KEY1;
		FMI->KEYR =KEY2;
	}

	FMI->CR |=(1<<MER);

	FMI->CR |=(1<<STRT);

	while(Get_Bit(FMI->SR,BSY)==1);

	FMI->CR &=~(1<<MER);
}
void MFMI_voidSectorErase(Sector Copy_uddtSectorNumber)
{
	while(Get_Bit(FMI->SR,BSY)==1);

	if(Get_Bit(FMI->CR,LOCK)==1)
	{
		FMI->KEYR =KEY1;
		FMI->KEYR =KEY2;
	}

	FMI->CR &=~(MUSK1<<SNB);
	FMI->CR |=(Copy_uddtSectorNumber<<SNB);

	FMI->CR |=(1<<SER);

	FMI->CR |=(1<<STRT);

	while(Get_Bit(FMI->SR,BSY)==1);

	FMI->CR &=~(1<<SER);
}

void MFMI_voidSectorsErase(Sector Copy_uddtSectorstart,Sector Copy_uddtSectorend)
{
	u8 i=0;
	for(i=Copy_uddtSectorstart;i<=Copy_uddtSectorend;i++)
	{
		MFMI_voidSectorErase(i);
	}

}
void MFMI_voidFlashWrite(u32 Copy_u32Adress,u16* Copy_pu16Ptr,u8 Copy_u8DataLength)
{
	u32 Loc_u32Iterator=0;

	while(Get_Bit(FMI->SR,BSY)==1);

	if(Get_Bit(FMI->CR,LOCK)==1)
	{
		FMI->KEYR =KEY1;
		FMI->KEYR =KEY2;
	}

	FMI->CR &=~(MUSK2<<PSIZE);
	FMI->CR |=(Write_HALF_Word<<PSIZE);

	for(Loc_u32Iterator=0;Loc_u32Iterator<Copy_u8DataLength;Loc_u32Iterator++)
	{
		FMI->CR |=(1<<PG);

		*((volatile u16*)(Copy_u32Adress))=Copy_pu16Ptr[Loc_u32Iterator];
		Copy_u32Adress +=2;

		while(Get_Bit(FMI->SR,BSY)==1);

		FMI->CR &=~(1<<PG);
	}



}

