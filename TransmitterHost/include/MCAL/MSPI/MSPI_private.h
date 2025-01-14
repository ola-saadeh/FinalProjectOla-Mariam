/*
 * MSPI_private.h
 *
 *  Created on: Dec 24, 2024
 *      Author: ZBOOK
 */

#ifndef MSPI_PRIVATE_H_
#define MSPI_PRIVATE_H_

#define SPI1_BASE_ADRESS (0x40013000)

typedef struct
{
	u32 CR1;
	u32 CR2;
	u32 SR;
	u32 DR;
	u32 CRCPR;
	u32 RXCRCR;
	u32 TXCRCR;
	u32 I2SCFGR;
	u32 I2SPR;
}MSPI_t;

#define SPI ((volatile MSPI_t*)SPI1_BASE_ADRESS)

#define SSM  9
#define SSI  8
#define MSTR 2
#define CPOL 1
#define SPE  6

#define TXE 1
#define RXNE 0

#endif /* MSPI_PRIVATE_H_ */
