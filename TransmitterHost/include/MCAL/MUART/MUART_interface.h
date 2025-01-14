/****************************************************************/
/******* Author     : Ola Saadeh                *****************/
/******* Created on : Dec 19, 2024              *****************/
/******* File Name  : MUART_interface.h         *****************/
/****************************************************************/

#ifndef MUART_INTERFACE_H_
#define MUART_INTERFACE_H_

/***********************< FUNCTION PROTOTYPES >*****************/

/**
 * @brief Initialize the UART with the configuration settings.
 * @return Std_ReturnType Initialization status (E_OK/E_NOT_OK).
 */
Std_ReturnType MUART_void_Init(void);

/**
 * @brief Send a byte via UART.
 * @param Copy_u8Data The data byte to be sent.
 * @return Std_ReturnType Status of the operation (E_OK/E_NOT_OK).
 */
Std_ReturnType MUART_void_SendData(u8 Copy_u8Data);

/**
 * @brief Send an array of data via UART.
 * @param Copy_u8Data Pointer to the data array.
 * @param DataSize Size of the data array.
 * @return Std_ReturnType Status of the operation (E_OK/E_NOT_OK).
 */
Std_ReturnType MUART_void_SendDataArray(u8 *Copy_u8Data, u16 DataSize);



void MUART_voidSendSrting( u8 * Copy_u8String );

/**
 * @brief Receive a byte via UART.
 * @return u8 The received byte.
 */
u8 MUART_u8_RecieveData(void);

#endif /* MUART_INTERFACE_H_ */
