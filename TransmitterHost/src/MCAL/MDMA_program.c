/****************************************************************/
/******* Author     : Ola Saadeh                *****************/
/******* Created on : Jan 4, 2025               *****************/
/******* File Name  : MDMA_program.c            *****************/
/****************************************************************/

/***********************< INCLUDES >*****************************/

/*****************************< LIB *****************************/
#include <LIB/Bit_Math.h>
#include <LIB/STD_Types.h>
#include <MCAL/MDMA/MDMA_interface.h>
#include <MCAL/MDMA/MDMA_private.h>
#include <MCAL/MUART/MUART_private.h>


// Global callback function pointer array
static void(*Copy_GLBPtr[8])(void);


/************************< Function Implementations ***************/
/**
 * @brief Initializes the DMA2 Stream 5 with necessary configurations.
 * Configures DMA2 for UART communication, including stream settings, interrupts, and FIFO thresholds.
 */
void MDMA2_void_Init(void)
{
    // Clear any previous settings
    DMA2->S[5].CR = 0;

    // Enable  Memory Increment Mode (MINC) and Circular Mode
    DMA2->S[5].CR |= (1 << MINC) | (1 << CIRC);
    DMA2->S[5].CR &= ~(MUSK3 << CHSEL); // Clear CHSEL[2:0]
    DMA2->S[5].CR |= (channel4 << CHSEL);  // Select Channel 4 (CHSEL = 100)

    // Set memory size (MSIZE) to byte (00)
    DMA2->S[5].CR &= ~(MUSK2 << MSIZE);
    DMA2->S[5].CR |= (0 << MSIZE);

    // Set peripheral size (PSIZE) to byte (00)
    DMA2->S[5].CR &= ~(MUSK2 << PSIZE);
    DMA2->S[5].CR |= (0 << PSIZE);

    // Enable Transfer Complete Interrupt (TCIE)
    DMA2->S[5].CR |= (1 << TCIE1);

    // Configure stream for fixed peripheral address (PINC = 0)
    DMA2->S[5].CR &= ~(1 << PINC);

    // Set transfer direction to peripheral-to-memory (DIR = 00)
    DMA2->S[5].CR &= ~(MUSK2 << DIR);
    DMA2->S[5].CR |= (0 << DIR);

    // Set FIFO threshold to 1/4 for early transfer
    DMA2->S[5].FCR |= FiFO_1_4;
}

/**
 * @brief Configures the DMA2 Stream 5 with the provided buffer and size.
 * @param buffer Pointer to the data buffer.
 * @param buffer_size Size of the data buffer.
 */
void MDMA2_SetStreamConfiguration(u8 *buffer, u16 buffer_size)
{
    DMA2->S[5].PAR = (u32)&UART->DR;   // Set peripheral address to UART Data Register
    DMA2->S[5].M0AR = (u32)buffer;    // Set memory address to buffer
    DMA2->S[5].NDTR = buffer_size;    // Set number of data to transfer
}

/**
 * @brief Registers a callback function for a specific DMA stream.
 * @param Copy_u8StreamID Stream identifier (0-7).
 * @param Copy_ptr Pointer to the callback function.
 */
void MDMA2_void_CallBack(u8 Copy_u8StreamID, void(*Copy_ptr)(void))
{
    Copy_GLBPtr[Copy_u8StreamID] = Copy_ptr;
}

/**
 * @brief DMA2 Stream 5 interrupt handler.
 * Checks if the transfer is complete and then calls the callback function.
 */
void DMA2_Stream5_IRQHandler(void)
{
    // Check if DMA transfer complete flag is set
    if (DMA2->HISR & (1 << TCIF5)) {
        Copy_GLBPtr[5]();  // Call the registered callback function
        DMA2->HIFCR |= (1 << CTCIF5);  // Clear the interrupt flag
    }
}

/**
 * @brief Disables a specific DMA stream.
 * @param Copy_u8StreamID Stream identifier (0-7).
 */
void MDMA2_disableStream(u8 Copy_u8StreamID)
{
    DMA2->S[Copy_u8StreamID].CR &= ~(1);  // Disable the stream
}

/**
 * @brief Enables a specific DMA stream.
 * @param Copy_u8StreamID Stream identifier (0-7).
 */
void MDMA2_enableStream(u8 Copy_u8StreamID)
{
    DMA2->S[Copy_u8StreamID].CR |= 1;  // Enable the stream
}

/******************************< End of File >******************************/
