/*
 * H7SEG_interface.h
 *
 *  Created on: Dec 6, 2024
 *      Author: Ola Saadeh
 */

#ifndef H7SEG_INTERFACE_H_
#define H7SEG_INTERFACE_H_

#define COMMON_CATHODE 0
#define COMMON_ANODE   1

void H7SEG_voidInit(void);
void H7SEG_voidDisplayAnyNumber(void);
void H7SEG_voidClear(void);
void H7SEG_voidSetNumber(u8 num);

#endif /* H7SEG_INTERFACE_H_ */





