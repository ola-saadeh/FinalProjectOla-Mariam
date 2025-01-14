
/*
 * MEXTI_interface.h
 *
 *  Created on: Dec 15, 2024
 *      Author:
 */

#ifndef MEXTI_INTERFACE_H_
#define MEXTI_INTERFACE_H_

typedef enum
{
	EXTI_LineZero=0,
	EXTI_LineOne,
	EXTI_LineTwo,
	EXTI_LineThree,
	EXTI_LineFour,
	EXTI_LineFive,
	EXTI_LineSix,
	EXTI_LineSeven,
	EXTI_LineEight,
	EXTI_LineNine,
	EXTI_LineTen,
	EXTI_LineEleven,
	EXTI_LineTwelve,
	EXTI_LineThirteen,
	EXTI_LineFourteen,
	EXTI_LineFifteen
}EXTI_LINE;

typedef enum
{
	EXTI_PORTA=0,
	EXTI_PORTB,
	EXTI_PORTC
}EXTI_PORT;

typedef enum
{
	EXTI_Rising=0,
	EXTI_Falling,
	EXTI_OnChange
}EXTI_TriggerMode;

void MEXTI_void_InterruptSetPort(EXTI_LINE Copy_uddtLine,EXTI_PORT Copy_uddtPort);
void MEXTI_void_Enable(EXTI_LINE Copy_uddtLine);
void MEXTI_void_Disable(EXTI_LINE Copy_uddtLine);
void MEXTI_void_InterruptSetTrigger(EXTI_LINE Copy_uddtLine,EXTI_TriggerMode Copy_uddtMode);
void MEXTI0_void_CallbackFunc(void(*Copy_ptr)(void));
void MEXTI1_void_CallbackFunc(void(*Copy_ptr)(void));
void MEXTI2_void_CallbackFunc(void(*Copy_ptr)(void));
void MEXTI3_void_CallbackFunc(void(*Copy_ptr)(void));

void  MEXTI13_void_CallbackFunc(void(*Copy_ptr)(void));
void MEXTI_void_EnableInterrupts(void);
void MEXTI_void_DisableInterrupts(void);


#endif /* MEXTI_INTERFACE_H_ */
