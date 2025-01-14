/*
 * MNVIC_interface.h
 *
 *  Created on: Dec 12, 2024
 *      Author: ZBOOK
 */

#ifndef MNVIC_INTERFACE_H_
#define MNVIC_INTERFACE_H_

typedef enum
{
	Group16Sub0=3,
	Group8Sub2,
	Group4Sub4,
	Group2Sub8,
	Group0Sub16
}MNVIC_Group_t;


void MNVIC_void_Enable(u8 Copy_u8IntPosition);
void MNVIC_void_Disable(u8 Copy_u8IntPosition);
void MNVIC_void_PendingEnable(u8 Copy_u8IntPosition);
void MNVIC_void_PendingDisable(u8 Copy_u8IntPosition);
u8   MNVIC_u8_ReadingActiveState(u8 Copy_u8IntPosition);
void MNVIC_void_SetInterruptPriority(u8 Copy_u8IntPosition,u8 Copy_u8Group,u8 Copy_u8SubGroub);
void MNVIC_void_SetInterruptGroupmode(MNVIC_Group_t Copy_uddtGroupMode);




#endif /* MNVIC_INTERFACE_H_ */
