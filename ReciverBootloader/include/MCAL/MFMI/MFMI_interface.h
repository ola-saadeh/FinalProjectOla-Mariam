/*
 * MFMI_interface.h
 *
 *  Created on: Jan 7, 2025
 *      Author: ZBOOK
 */


#ifndef MFMI_INTERFACE_H_
#define MFMI_INTERFACE_H_

#define VTOR *((volatile u32*) (0xE000ED08))
typedef enum
{
	sector0=0,
	sector1,
	sector2,
	sector3,
	sector4,
	sector5
}Sector;



void MFMI_voidMassErase(void);
void MFMI_voidSectorErase(Sector Copy_uddtSectorNumber);
void MFMI_voidSectorsErase(Sector Copy_uddtSectorstart,Sector Copy_uddtSectorend);
void MFMI_voidFlashWrite(u32 Copy_u32Adress,u16* Copy_pu16Ptr,u8 Copy_u8DataLength);


#endif /* MFMI_INTERFACE_H_ */
