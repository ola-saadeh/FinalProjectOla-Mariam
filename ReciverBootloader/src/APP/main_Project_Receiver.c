/****************************************************************/
/******* Author     : Ola & Mariam              *****************/
/******* Created on : Jan 4, 2025               *****************/
/******* File Name  : main_Project_Receiver.c   *****************/
/****************************************************************/
/**
 * @file main_Project_Receiver.c
 * @brief Receiver application to process received data and manage the device firmware.
 *        Includes handling of UART communication, flash memory operations, and CRC verification.
 *
 * @details
 * This program initializes the required peripherals and provides multiple functions to:
 * - Receive data via UART.
 * - Handle various command signals (e.g., erase sectors, verify CRC, etc.).
 * - Perform flash memory operations, such as erasing and writing data.
 * - Verify data integrity using CRC calculations.
 * - Manage the state of the receiver, including error handling and successful data processing.
 */

/*****************************< LIB *****************************/
#include <LIB/Bit_Math.h>
#include <LIB/STD_Types.h>

/*****************************< MCAL ****************************/
#include <MCAL/MEXTI/MEXTI_interface.h>
#include <MCAL/MFMI/MFMI_interface.h>
#include <MCAL/MGPIO/MGPIO_interface.h>
#include <MCAL/MNVIC/MNVIC_interface.h>
#include <MCAL/MRCC/MRCC_interface.h>
#include <MCAL/MSTK/MSTK_interface.h>
#include <MCAL/MUART/MUART_interface.h>

/*****************************< APP *****************************/
#include <APP/AHexParser/AHexParser_interface.h>
#include "APP/AHexParser/OUT.h"

/*********************< Macros Definitions***********************/
#define Sector2_BaseAdress 0x08008000
#define Sector3_BaseAdress 0x0800C000
#define Sector4_BaseAdress 0x08010000

/**********************<  GLOBAL VARIABLE ***********************/
/**
 * @brief Variable to store the high memory address.
 */
u32 HighAdd;

/**
 * @brief Defines a function pointer type for application calls.
 */
typedef void (*pf)(void);
pf App_Call;

/**
 * @brief Defines the maximum number of applications supported.
 */
#define MAX_APPS 3
u32 App_BaseAddresses[MAX_APPS] = {Sector2_BaseAdress, Sector3_BaseAdress,
                                   Sector4_BaseAdress};

/**
 * @brief Jumps to the specified application by setting up vector table and function pointer.
 * @param AppIndex Index of the application to jump to.
 */
void Jump_To_App(u8 AppIndex)
{
    if (AppIndex >= MAX_APPS)
    {
        // Notify invalid application index.
        MUART_voidSendSrting((u8 *)"Invalid Application Index");
        return;
    }

    // Set the vector table offset for the selected application
    VTOR = App_BaseAddresses[AppIndex];

    // Get MSP for the application
    u32 MSPAdress = *((volatile u32 *)(App_BaseAddresses[AppIndex]));

    __asm volatile("MSR MSP, %0" ::"r"(MSPAdress));

    // Set application call address
    u32 ResetHandlerAdress =
        *((volatile u32 *)(App_BaseAddresses[AppIndex] + 4));

    App_Call = (void *)ResetHandlerAdress;

    // Notify the user which application is being jumped to
    if (AppIndex == 0)
    {
        MUART_voidSendSrting((u8 *)"Jumping to Application 1");
    }
    else if (AppIndex == 2)
    {
        MUART_voidSendSrting((u8 *)"Jumping to Application 2");
    }
    // Call the selected application
    App_Call();
}

void Jump_To_App_0(void)
{
    Jump_To_App(0);
}

