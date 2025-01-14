/*
 * HTFT_program.c
 *
 *  Created on: Dec 24, 2024
 *      Author: ZBOOK
 */

#include <HAL/HTFT/HTFT_config.h>
#include <HAL/HTFT/HTFT_interface.h>
#include <LIB/Bit_Math.h>
#include <LIB/STD_Types.h>
#include <MCAL/MGPIO/MGPIO_interface.h>
#include <MCAL/MSTK/MSTK_interface.h>
#include "MCAL/MSPI/MSPI_interface.h"


void HTFT_void_Init(void)
{
	MGPIO_void_SetMode(TFT_PORT,RST_PIN,Output);
	MGPIO_void_SetOutputPinMode(TFT_PORT,RST_PIN,PUSH_PULL,LOWSpeed);


	MGPIO_void_SetMode(TFT_PORT,DC_PIN,Output);
	MGPIO_void_SetOutputPinMode(TFT_PORT,DC_PIN,PUSH_PULL,LOWSpeed);

	MGPIO_void_SetMode(TFT_PORT,CS_PIN,Output);
    MGPIO_void_SetOutputPinMode(TFT_PORT,CS_PIN,PUSH_PULL,LOWSpeed);


	//reset sequence
	MGPIO_void_SetPinValue(TFT_PORT,RST_PIN,High);
	MSTK_voidDelayus(100);
	MGPIO_void_SetPinValue(TFT_PORT,RST_PIN,LOW);
	MSTK_voidDelayus(1);
	MGPIO_void_SetPinValue(TFT_PORT,RST_PIN,High);
	MSTK_voidDelayus(100);
	MGPIO_void_SetPinValue(TFT_PORT,RST_PIN,LOW);
	MSTK_voidDelayus(100);
	MGPIO_void_SetPinValue(TFT_PORT,RST_PIN,High);
	MSTK_voidDelayms(120);

	//sleepout
	HTFT_void_WriteCMD(0x11);
	MSTK_voidDelayms(10);

	//select color mode
	HTFT_void_WriteCMD(0x3A);
	//Select RGB 565
	HTFT_void_Writedata(0x05);

	//display on
	HTFT_void_WriteCMD(0x29);



}
void HTFT_void_Writedata(u8 Copy_u8Data)
{
	MGPIO_void_SetPinValue(TFT_PORT,CS_PIN,LOW);
	MGPIO_void_SetPinValue(TFT_PORT,DC_PIN,High);
	(void)MSPI_u8Transcieve(Copy_u8Data);

}
void HTFT_void_WriteCMD(u8 Copy_u8CMD)
{
	MGPIO_void_SetPinValue(TFT_PORT,CS_PIN,LOW);
	MGPIO_void_SetPinValue(TFT_PORT,DC_PIN,LOW);
	(void)MSPI_u8Transcieve(Copy_u8CMD);

}
void HTFT_void_Display(const u16 *Copy_pu16PTR)
{
	u16 i=0;
	u8 Copy_u8High=0;
	u8 Copy_u8Low=0;

	//Set X
	HTFT_void_WriteCMD(0x2A);
	HTFT_void_Writedata(0);
	HTFT_void_Writedata(0);
	HTFT_void_Writedata(0);
	HTFT_void_Writedata(127);

	//Set y
	HTFT_void_WriteCMD(0x2B);
	HTFT_void_Writedata(0);
	HTFT_void_Writedata(0);
	HTFT_void_Writedata(0);
	HTFT_void_Writedata(159);


	//Write in RAM (on screen)
	HTFT_void_WriteCMD(0x2C);

	for(i=0;i<20480;i++)
	{
		Copy_u8High=(u8)(Copy_pu16PTR[i]>>8);
		Copy_u8Low=(u8)Copy_pu16PTR[i];
		HTFT_void_Writedata(Copy_u8High);
		HTFT_void_Writedata(Copy_u8Low);
	}










}
