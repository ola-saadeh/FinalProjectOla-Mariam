/****************************************************************/
/******* Author     : Ola Saadeh                *****************/
/******* Created on : Jan 4, 2025               *****************/
/******* File Name  : MDMA_interface.h          *****************/
/****************************************************************/


#ifndef MDMA_INTERFACE_H_
#define MDMA_INTERFACE_H_

/* DMA Data Size Enum */
typedef enum
{
	byte=0,     /**< Data size: Byte (8 bits) */
	half_word,  /**< Data size: Half Word (16 bits) */
	word        /**< Data size: Word (32 bits) */
}Size;

/* DMA FIFO Threshold Enum */
typedef enum
{
	FiFO_1_4=0,
	FiFO_1_2,
	FiFO_3_4,
	Full_Fifo
}Thresh_hold;

typedef enum {
	channel0 = 0,
	channel1,
	channel2,
	channel3,
	channel4,
	channel5,
	channel6,
	channel7
} Channel;


/***********************< FUNCTION PROTOTYPES >*****************/

/**
 * @brief Initialize DMA2 peripheral.
 */
void MDMA2_void_Init(void);



/**
 * @brief Configure a DMA stream with the provided buffer and size.
 *
 * @param buffer Pointer to the buffer to transfer data.
 * @param buffer_size Size of the buffer in bytes.
 */
void MDMA2_SetStreamConfiguration(u8 *buffer, u16 buffer_size);



/**
 * @brief Set a callback function for a specific DMA stream.
 *
 * @param Copy_u8StreamID Stream ID to assign the callback.
 * @param Copy_ptr Pointer to the callback function.
 */
void MDMA2_void_CallBack(u8 Copy_u8StreamID,void(*Copy_ptr)(void));



/**
 * @brief Enable a specific DMA stream.
 *
 * @param Copy_u8StreamID Stream ID to enable.
 */
void MDMA2_enableStream(u8 Copy_u8StreamID);



/**
 * @brief Disable a specific DMA stream.
 *
 * @param Copy_u8StreamID Stream ID to disable.
 */
void MDMA2_disableStream(u8 Copy_u8StreamID);





#endif /* MDMA_INTERFACE_H_ */
