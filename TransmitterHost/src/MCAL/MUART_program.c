/****************************************************************/
/******* Author     : Ola Saadeh                *****************/
/******* Created on : Jan 4, 2025               *****************/
/******* File Name  : MUART_program.c           *****************/
/****************************************************************/

/*****************************< LIB *****************************/
#include <LIB/Bit_Math.h>
#include <LIB/STD_Types.h>
#include <MCAL/MDMA/MDMA_interface.h>
#include <MCAL/MUART/MUART_config.h>
#include <MCAL/MUART/MUART_interface.h>
#include <MCAL/MUART/MUART_private.h>

/************************< Function Implementations ***************/


/**
 * @brief Initialize UART with the required configuration.
 *
 * Configures baud rate, data length, and enables transmitter and receiver.
 *
 * @return Std_ReturnType Initialization status (E_OK/E_NOT_OK).
 */
Std_ReturnType MUART_void_Init(void)
{
    UART->CR1.OVER8 = 0;  // 16x oversampling
    UART->BRR = (104 << 4) | (3);  // Baud rate 9600
    UART->CR1.M = 0;  // 8-bit data length
    UART->CR1.PCE = 0;  // No parity
    UART->CR1.TE = 1;  // Enable transmitter
    UART->CR1.RE = 1;  // Enable receiver
    UART->CR3 |= (1 << 6);  // Enable DMA for reception
    UART->CR1.UE = 1;  // Enable UART

    return E_OK;  // Success
}



/**
 * @brief Send a byte via UART.
 *
 * Waits for the TXE flag and then sends the byte.
 *
 * @param Copy_u8Data Data byte to be transmitted.
 * @return Std_ReturnType Transmission status (E_OK/E_NOT_OK).
 */
Std_ReturnType MUART_void_SendData(u8 Copy_u8Data)
{
    while (!Get_Bit(UART->SR, TXE));  // Wait for TXE flag
    UART->DR = Copy_u8Data;  // Send data byte
    while (!Get_Bit(UART->SR, TC));  // Wait for TC flag (transmission complete)

    return E_OK;  // Success
}



/**
 * @brief Send an array of data via UART.
 *
 * Sends multiple bytes by waiting for the TXE and TC flags.
 *
 * @param Copy_u8Data Data array to be transmitted.
 * @param DataSize Size of the data array.
 * @return Std_ReturnType Transmission status (E_OK/E_NOT_OK).
 */
Std_ReturnType MUART_void_SendDataArray(u8 *Copy_u8Data, u16 DataSize)
{
    if (Copy_u8Data == NULL || DataSize == 0)
    {
        return E_INVALID_PARAMETER;  // Invalid input
    }

    for (u16 i = 0; i < DataSize; ++i)
    {
        while (!Get_Bit(UART->SR, TXE));  // Wait for TXE flag
        UART->DR = Copy_u8Data[i];  // Send data byte
        while (!Get_Bit(UART->SR, TC));  // Wait for TC flag (transmission complete)
    }

    return E_OK;  // Success
}

void MUART_voidSendSrting( u8 * Copy_u8String ){

	u8 LOC_u8Iterator = 0 ;

	while( Copy_u8String[ LOC_u8Iterator ] != '\0' ){

		MUART_void_SendData(  Copy_u8String[ LOC_u8Iterator ] );
		LOC_u8Iterator++;

	}

}

/**
 * @brief Receive a byte of data via UART.
 *
 * Waits for the RXNE flag and then reads the received byte.
 *
 * @return u8 Received data byte.
 */
u8 MUART_u8_RecieveData(void)
{
    while (!Get_Bit(UART->SR, RXNE));  // Wait for RXNE flag
    return (u8)UART->DR;  // Return received data byte
}

/******************************< End of File >******************************/
