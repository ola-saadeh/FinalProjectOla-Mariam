
/*
 * MEXTI_private.h
 *
 *  Created on: Dec 15, 2024
 *      Author:
 */

#ifndef MEXTI_PRIVATE_H_
#define MEXTI_PRIVATE_H_

#define EXTI_BASE_ADRESS (0x40013C00)
#define SYSCFG_BASE_ADRESS (0x40013800)


typedef struct
{
	u32 IMR;
	u32 EMR;
	u32 RTSR;
	u32 FTSR;
	u32 SWIER;
	u32 PR;
}MEXTI_t;


typedef struct
{
 u32 MEMRMP;
 u32 PMC;
 u32 EXTICR[4];
 u32 Reserved[2];
 u32 CMPCR;
}MSYSCFG_t;

#define EXTI ((volatile MEXTI_t*)EXTI_BASE_ADRESS)
#define SYSCFG ((volatile MSYSCFG_t*)SYSCFG_BASE_ADRESS)


#define DIV_Fac  4
#define Musk     15


#endif /* MEXTI_PRIVATE_H_ */
