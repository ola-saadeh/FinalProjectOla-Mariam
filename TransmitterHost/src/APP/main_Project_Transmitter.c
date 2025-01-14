/****************************************************************/
/******* Author     : Ola & Mariam              *****************/
/******* Created on : Jan 4, 2025               *****************/
/******* File Name  : main_Project_Transmitter.c*****************/
/****************************************************************/
/**
 * @file main_Project_Transmitter.c
 * @brief Transmitter application to process and send data records using UART communication.
 *        Includes parsing of Intel HEX records and CRC verification.
 *
 * @details
 * This program initializes necessary peripherals and provides multiple functions to:
 * - Parse Intel HEX records.
 * - Calculate CRC for the records.
 * - Transmit data using UART.
 * - Perform specific tasks such as erasing data or verifying CRC.
 * - Manage connection state for data transfer.
 */

/*****************************< LIB *****************************/
#include "LIB/Bit_Math.h"
#include "LIB/STD_Types.h"

/*****************************< MCAL ****************************/
#include "MCAL/MEXTI/MEXTI_interface.h"
#include "MCAL/MFMI/MFMI_interface.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MNVIC/MNVIC_interface.h"
#include "MCAL/MRCC/MRCC_interface.h"
#include "MCAL/MSTK/MSTK_interface.h"
#include "MCAL/MUART/MUART_interface.h"

/*****************************< APP *****************************/
#include "APP/AHexParser/AHexParser_interface.h"
#include "APP/AHexParser/OUT.h"

/**********************<  GLOBAL VARIABLE ***********************/
/**
 * @brief Flags to manage the state of transmission.
 */
volatile u8 firstFlag = 0;

/***************< Function Implementations**********************/
/**
 * @brief Calculates the CRC for an Intel HEX record and transmits the calculated CRC.
 *
 * @param[in] record The Intel HEX record as a string.
 */
void Calculate_IntelHex_CRC(const char *record)
{
    u8 byte = 0;
    // Extract the high and low nibbles of the number of data from the record
    u8 CC_High = AHexParser_u8ASCIToHex(record[1]);
    u8 CC_Low = AHexParser_u8ASCIToHex(record[2]);
    u8 CC_Value = (CC_High << 4) | (CC_Low); // Combine the high and low nibbles to get the number of data value

    u8 recordLength = 0;
    // Calculate the length of the Intel HEX record (excluding the null terminator and newline)
    while (record[recordLength] != '\0' && record[recordLength] != '\n')
    {
        recordLength++;
    }
    // Send record length to bootloader receiver
    MUART_void_SendData(recordLength);

    // Transmit the bytes from the record (excluding the first characters and last 2 CRC characters)
    for (u8 i = 1; i < recordLength - 2; i += 2)
    {
        // Convert each pair of characters to a byte (high nibble and low nibble)
        u8 highNibble = AHexParser_u8ASCIToHex(record[i]);
        u8 lowNibble = AHexParser_u8ASCIToHex(record[i + 1]);

        // Combine high and low nibbles to form a byte
        byte = (highNibble << 4) | lowNibble;

        // Transmit the byte to bootloader receiver
        MUART_void_SendData(byte);
    }

    // Extract the CRC from the record
    u8 CRC_High = AHexParser_u8ASCIToHex(record[9 + (CC_Value * 2)]); // Extract the high nibble of CRC
    u8 CRC_Low = AHexParser_u8ASCIToHex(record[10 + (CC_Value * 2)]); // Extract the low nibble of CRC

    u8 CRC = (CRC_High << 4) | CRC_Low; // Combine the high and low nibbles to form the CRC byte

    // Send the CRC byte to bootloader receiver
    MUART_void_SendData(CRC);
}

/**
 * @brief Parses a record and performs actions based on the type of record.
 *
 * @param[in] Record The Intel HEX record as a string.
 */
