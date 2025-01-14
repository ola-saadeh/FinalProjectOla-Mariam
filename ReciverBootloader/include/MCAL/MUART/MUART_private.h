/****************************************************************/
/******* Author     : Ola Saadeh                *****************/
/******* Created on : Jan 4, 2025               *****************/
/******* File Name  : MUART_private.h           *****************/
/****************************************************************/


#ifndef MUART_PRIVATE_H_
#define MUART_PRIVATE_H_

/**
 * @brief USART base address.
 */
#define UART1_BASE_Adress (0x40011000)

/**
 * @brief USART control register 1 (USART_CR1) bit definitions.
 */
typedef struct
{
	u32 SBK :1;        /**< Send Break */
	u32 RWU :1;        /**< Receiver Wakeup */
	u32 RE :1;         /**< Receiver Enable */
	u32 TE :1;         /**< Transmitter Enable */
	u32 IDLEIE :1;     /**< IDLE Interrupt Enable */
	u32 RXNEIE:1;      /**< RXNE Interrupt Enable */
	u32 TCIE :1;       /**< Transmission Complete Interrupt Enable */
	u32 TXEIE :1;      /**< TXE Interrupt Enable */
	u32 PEIE:1;        /**< Parity Error Interrupt Enable */
	u32 PS :1;         /**< Parity Selection */
	u32 PCE:1;         /**< Parity Control Enable */
	u32 WAKE:1;        /**< Wakeup Method */
	u32 M:1;           /**< Word Length */
	u32 UE:1;          /**< USART Enable */
	u32 Reserved1:1;   /**< Reserved bit */
	u32 OVER8:1;       /**< Oversampling Mode */
	u32 Reserved2:16;  /**< Reserved bits */
}MUART_CR1;

/**
 * @brief Structure representing USART registers.
 */
typedef struct
{
 u32 SR;        /**< Status register */
 u32 DR;        /**< Data register */
 u32 BRR;       /**< Baud rate register */
 MUART_CR1 CR1; /**< Control register 1 */
 u32 CR2;       /**< Control register 2 */
 u32 CR3;       /**< Control register 3 */
 u32 GTPR;      /**< Guard time and prescaler register */
}MUART_t;

/**
 * @brief USART1 pointer.
 */
#define UART ((volatile MUART_t*)UART1_BASE_Adress)

#define TXE   7    /**< Transmit data register empty */
#define TC    6    /**< Transmission complete        */
#define RXNE  5    /**< Read data register not empty */



#endif /* MUART_PRIVATE_H_ */