void Jump_To_App_2(void)
{
    Jump_To_App(2);
}
int main(void)
{
    // Temporarily disable interrupts for safe configuration
    __asm volatile("MSR PRIMASK, %0" ::"r"(1) : "memory");

    // Initialize system clock
    MRCC_void_Init();

    // Enable clocks for required peripherals
    MRCC_void_EnablePeriperalClock(AHB1_BUS, AHB1_GPIOA);
    MRCC_void_EnablePeriperalClock(AHB1_BUS, AHB1_GPIOB);
    MRCC_void_EnablePeriperalClock(APB2_BUS, APB2_USART1);
    MRCC_void_EnablePeriperalClock(APB2_BUS, APB2_SYSCFG);

    // UART initialization for communication
    MUART_void_Init();

    // Set GPIOA pin 9 (TX) and pin 10 (RX) for UART communication
    MGPIO_void_SetMode(PORTA, PIN9, Alternative_Function);
    MGPIO_void_SetAlternativeFunctionMode(PORTA, PIN9, AF7);
    MGPIO_void_SetMode(PORTA, PIN10, Alternative_Function);
    MGPIO_void_SetAlternativeFunctionMode(PORTA, PIN10, AF7);

    // Configure GPIO pins for(starting core app toggling led 13)
    MGPIO_void_SetMode(PORTA, PIN13, Output);
    MGPIO_void_SetOutputPinMode(PORTA, PIN13, PUSH_PULL, LOWSpeed);

    // Configure other GPIO pins (PA0 to PA7) as output for feedback while flashing
    int var = 0;
    for (var = 0; var < 8; var++)
    {
        MGPIO_void_SetMode(PORTA, var, Output);
        MGPIO_void_SetOutputPinMode(PORTA, var, PUSH_PULL, LOWSpeed);
    }

    // Configure GPIOB pins 0 and 1 as input for triggering application jump
    MGPIO_void_SetMode(PORTB, PIN0, Input); // For Jumping to Application 1
    MGPIO_void_SetInputPinMode(PORTB, PIN0, PULLUP);

    MGPIO_void_SetMode(PORTB, PIN1, Input); // For Jumping to Application 2
    MGPIO_void_SetInputPinMode(PORTB, PIN1, PULLUP);

    // Enable interrupt lines for EXTI (External Interrupts)
    MNVIC_void_Enable(6); // Enable interrupt for EXTI Line 0
    MNVIC_void_Enable(7); // Enable interrupt for EXTI Line 1

    // Configure the EXTI lines to be triggered by falling edges (button press)
    MEXTI_void_InterruptSetPort(EXTI_LineZero, EXTI_PORTB); // Line 0 on Port B
    MEXTI_void_InterruptSetPort(EXTI_LineOne, EXTI_PORTB);  // Line 1 on Port B

    MEXTI_void_InterruptSetTrigger(EXTI_LineZero, EXTI_Falling); // Trigger on falling edge for line 0
    MEXTI_void_InterruptSetTrigger(EXTI_LineOne, EXTI_Falling);  // Trigger on falling edge for line 1

    MEXTI0_void_CallbackFunc(Jump_To_App_0); // Callback for EXTI Line 0 (Jump to App 1)
    MEXTI1_void_CallbackFunc(Jump_To_App_2); // Callback for EXTI Line 1 (Jump to App 2)

    // Enable the EXTI lines to start listening for interrupts
    MEXTI_void_Enable(EXTI_LineZero);
    MEXTI_void_Enable(EXTI_LineOne);

    // Re-enable interrupts globally
    __asm volatile("MSR PRIMASK, %0" ::"r"(0) : "memory");

    /**
     * @brief Receiver function for receiving data from the transmitter.
     *
     * This function listens for data transmissions, processes control signals, and manages the flashing process
     * for different applications. It operates in the following steps:
     * - First, it checks for the 'm' signal to initiate communication and enter "m mode."
     * - Then, the receiver listens for control data to decide which application to flash or process.
     * - If an application index (1, 2, or 3) is received, it erases the corresponding sector and flashes the application.
     * - The function also handles CRC validation for the received data to ensure data integrity.
     * - In case of specific control signals ('e', 'z', 'v'), the receiver can erase sectors, display device information, or handle invalid commands.
     * - After completing the flashing process, the system performs a visual indication using GPIO pins to indicate success.
     */
    u8 mode = MUART_u8_RecieveData();
    if (mode == 'm')
    {
        while (1)
        {

            // Disable interrupts on receiver to ensure no interference during the process
            MEXTI_void_DisableInterrupts();

            // Listen for control data to decide the next operation
            u8 ctrlDataListen = MUART_u8_RecieveData();

            if (ctrlDataListen == 's')
            {
                // Break the loop if 's' is received (stop listening)
                break;
            }

            if (ctrlDataListen >= '1' && ctrlDataListen <= '3')
            {                                       // SEND '1' This means flash app1 -> sector2 App_BaseAddresses[0]
                u8 AppIndex = ctrlDataListen - '1'; // Get the application index
                MFMI_voidSectorErase(AppIndex + 2); // Erase the corresponding sector based on the application index

                u8 length = 0;
                u8 FirstAddressByte, SecondAddressByte;
                u32 Address = 0;

                while (1) // Keep receiving records until 'f' is received
                {
                    u8 ctrlDataRec = MUART_u8_RecieveData();

                    if (ctrlDataRec == 'f') // End of file or transmission signal If 'f' is received, finish the flashing process
                    {
                        // Send an acknowledgment to end of flashing
                        MUART_void_SendData(AppIndex == 0 ? '.' : ',');
                        MUART_voidSendSrting(
                            (u8 *)(AppIndex == 0 ? "Flashing Application 1" : "Flashing Application 2"));
                        break; // Exit the loop once 'f' is received
                    }
                    else if (ctrlDataRec == 'h') // Handle high address byte
                    {
                        u8 FirstHAddressByte = MUART_u8_RecieveData();
                        u8 SecondHAddressByte = MUART_u8_RecieveData();
                        HighAdd = ((FirstHAddressByte << 8) | (SecondHAddressByte)) << 16;
                    }
                    else if (ctrlDataRec == 'p') // Handle program data
                    {
                        length = MUART_u8_RecieveData(); // Get data length
                        FirstAddressByte = MUART_u8_RecieveData();
                        SecondAddressByte = MUART_u8_RecieveData();
                        Address = (HighAdd) | (FirstAddressByte << 8) | SecondAddressByte;

                        u8 FirstDigitByte = 0;
                        u8 SecondDigitByte = 0;
                        u16 Data[8] = {0}; // Array to store received data
                        u8 i = 0;

                        for (i = 0; i < (length / 2); i++)
                        {
                            FirstDigitByte = MUART_u8_RecieveData();
                            SecondDigitByte = MUART_u8_RecieveData();
                            Data[i] = (SecondDigitByte << 8) | FirstDigitByte;
                            MGPIO_void_SetPinValue(PORTA, i, Data[i]); // Set GPIO pins with data just for indicate what flashing
                        }
                        MFMI_voidFlashWrite(Address, Data, (length / 2)); // Write data to flash
                    }
                }
            }
            else if (ctrlDataListen == 'c' || ctrlDataListen == 'q') // Handle CRC validation for applications 1 & 2
            {
                {
                    u8 crcflag = 0;
                    int var = 0;
                    u8 size_high = MUART_u8_RecieveData();
                    u8 size_low = MUART_u8_RecieveData();
                    int size = (size_high << 8) | size_low;
                    for (var = 0; var < size; ++var)
                    {

                        u8 sum = 0;
                        u8 recordLength = MUART_u8_RecieveData();
                        for (u8 i = 1; i < recordLength - 2; i += 2)
                        {
                            u8 num = MUART_u8_RecieveData();
                            sum += num;
                        }
                        u8 CalculateCRC = (~sum + 1);
                        u8 CRC = MUART_u8_RecieveData();
                        if (CRC != CalculateCRC)
                        {
                            crcflag = 1;
                        }
                    }

                    if ((ctrlDataListen == 'c') && (crcflag == 1))
                    {
                        MUART_voidSendSrting((u8 *)"Application 1 CRC Fault");
                    }
                    else if ((ctrlDataListen == 'c') && (crcflag == 0))
                    {
                        MUART_voidSendSrting(
                            (u8 *)"Application 1 CRC Correct");
                    }
                    else if ((ctrlDataListen == 'q') && (crcflag == 1))
                    {
                        MUART_voidSendSrting((u8 *)"Application 2 CRC Fault");
                    }
                    else if ((ctrlDataListen == 'q') && (crcflag == 0))
                    {
                        MUART_voidSendSrting(
                            (u8 *)"Application 2 CRC Correct");
                    }
                }
            }
            else if (ctrlDataListen == 'e') // Erase sector 2 and reflash empty project
            {

                // In Proteus simulation, the sector erase operation may not work correctly, so we opted for the following solution:
                // We perform the sector erase on the actual hardware using MFMI_voidSectorErase(2).
                MFMI_voidSectorErase(sector2); // This function erases sector 2 of the flash memory

                // After erasing, we reflash an empty project (or empty record) in the same location.
                int size = sizeof(arr2) / sizeof(arr2[0]); // Calculate size of the empty project array
                for (u16 i = 0; i < size; i++)             // Parse and transmit each record of the empty project
                {
                    AHexParser_voidParseRecord(arr2[i]);
                }
                // Send a confirmation message indicating that sector 2 was erased
                MUART_voidSendSrting((u8 *)"erase sector 2 ");
            }
            else if (ctrlDataListen == 'z')
            { // Erase sector 4 and reflash empty project

                MFMI_voidSectorErase(sector4);
                // arr is an array of records for empty project on sector 4
                int size = sizeof(arr) / sizeof(arr[0]);
                for (u16 i = 0; i < size; i++)
                {
                    AHexParser_voidParseRecord(arr[i]);
                }
                // Send confirmation message
                MUART_voidSendSrting((u8 *)"erase sector 4 ");
            }
            else if (ctrlDataListen == 'v')
            { // Return device version
                MUART_voidSendSrting((u8 *)"CORTEX M4 STM32F401CC ");
            }
            else
            { // Handle other cases, possibly invalid or unexpected data
                MUART_voidSendSrting((u8 *)"Invalid data received");
            }
        }
    }
    // after finish m mode (connect mode with transmitter) enable interrupt on receiver
    MEXTI_void_EnableInterrupts();
    // after finish m mode go to core app mode its blinking pin13
    while (1)
    {
        MGPIO_void_SetPinValue(PORTA, PIN13, High);
        MSTK_voidDelayms(2000);
        MGPIO_void_SetPinValue(PORTA, PIN13, LOW);
        MSTK_voidDelayms(2000);
    }

    return 0;
}
