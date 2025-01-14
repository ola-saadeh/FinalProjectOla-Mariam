/*
 * AHexParser_prg.c
 *
 *  Created on: Jan 11, 2025
 *      Author: ZBOOK
 */

#include <APP/AHexParser/AHexParser_interface.h>
#include <LIB/Bit_Math.h>
#include <LIB/STD_Types.h>
#include <MCAL/MFMI/MFMI_interface.h>
u32 Copy_u32HighAddress;



static u8 AHexParser_u8ASCIToHex(u8 Copy_u8Variable)
{
	u8 Copy_u8Local=0;
	if(Copy_u8Variable>='0' &&Copy_u8Variable<='9')
	{
		Copy_u8Local=Copy_u8Variable-48;
	}
	else
	{
		Copy_u8Local=Copy_u8Variable-55;
	}
	return Copy_u8Local;
}


void AHexParser_voidParseRecord(const char *Copy_u8Record)
{
	u8 Copy_u8Local=AHexParser_u8ASCIToHex(Copy_u8Record[8]);
	u8 HighAddress1,HighAddress2,HighAddress3,HighAddress4;
	u32 NewHighAddress;
	switch (Copy_u8Local) {
	case 0:
		AHexParser_voidParseData(Copy_u8Record);
		break;
	case 4:
		HighAddress1 = AHexParser_u8ASCIToHex(Copy_u8Record[9]);
		HighAddress2 = AHexParser_u8ASCIToHex(Copy_u8Record[10]);
		HighAddress3 = AHexParser_u8ASCIToHex(Copy_u8Record[11]);
		HighAddress4 = AHexParser_u8ASCIToHex(Copy_u8Record[12]);
		NewHighAddress = (HighAddress1 << 12) | (HighAddress2 << 8)| (HighAddress3 << 4)| (HighAddress4);
		Copy_u32HighAddress = NewHighAddress << 16;
		break;
	case 1:
		//end of file
		break;
	default:
		break;
	}

}
void AHexParser_voidParseData(const char *Copy_u8Record)
{
	u8 CC_High=AHexParser_u8ASCIToHex(Copy_u8Record[1]);
	u8 CC_Low=AHexParser_u8ASCIToHex(Copy_u8Record[2]);
	u8 CC_Value=(CC_High<<4)|(CC_Low);

	u8 Address_0=AHexParser_u8ASCIToHex(Copy_u8Record[3]);
	u8 Address_1=AHexParser_u8ASCIToHex(Copy_u8Record[4]);
	u8 Address_2=AHexParser_u8ASCIToHex(Copy_u8Record[5]);
	u8 Address_3=AHexParser_u8ASCIToHex(Copy_u8Record[6]);

	u32 Address=Copy_u32HighAddress |(Address_0<<12)|(Address_1<<8)|(Address_2<<4)|(Address_3);

	u8 Digit_0=0;
	u8 Digit_1=0;
	u8 Digit_2=0;
	u8 Digit_3=0;
	u16 Data[10]={0};

	for(u8 i=0;i<(CC_Value/2);i++)
	{
		Digit_0=AHexParser_u8ASCIToHex(Copy_u8Record[9+(i*4)]);
		Digit_1=AHexParser_u8ASCIToHex(Copy_u8Record[10+(i*4)]);
		Digit_2=AHexParser_u8ASCIToHex(Copy_u8Record[11+(i*4)]);
		Digit_3=AHexParser_u8ASCIToHex(Copy_u8Record[12+(i*4)]);
		Data[i]=(Digit_2<<12)|(Digit_3<<8)|(Digit_0<<4)|(Digit_1);
	}

	MFMI_voidFlashWrite(Address,Data,(CC_Value/2));

}