void USART_ParseRecord(const char *Record)
{
    // Parse the type of record based on the 9th character (index 8) of the record
    u8 Local = AHexParser_u8ASCIToHex(Record[8]);

    switch (Local)
    {
    case 0:
    {
        // Case 0: Process the record by sending parsed data
        MUART_void_SendData('p'); // Indicating that we are processing case 0

        // Extract the number of data bytes (CC_Value) from the record
        u8 CC_High = AHexParser_u8ASCIToHex(Record[1]);
        u8 CC_Low = AHexParser_u8ASCIToHex(Record[2]);
        u8 CC_Value = (CC_High << 4) | (CC_Low);
        MUART_void_SendData(CC_Value);

        // Extract the 16-bit address (first two address bytes) and send them
        u8 Address_0 = AHexParser_u8ASCIToHex(Record[3]);
        u8 Address_1 = AHexParser_u8ASCIToHex(Record[4]);
        u8 FirstAddressByte = (Address_0 << 4) | (Address_1);
        MUART_void_SendData(FirstAddressByte);

        // Extract the second two address bytes and send them
        u8 Address_2 = AHexParser_u8ASCIToHex(Record[5]);
        u8 Address_3 = AHexParser_u8ASCIToHex(Record[6]);
        u8 SecondAddressByte = (Address_2 << 4) | (Address_3);
        MUART_void_SendData(SecondAddressByte);

        // Loop through and send the data bytes (based on CC_Value)
        u8 Digit_0 = 0, Digit_1 = 0, Digit_2 = 0, Digit_3 = 0;
        u8 i = 0;
        for (i = 0; i < (CC_Value / 2); i++)
        {
            // Extract and send the first pair of digits
            Digit_0 = AHexParser_u8ASCIToHex(Record[9 + (i * 4)]);
            Digit_1 = AHexParser_u8ASCIToHex(Record[10 + (i * 4)]);
            u8 FirstDigitByte = (Digit_0 << 4) | (Digit_1);
            MUART_void_SendData(FirstDigitByte);

            // Extract and send the second pair of digits
            Digit_2 = AHexParser_u8ASCIToHex(Record[11 + (i * 4)]);
            Digit_3 = AHexParser_u8ASCIToHex(Record[12 + (i * 4)]);
            u8 SecondDigitByte = (Digit_2 << 4) | (Digit_3);
            MUART_void_SendData(SecondDigitByte);
        }
    }

    break;
    case 4:
        // Case 4: Handle sending high address bytes
        MUART_void_SendData('h'); // Indicating that we are processing case 4

        // Extract and send the first pair of high address bytes
        u8 HighAddress1 = AHexParser_u8ASCIToHex(Record[9]);
        u8 HighAddress2 = AHexParser_u8ASCIToHex(Record[10]);
        u8 FirstHAddressByte = (HighAddress1 << 4) | (HighAddress2);
        MUART_void_SendData(FirstHAddressByte);

        // Extract and send the second pair of high address bytes
        u8 HighAddress3 = AHexParser_u8ASCIToHex(Record[11]);
        u8 HighAddress4 = AHexParser_u8ASCIToHex(Record[12]);
        u8 SecondHAddressByte = (HighAddress3 << 4) | (HighAddress4);
        MUART_void_SendData(SecondHAddressByte);
        break;
    case 1:
        // Case 1: End of file - send 'f'
        MUART_void_SendData('f');

        // Check for specific characters to perform actions based on any function flashed
        // If '.' is received, indicate "app1" by setting PIN0 high
        if (MUART_u8_RecieveData() == '.')
        {
            MGPIO_void_SetPinValue(PORTB, PIN0, High); // Set PIN0 high to indicate "app1" flashing in the receiver bootloader
        }
        // If ',' is received, indicate "app2" by setting PIN1 high
        else if (MUART_u8_RecieveData() == ',')
        {
            MGPIO_void_SetPinValue(PORTB, PIN1, High); // Set PIN1 high to indicate "app2" flashing in the receiver bootloader
        }
        break;
    default:
        // Default case: send 'o' to indicate an unknown record type
        MUART_void_SendData('o');
        break;
    }
}

/**
 * @brief Transmitter function for transmitting the first application.
 *
 * This function handles the transmission of the hex data for the first application by performing the following steps:
 * - Initially, it checks the flag `firstFlag`. If it's the first transmission, it sends 'm' to indicate
 *   the start of the process and switches the system into "m mode", where the transmitter and receiver
 *   communicate through the bootloader, allowing the transmitter to respond to any interrupt indicating
 *   a command to send. It also sets `firstFlag` to 1 to prevent sending 'm' again during future transmissions
 *   triggered by interrupts.
 * - Then, it disables external interrupts to avoid any interference during the transmission process.
 * - After that, it sends '1' to signal that the first application is being transmitted.
 * - It iterates through the records in the array `arr`, calling `USART_ParseRecord` to transmit each Intel HEX record.
 * - Finally, it re-enables external interrupts to allow processing of any external interrupts that may occur after the transmission.
 */
