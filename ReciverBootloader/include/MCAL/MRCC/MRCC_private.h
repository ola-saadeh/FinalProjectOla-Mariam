/*
 * MRCC_private.h
 *
 *  Created on: Nov 24, 2024
 *      Author: ZBOOK
 */


#ifndef MRCC_PRIVATE_H_
#define MRCC_PRIVATE_H_


#define RCC_BASE_ADRESS (0x40023800)

typedef struct
{
	u32 CR;
	u32 PLLCFGR;
	u32 CFGR;
	u32 CIR;
	u32 AHB1RSTR;
	u32 AHB2RSTR;
	u32 Reserved1;
	u32 Reserved2;
	u32 APB1RSTR;
	u32 APB2RSTR;
	u32 Reserved3;
	u32 Reserved4;
	u32 AHB1ENR;
	u32 AHB2ENR;
	u32 Reserved5;
	u32 Reserved6;
	u32 APB1ENR;
	u32 APB2ENR;
	u32 Reserved7;
	u32 Reserved8;
	u32 AHB1LPENR;
	u32 AHB2LPENR;
	u32 Reserved9;
	u32 Reserved10;
	u32 APB1LPENR;
	u32 APB2LPENR;
	u32 Reserved11;
	u32 Reserved12;
	u32 BDCR;
	u32 CSR;
	u32 Reserved13;
	u32 Reserved14;
	u32 SSCGR;
	u32 PLLI2SCFGR;
	u32 Reserved15;
	u32 DCKCFGR;

}RCC_t;

#define RCC    ((volatile RCC_t*)RCC_BASE_ADRESS)


#define MRCC_HSEBYP 18
#define MRCC_HSERDY 17
#define MRCC_HSEON  16
#define MRCC_HSIRDY 1
#define MRCC_HSION  0

#define MRCC_SW1    1
#define MRCC_SW0    0

#define HSI_CLOCK 0
#define HSE_CLOCK 1


#define SWITCH_HSI  0
#define SWITCH_HSE  1
#define SWITCH_MUSK 3

#define MECHANICAL_HSE  0
#define ELECTRICAL_HSE  1




#endif /* MRCC_PRIVATE_H_ */
