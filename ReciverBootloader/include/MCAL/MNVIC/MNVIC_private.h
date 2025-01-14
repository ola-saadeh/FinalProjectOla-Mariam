/*
 * MNVIC_private.h
 *
 *  Created on: Dec 12, 2024
 *      Author: ZBOOK
 */

#ifndef MNVIC_PRIVATE_H_
#define MNVIC_PRIVATE_H_

#define NVIC_BASE_ADRESS (0xE000E100)

typedef struct
{
u32 NVIC_ISER[8];
u32 Reserved0[24];
u32 NVIC_ICER[8];
u32 Reserved1[24];
u32 NVIC_ISPR[8];
u32 Reserved2[24];
u32 NVIC_ICPR[8];
u32 Reserved3[24];
u32 NVIC_IAPR[8];
u32 Reserved4[56];
u8  NVIC_IPR[240];
u32 Reserved5[580];
u32 NVIC_STIR;
}NVIC_t;

#define NVIC  ((volatile NVIC_t*)NVIC_BASE_ADRESS)


#define Reg_Div  32


#define SCB_AIRCR (*(volatile u32*)(0xE000ED0C))
#define VectKey  0x05FA0000



#endif /* MNVIC_PRIVATE_H_ */