void tranmitter1(void)
{
    // Check if it's the first transmission attempt
    if (firstFlag == 0)
    {
        // Send 'm' to indicate the start of transmission and enter "m mode"
        MUART_void_SendData('m');
        // Set firstFlag to 1 to prevent sending 'm' again in future transmissions
        firstFlag = 1;
    }
    // Disable external interrupts to ensure no interference during transmission
    MEXTI_void_DisableInterrupts();
    // Send '1' to indicate that the first application is being transmitted
    MUART_void_SendData('1');
    // Iterate over the records in the array and transmit them one by one
    u8 var = 0;
    int size = sizeof(arr) / sizeof(arr[0]);
    for (var = 0; var < size; ++var)
    {
        // Call USART_ParseRecord to send each Intel HEX record
        USART_ParseRecord(arr[var]);
    }
    // Re-enable external interrupts after the transmission is complete

    MEXTI_void_EnableInterrupts();
}

/**
 * @brief Transmitter function for transmitting the second application.
 *
 * This function handles the transmission of hex data for the second application by following the step
 *  as above explain but send '3' signal
 */
void tranmitter2(void)
{
    if (firstFlag == 0)
    {
        // If it's the first transmission, send 'm' to signal bootloader mode
        // and prevent sending 'm' again by setting firstFlag to 1
        MUART_void_SendData('m');
        firstFlag = 1;
    }
    // Disable external interrupts to prevent interruptions during the transmission
    MEXTI_void_DisableInterrupts();

    // Send '3' to indicate the start of transmitting the second application
    MUART_void_SendData('3');

    // Get the size of the array arr2
    int var = 0;
    int size = sizeof(arr2) / sizeof(arr2[0]);
    // Iterate through each record in arr2 and send it using USART_ParseRecord
    for (var = 0; var < size; ++var)
    {
        USART_ParseRecord(arr2[var]);
    }
    // Re-enable external interrupts after transmission
    MEXTI_void_EnableInterrupts();
}

/**
 * @brief Erase function for transmitting 'e' to erase sector 2 where application 1 was flashed.
 *
 * This function is responsible for erasing sector 2, which contains application 1. The steps are as above explained.
 */
void erase2(void)
{
    if (firstFlag == 0)
    {
        // If it's the first transmission, send 'm' to signal bootloader mode
        // and prevent sending 'm' again by setting firstFlag to 1
        MUART_void_SendData('m');
        firstFlag = 1;
    }
    // Disable external interrupts to avoid interruptions during the erase operation
    MEXTI_void_DisableInterrupts();

    // Send 'e' to signal that sector 2 should be erased
    MUART_void_SendData('e');

    // Re-enable external interrupts after sending the erase command
    MEXTI_void_EnableInterrupts();
}

/**
 * @brief Erase function for transmitting 'z' to erase sector 4 where application 2 was flashed.
 *
 * This function is responsible for erasing sector 4, which contains application 2. The steps are as above explained.
 */
void erase4(void)
{
    if (firstFlag == 0)
    {
        // If it's the first transmission, send 'm' to signal bootloader mode
        // and prevent sending 'm' again by setting firstFlag to 1
        MUART_void_SendData('m');
        firstFlag = 1;
    }
    // Disable external interrupts to avoid interruptions during the erase operation
    MEXTI_void_DisableInterrupts();

    // Send 'z' to signal that sector 4 should be erased
    MUART_void_SendData('z');

    // Re-enable external interrupts after sending the erase command
    MEXTI_void_EnableInterrupts();
}
/**
 * @brief Get version function transmitting 'v' to retrieve the microcontroller's version.
 *
 * This function handles the process of requesting the microcontroller's version. The steps are as above explained.
 */
void get_version(void)
{
    if (firstFlag == 0)
    {
        // If it's the first transmission, send 'm' to indicate bootloader mode
        // and set firstFlag to 1 to avoid sending 'm' again in subsequent transmissions
        MUART_void_SendData('m');
        firstFlag = 1;
    }
    // Disable external interrupts to prevent interference during the transmission
    MEXTI_void_DisableInterrupts();

    // Send 'v' to request the microcontroller's version
    MUART_void_SendData('v');

    // Re-enable external interrupts after sending the version request
    MEXTI_void_EnableInterrupts();
}

