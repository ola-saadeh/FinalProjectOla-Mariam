/*
 * MGPIO_interface.h
 *
 *  Created on: Dec 3, 2024
 *      Author:  Ola Saadeh
 */


#ifndef MGPIO_INTERFACE_H_
#define MGPIO_INTERFACE_H_

typedef enum
{
	PORTA=0,
	PORTB,
	PORTC
}PORTS;

typedef enum
{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
}PINS;


typedef enum
{
	Input=0,
	Output,
	Alternative_Function,
	Analog
}Modes;

typedef enum
{
	NOPULLUPORPULLDOWN=0,
	PULLUP,
	PULDOWN
}INPUT_Modes;

typedef enum
{
	LOW=0,
	High
}OUTPUT_VALUE;

typedef enum
{
	PUSH_PULL=0,
	OPEN_DRAIN
}OUTPUT_Type;


typedef enum
{
	LOWSpeed=0,
	MediumSpeed,
	HighSpeed,
	VhighSpeed
}OUTPUT_SPEED;

typedef enum
{
    AF0=0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
}Alternative_Functions;


void MGPIO_void_SetMode(PORTS Copy_uddtPort,PINS Copy_uddtPin,Modes Copy_udddtmode);
void MGPIO_void_SetInputPinMode(PORTS Copy_uddtPort,PINS Copy_uddtPin,INPUT_Modes Copy_uddtInputMode);
u8   MGPIO_u8GetPinValue(PORTS Copy_uddtPort,PINS Copy_uddtPin);
u8   MGPIO_u8GetPinValuePyPTR(PORTS Copy_uddtPort,PINS Copy_uddtPin,u8 *Copy_Pu8Ptr);
void MGPIO_void_SetOutputPinMode(PORTS Copy_uddtPort,PINS Copy_uddtPin,OUTPUT_Type COPY_uddtOutputType,OUTPUT_SPEED COPY_uddtOutputSpeed);
void MGPIO_void_SetPinValue(PORTS Copy_uddtPort,PINS Copy_uddtPin,OUTPUT_VALUE Copy_uddtOutputValue);
void MGPIO_void_AtomicSetPinValue(PORTS Copy_uddtPort,PINS Copy_uddtPin,OUTPUT_VALUE Copy_uddtOutputValue);
void MGPIO_void_SetAlternativeFunctionMode(PORTS Copy_uddtPort,PINS Copy_uddtPin,Alternative_Functions Copy_uddtAlternativeFunction);

#endif /* MGPIO_INTERFACE_H_ */
