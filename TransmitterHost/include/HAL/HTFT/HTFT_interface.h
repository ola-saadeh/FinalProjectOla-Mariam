/*
 * HTFT_interface.h
 *
 *  Created on: Dec 24, 2024
 *      Author: ZBOOK
 */

#ifndef HTFT_INTERFACE_H_
#define HTFT_INTERFACE_H_
#include <LIB/STD_Types.h>
void HTFT_void_Init(void);
void HTFT_void_Writedata(u8 Copy_u8Data);
void HTFT_void_WriteCMD(u8 Copy_u8CMD);
void HTFT_void_Display(const u16 *Copy_pu16PTR);


#endif /* HTFT_INTERFACE_H_ */