/**
 * @brief Verify CRC function for first application.
 *
 * This function handles the process of verifying the CRC for the first application.
 * The steps performed are:
 * - If it's the first transmission, it sends 'm' to indicate bootloader mode.
 * - It disables external interrupts to prevent interference during the transmission process.
 * - Sends 'c' to signal the start of CRC verification.
 * - Sends the size of the application (in two bytes: high byte and low byte).
 * - Iterates through each record in the array `arr`, calling `Calculate_IntelHex_CRC` to calculate and verify the CRC for each record.
 * - Re-enables external interrupts after CRC verification is complete.
 */
void verify_crc1(void)
{
    if (firstFlag == 0)
    {
        // Send 'm' to indicate bootloader mode on first transmission
        // Set firstFlag to 1 to avoid sending 'm' again in subsequent transmissions
        MUART_void_SendData('m');
        firstFlag = 1;
    }
    // Disable external interrupts to prevent interference during CRC verification
    MEXTI_void_DisableInterrupts();

    // Send 'c' to indicate that CRC verification
    MUART_void_SendData('c');

    // Send the size of the application in two bytes (high byte and low byte)
    int var = 0;
    int size = sizeof(arr) / sizeof(arr[0]);
    MUART_void_SendData((u8)(size >> 8));   // Send high byte of size
    MUART_void_SendData((u8)(size & 0xFF)); // Send low byte of size

    // Calculate the CRC for each record in the array
    for (var = 0; var < size; ++var)
    {
        Calculate_IntelHex_CRC(arr[var]);
    }

    // Re-enable external interrupts after CRC verification
    MEXTI_void_EnableInterrupts();
}

/**
 * @brief Verify CRC function for second application.
 *
 * This function handles the process of verifying the CRC for the second application.
 * The steps performed are as above explained but sends 'q' to signal the start of CRC verification for the second application.
 */
void verify_crc2(void)
{
    if (firstFlag == 0)
    {
        // Send 'm' to indicate bootloader mode on first transmission
        // Set firstFlag to 1 to avoid sending 'm' again in subsequent transmissions
        MUART_void_SendData('m');
        firstFlag = 1;
    }
    // Disable external interrupts to prevent interference during CRC verification
    MEXTI_void_DisableInterrupts();

    // Send 'q' to indicate that CRC verification for the second application
    MUART_void_SendData('q');

    // Send the size of the application in two bytes (high byte and low byte)
    int var = 0;
    int size = sizeof(arr2) / sizeof(arr2[0]);
    MUART_void_SendData((u8)(size >> 8));   // Send high byte of size
    MUART_void_SendData((u8)(size & 0xFF)); // Send low byte of size

    // Calculate the CRC for each record in the array
    for (var = 0; var < size; ++var)
    {
        Calculate_IntelHex_CRC(arr2[var]);
    }

    // Re-enable external interrupts after CRC verification
    MEXTI_void_EnableInterrupts();
}

/**
 * @brief Stop connection function.
 *
 * This function handles the process of stopping the communication between the transmitter and receiver.
 * - Sends 's' to indicate that the connection should be stopped.
 * - Disables external interrupts to prevent any interrupts from the transmitter after stopping.
 */
void stop_conection(void)
{
    // Send 's' to indicate stopping the connection
    MUART_void_SendData('s');

    // Disable external interrupts to prevent interrupts from the transmitter
    MEXTI_void_DisableInterrupts();
}

/**
 * @brief Main function to initialize peripherals and manage the main loop.
 *
 * This function initializes the system and peripherals required for the application. It:
 * - Configures system clocks and GPIOs.
 * - Initializes UART for communication.
 * - Sets up external interrupts with appropriate triggers and callback functions.
 * - Includes a mechanism to allow entering 'm' mode within a specific timeout.
 * If no mode change occurs, it transitions to the core application by sending 'x' and disabling interrupts.
 */
