/*
 * MSPI_program.c
 *
 *  Created on: Dec 24, 2024
 *      Author: ZBOOK
 */

#include "LIB/STD_Types.h"
#include "LIB/Bit_Math.h"
#include "MCAL/MSPI/MSPI_private.h"
#include "MCAL/MSPI/MSPI_interface.h"


void MSPI_void_MasterInit(void)
{

	SPI->CR1 |=(1<<SSM);
	SPI->CR1 |=(1<<SSI);

	SPI->CR1 |=(1<<MSTR);
	SPI->CR1 |=(1<<CPOL);

	SPI->CR1 |=(1<<SPE);

}
void MSPI_void_SlaveInit(void)
{
	SPI->CR1 &=~(1<<MSTR);
	SPI->CR1 |=(1<<CPOL);
	SPI->CR1 |=(1<<SPE);

}
u8 MSPI_u8Transcieve(u8 Copy_u8Data)
{
	while(!Get_Bit(SPI->SR,TXE));
	SPI->DR=Copy_u8Data;
	while(!Get_Bit(SPI->SR,RXNE));
	return (u8)SPI->DR;
}


