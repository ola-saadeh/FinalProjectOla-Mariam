/*
 * H7SEG_program.c
 *
 *  Created on: Dec 6, 2024
 *      Author: Ola Saadeh
 */


#include "LIB/STD_Types.h"
#include "LIB/Bit_Math.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "HAL/H7SEG/H7SEG_config.h"
#include "HAL/H7SEG/H7SEG_interface.h"


// Static variable initialized to 9 to ensure that if the user tries to set a number greater than 9 in the main program,
// the display will show the largest valid single-digit number, which is 9.
static u8 H7SEG_u8NumberToDisplay = 9;


static u8 H7SEG_u8Numbers[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4 10011001
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};



void H7SEG_voidInit(void) {
    u8 LOC_u8Iter;

    // Set segment pins (a to g) as output
    for (LOC_u8Iter = SEGMENT_START_PIN; LOC_u8Iter < SEGMENT_START_PIN + 7; LOC_u8Iter++) {
        MGPIO_void_SetMode(SEGMENT_PORT, LOC_u8Iter, Output);
        MGPIO_void_SetOutputPinMode(SEGMENT_PORT, LOC_u8Iter, PUSH_PULL, LOWSpeed);
    }

    // Set enable pins as output
    MGPIO_void_SetMode(SEGMENT_ENABLE_PORT, SEGMENT_ENABLE_PIN_1, Output);
    MGPIO_void_SetMode(SEGMENT_ENABLE_PORT, SEGMENT_ENABLE_PIN_2, Output);

    H7SEG_voidClear();

 }

void H7SEG_voidDisplayAnyNumber(void) {
    u8 LOC_u8Data = H7SEG_u8Numbers[H7SEG_u8NumberToDisplay];// Get the corresponding segment data for the number to display
    u8 LOC_u8Iter;

    if (DISPLAYTYPE == COMMON_ANODE) {
        LOC_u8Data = ~LOC_u8Data; // Invert the bits for common anode
        MGPIO_void_SetPinValue(SEGMENT_ENABLE_PORT, SEGMENT_ENABLE_PIN_2, High);//enable anode

    }else{
        MGPIO_void_SetPinValue(SEGMENT_ENABLE_PORT, SEGMENT_ENABLE_PIN_1, LOW);// enable cathode
    }


    for (LOC_u8Iter = 0; LOC_u8Iter < 7; LOC_u8Iter++) {
        MGPIO_void_SetPinValue(SEGMENT_PORT, SEGMENT_START_PIN + LOC_u8Iter, Get_Bit(LOC_u8Data, LOC_u8Iter));
    }
}

void H7SEG_voidClear(void) {
    u8 LOC_u8Iter;

    // Disable all segments (set to LOW)
    for (LOC_u8Iter = SEGMENT_START_PIN; LOC_u8Iter < SEGMENT_START_PIN + 7; LOC_u8Iter++) {
        MGPIO_void_SetPinValue(SEGMENT_PORT, LOC_u8Iter, LOW);
    }

    // Disable the enable pins (for common anode or cathode)
    MGPIO_void_SetPinValue(SEGMENT_ENABLE_PORT, SEGMENT_ENABLE_PIN_1, High);  // Common cathode OFF
    MGPIO_void_SetPinValue(SEGMENT_ENABLE_PORT, SEGMENT_ENABLE_PIN_2, LOW);   // Common anode OFF
}

void H7SEG_voidSetNumber(u8 num) {
    if (num <= 9) {
        H7SEG_u8NumberToDisplay = num;
    }
}