int main(void)
{
    // Temporarily disable interrupts for safe configuration
    __asm volatile("MSR PRIMASK, %0" ::"r"(1) : "memory");

    // Initialize system clocks and SysTick
    MRCC_void_Init(); // Initialize the RCC (Reset and Clock Control)
    MSTK_voidInit();  // Initialize the SysTick Timer for delay functions

    // Enable clocks for required peripherals
    MRCC_void_EnablePeriperalClock(AHB1_BUS, AHB1_GPIOA);
    MRCC_void_EnablePeriperalClock(AHB1_BUS, AHB1_GPIOB);
    MRCC_void_EnablePeriperalClock(AHB1_BUS, AHB1_GPIOC);
    MRCC_void_EnablePeriperalClock(APB2_BUS, APB2_USART1);
    MRCC_void_EnablePeriperalClock(APB2_BUS, APB2_SYSCFG);

    // UART initialization for communication
    MUART_void_Init();

    // Configure GPIO pins for output (indicators for flashing app1 & app2)
    MGPIO_void_SetMode(PORTB, PIN0, Output);
    MGPIO_void_SetOutputPinMode(PORTB, PIN0, PUSH_PULL, LOWSpeed);
    MGPIO_void_SetMode(PORTB, PIN1, Output);
    MGPIO_void_SetOutputPinMode(PORTB, PIN1, PUSH_PULL, LOWSpeed);

    // Configure input pins with pull-up resistors for 'finish' button
    MGPIO_void_SetMode(PORTC, PIN13, Input);
    MGPIO_void_SetInputPinMode(PORTC, PIN13, PULLUP);

    // Configure input pins (PORTA) with pull-up resistors for bootloader commands
    u8 pin = 0;
    for (pin = PIN0; pin <= PIN6; pin++)
    {
        MGPIO_void_SetMode(PORTA, pin, Input);
        MGPIO_void_SetInputPinMode(PORTA, pin, PULLUP);
    }

    // Configure USART pins (TX and RX) with AF7 mode
    MGPIO_void_SetMode(PORTA, PIN9, Alternative_Function);
    MGPIO_void_SetAlternativeFunctionMode(PORTA, PIN9, AF7); // TX

    MGPIO_void_SetMode(PORTA, PIN10, Alternative_Function);
    MGPIO_void_SetAlternativeFunctionMode(PORTA, PIN10, AF7); // RX

    // Enable external interrupt lines for pins 0-6 and 13
    MNVIC_void_Enable(6);  // EXT0 for pin0
    MNVIC_void_Enable(7);  // EXT1 for pin1
    MNVIC_void_Enable(8);  // EXT2 for pin2
    MNVIC_void_Enable(9);  // EXT3 for pin3
    MNVIC_void_Enable(10); // EXT4 for pin4
    MNVIC_void_Enable(23); // EXT5-9 for pin5 and pin6
    MNVIC_void_Enable(40); // EXT13 PC13

    // Configure EXTI lines and triggers
    for (int line = EXTI_LineZero; line <= EXTI_LineSix; line++)
    {
        MEXTI_void_InterruptSetPort(line, EXTI_PORTA);
        MEXTI_void_InterruptSetTrigger(line, EXTI_Falling);
    }
    MEXTI_void_InterruptSetPort(EXTI_LineThirteen, EXTI_PORTC);
    MEXTI_void_InterruptSetTrigger(EXTI_LineThirteen, EXTI_Falling);

    // Assign callback functions for EXTI lines
    MEXTI0_void_CallbackFunc(tranmitter1);
    MEXTI1_void_CallbackFunc(tranmitter2);
    MEXTI2_void_CallbackFunc(erase2);
    MEXTI3_void_CallbackFunc(erase4);
    MEXTI4_void_CallbackFunc(get_version);
    MEXTI5_void_CallbackFunc(verify_crc1);
    MEXTI6_void_CallbackFunc(verify_crc2);
    MEXTI13_void_CallbackFunc(stop_conection);

    // Enable the EXTI lines
    for (int line = EXTI_LineZero; line <= EXTI_LineSix; line++)
    {
        MEXTI_void_Enable(line);
    }
    MEXTI_void_Enable(EXTI_LineThirteen);

    // Re-enable interrupts after configuration
    __asm volatile("MSR PRIMASK, %0" ::"r"(0) : "memory");

    /* Wait for a total of 28 seconds (7 seconds * 4 iterations).
     *  This duration is set based on observations in the Proteus simulation, where it approximately equals 8 seconds in total.
     * The delay allows the system to enter the 'm' mode if any interrupt is handled during this period.
     * If no interrupt occurs and the firstFlag remains 0, the system sends 'x' to go to the core application
     * and disables interrupts to end the connection. */
    u8 i = 0;
    for (i = 0; i < 4; i++)
    {
        MSTK_voidDelayms(7000);
    }

    if (firstFlag == 0)
    {
        MEXTI_void_DisableInterrupts(); // Disable all interrupts
        MUART_void_SendData('x');       // Signal to transition to core application
    }

    return 0;
}
