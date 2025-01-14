/*
 * MSTK_interface.h
 *
 *  Created on: Dec 3, 2024
 *      Author:
 */

#ifndef MSTK_INTERFACE_H_
#define MSTK_INTERFACE_H_


typedef enum
{
	SYSTICKINTENABLE=0,
	SYSTICKINTDISABLE

}SYSTICKINTSTATE;

void MSTK_voidInit(void);
void MSTK_voidStartTimer(u32 Copy_u32ReloadValue);
u8   MSTK_u8ReadFlag(void);
void MSTK_voidCtrlIntState(SYSTICKINTSTATE Copy_uddtSYSTICKINT);
u32  MSTK_u32GetElapsedTicksSingleShot(void);
u32  MSTK_u32GetRemainingTicksSingleShot(void);
void MSTK_voidStopTimer(void);

void MSTK_voidDelayms(u32 Copy_u32DelayByMS);
void MSTK_voidDelayus(u32 Copy_u32DelayByUS);


void MSTK_void_CallBack(void(*ptr)(void),u32 TickTime);
void MSTK_void_CallBacksingle(void(*ptr)(void),u32 TickTimeUS);


#endif /* MSTK_INTERFACE_H_ */
