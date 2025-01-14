/*
 * MEXTI_program.c
 *
 *  Created on: Dec 15, 2024
 *
 */
#include <LIB/Bit_Math.h>
#include <LIB/STD_Types.h>
#include <MCAL/MEXTI/MEXTI_config.h>
#include <MCAL/MEXTI/MEXTI_interface.h>
#include <MCAL/MEXTI/MEXTI_private.h>

static void (*Copy_GlobalPtr[16])(void);

void MEXTI_void_InterruptSetPort(EXTI_LINE Copy_uddtLine,
		EXTI_PORT Copy_uddtPort) {
	SYSCFG->EXTICR[Copy_uddtLine / DIV_Fac] &= ~(Musk
			<< (4 * (Copy_uddtLine % DIV_Fac)));
	SYSCFG->EXTICR[Copy_uddtLine / DIV_Fac] |= Copy_uddtPort
			<< (4 * (Copy_uddtLine % DIV_Fac));
}

void MEXTI_void_Enable(EXTI_LINE Copy_uddtLine) {
	EXTI->IMR |= (1 << Copy_uddtLine);
}
void MEXTI_void_Disable(EXTI_LINE Copy_uddtLine) {
	EXTI->IMR &= ~(1 << Copy_uddtLine);
}

void MEXTI_void_DisableInterrupts(void) {
	for (u8 i = 0; i < 16; i++) {
		EXTI->IMR &= ~(1 << i);
	}

}
void MEXTI_void_EnableInterrupts(void) {
	for (u8 i = 0; i < 16; i++) {
		EXTI->IMR |= (1 << i);
	}

}
void MEXTI_void_InterruptSetTrigger(EXTI_LINE Copy_uddtLine,
		EXTI_TriggerMode Copy_uddtMode) {
	switch (Copy_uddtMode) {
	case EXTI_Rising:
		EXTI->FTSR &= ~(1 << Copy_uddtLine);
		EXTI->RTSR |= (1 << Copy_uddtLine);
		break;
	case EXTI_Falling:
		EXTI->RTSR &= ~(1 << Copy_uddtLine);
		EXTI->FTSR |= (1 << Copy_uddtLine);
		break;
	case EXTI_OnChange:
		EXTI->RTSR |= (1 << Copy_uddtLine);
		EXTI->FTSR |= (1 << Copy_uddtLine);
		break;
	default:
		break;
	}
}

void MEXTI0_void_CallbackFunc(void (*Copy_ptr)(void)) {
	Copy_GlobalPtr[0] = Copy_ptr;
}
void MEXTI1_void_CallbackFunc(void (*Copy_ptr)(void)) {
	Copy_GlobalPtr[1] = Copy_ptr;
}
void MEXTI2_void_CallbackFunc(void (*Copy_ptr)(void)) {
	Copy_GlobalPtr[2] = Copy_ptr;
}
void MEXTI3_void_CallbackFunc(void (*Copy_ptr)(void)) {
	Copy_GlobalPtr[3] = Copy_ptr;
}
void MEXTI4_void_CallbackFunc(void (*Copy_ptr)(void)) {
	Copy_GlobalPtr[4] = Copy_ptr;
}
void MEXTI5_void_CallbackFunc(void (*Copy_ptr)(void)) {
	Copy_GlobalPtr[5] = Copy_ptr;
}
void MEXTI6_void_CallbackFunc(void (*Copy_ptr)(void)) {
	Copy_GlobalPtr[6] = Copy_ptr;
}

void MEXTI13_void_CallbackFunc(void (*Copy_ptr)(void)) {
	Copy_GlobalPtr[13] = Copy_ptr;
}

void EXTI0_IRQHandler(void) {
	Copy_GlobalPtr[0]();
	EXTI->PR |= 1;
}

void EXTI1_IRQHandler(void) {
	Copy_GlobalPtr[1]();
	EXTI->PR |= (1 << 1);
}
void EXTI2_IRQHandler(void) {
	Copy_GlobalPtr[2]();
	EXTI->PR |= (1 << 2);
}

void EXTI3_IRQHandler(void) {
	Copy_GlobalPtr[3]();
	EXTI->PR |= (1 << 3);
}
void EXTI4_IRQHandler(void) {
	Copy_GlobalPtr[4]();
	EXTI->PR |= (1 << 4);
}

void EXTI9_5_IRQHandler(void) {
	if (EXTI->PR & (1 << 5)) {
		Copy_GlobalPtr[5]();
		EXTI->PR |= (1 << 5);
	}else if (EXTI->PR & (1 << 6)){
		Copy_GlobalPtr[6]();
		EXTI->PR |= (1 << 6);
	}
}

void EXTI15_10_IRQHandler(void) {
	if (EXTI->PR & (1 << 13)) {
		Copy_GlobalPtr[13]();
		EXTI->PR |= (1 << 13);
	}
}

