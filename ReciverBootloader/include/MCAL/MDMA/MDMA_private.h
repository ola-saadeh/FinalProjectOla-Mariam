/****************************************************************/
/******* Author     : Ola Saadeh                *****************/
/******* Created on : Jan 4, 2025               *****************/
/******* File Name  : MDMA_private.h            *****************/
/****************************************************************/

#ifndef MDMA_PRIVATE_H_
#define MDMA_PRIVATE_H_

/* Base addresses for DMA1 and DMA2 */
#define MDMA1_BASE_ADDRESS (0x40026000)   /**< Base address for DMA1 */
#define MDMA2_BASE_ADDRESS (0x40026400)   /**< Base address for DMA2 */

/* DMA Stream Register structure */
typedef struct
{
    u32 CR;       /**< Control Register */
    u32 NDTR;     /**< Number of Data to Transfer Register */
    u32 PAR;      /**< Peripheral Address Register */
    u32 M0AR;     /**< Memory Address Register (0) */
    u32 M1AR;     /**< Memory Address Register (1) */
    u32 FCR;      /**< FIFO Control Register */
} DMA_stream_t;

/* DMA Register structure that contains 8 streams */
typedef struct
{
    u32 LISR;      /**< Low Interrupt Status Register */
    u32 HISR;      /**< High Interrupt Status Register */
    u32 LIFCR;     /**< Low Interrupt Flag Clear Register */
    u32 HIFCR;     /**< High Interrupt Flag Clear Register */
    DMA_stream_t S[8];  /**< DMA Streams (0-7) */
} DMA_t;

/* DMA1 and DMA2 are volatile pointers to DMA_t structures */
#define DMA1 ((volatile DMA_t*)MDMA1_BASE_ADDRESS)  /**< DMA1 pointer */
#define DMA2 ((volatile DMA_t*)MDMA2_BASE_ADDRESS)  /**< DMA2 pointer */

/* Bitfield definitions for DMA stream control register (CR) */
#define TCIE1    4     /**< Transfer Complete Interrupt Enable (TCIE) */
#define DIR      6     /**< Data Transfer Direction (DIR) */
#define CIRC     8     /**< Circular Mode (CIRC) */
#define PINC     9     /**< Peripheral Increment Mode (PINC) */
#define MINC     10    /**< Memory Increment Mode (MINC) */
#define PSIZE    11    /**< Peripheral Data Size (PSIZE) */
#define MSIZE    13    /**< Memory Data Size (MSIZE) */
#define CHSEL    25    /**< Channel Selection (CHSEL) */

/* DMA interrupt flags */
#define TCIF5    11    /**< Stream 5 transfer complete interrupt flag  */
#define CTCIF5   11    /**< Stream 5 clear transfer complete interrupt flag  */

/* Mask definitions for bit manipulation */
#define MUSK2   0x03   /**< Mask 2 bit (MUSK2) */
#define MUSK3   0x07   /**< Mask 3 bit (MUSK3) */

#endif /* MDMA_PRIVATE_H_ */
