/*
 * MFMI_private.h
 *
 *  Created on: Jan 7, 2025
 *      Author: ZBOOK
 */

#ifndef MFMI_PRIVATE_H_
#define MFMI_PRIVATE_H_

#define MFMI_BASE_ADDRESS  0x40023C00

typedef struct
{
	u32 ACR;
	u32 KEYR;
	u32 OPTKEYR;
	u32 SR;
	u32 CR;
	u32 OPTCR;
}MFMI_t;

#define FMI ((volatile MFMI_t*)(MFMI_BASE_ADDRESS))

#define BSY  16

#define LOCK  31

#define KEY1  0x45670123

#define KEY2  0xCDEF89AB

#define MER  2
#define SER  1
#define PG   0
#define STRT 16
#define MUSK1 15
#define SNB 3

#define MUSK2 3
#define Write_HALF_Word 1
#define PSIZE 8

#endif /* MFMI_PRIVATE_H_ */
