#include <LIB/Bit_Math.h>
#include <LIB/STD_Types.h>
#include <MCAL/MGPIO/MGPIO_interface.h>
#include <MCAL/MGPIO/MGPIO_private.h>

void MGPIO_void_SetMode(PORTS Copy_uddtPort,PINS Copy_uddtPin,Modes Copy_udddtmode)
{
	switch (Copy_uddtPort)
	{
	case PORTA:
		GPIOA->MODER &=~(GPIO_MUSK<<(Copy_uddtPin*2));
		GPIOA->MODER |=(Copy_udddtmode<<(Copy_uddtPin*2));
		break;
	case PORTB:
		GPIOB->MODER &=~(GPIO_MUSK<<(Copy_uddtPin*2));
		GPIOB->MODER |=(Copy_udddtmode<<(Copy_uddtPin*2));
		break;
	case PORTC:
		GPIOC->MODER &=~(GPIO_MUSK<<(Copy_uddtPin*2));
		GPIOC->MODER |=(Copy_udddtmode<<(Copy_uddtPin*2));
		break;
	default:
		break;
	}
}

void MGPIO_void_SetInputPinMode(PORTS Copy_uddtPort,PINS Copy_uddtPin,INPUT_Modes Copy_uddtInputMode)
{
	switch (Copy_uddtPort)
	{
	case PORTA:
		GPIOA->PUPDR &=~(GPIO_MUSK<<(Copy_uddtPin*2));
		GPIOA->PUPDR |=(Copy_uddtInputMode<<(Copy_uddtPin*2));
		break;
	case PORTB:
		GPIOB->PUPDR &=~(GPIO_MUSK<<(Copy_uddtPin*2));
		GPIOB->PUPDR |=(Copy_uddtInputMode<<(Copy_uddtPin*2));
		break;
	case PORTC:
		GPIOC->PUPDR &=~(GPIO_MUSK<<(Copy_uddtPin*2));
		GPIOC->PUPDR |=(Copy_uddtInputMode<<(Copy_uddtPin*2));
		break;
	default:
		break;
	}

}
u8 MGPIO_u8GetPinValue(PORTS Copy_uddtPort,PINS Copy_uddtPin)
{
	u8 LOC_u8PinValue = INIT_VALUE;
	switch (Copy_uddtPort)
	{
	case PORTA:
		LOC_u8PinValue=Get_Bit(GPIOA->IDR,Copy_uddtPin);
		break;
	case PORTB:
		LOC_u8PinValue=Get_Bit(GPIOB->IDR,Copy_uddtPin);
		break;
	case PORTC:
		LOC_u8PinValue=Get_Bit(GPIOC->IDR,Copy_uddtPin);
		break;
	default:
		break;
	}
	return LOC_u8PinValue;
}

u8 MGPIO_u8GetPinValuePyPTR(PORTS Copy_uddtPort,PINS Copy_uddtPin,u8 *Copy_Pu8Ptr)
{
	u8 LOC_u8ErrorState=0;
	switch (Copy_uddtPort)
	{
	case PORTA:
		*Copy_Pu8Ptr=Get_Bit(GPIOA->IDR,Copy_uddtPin);
		break;
	case PORTB:
		*Copy_Pu8Ptr=Get_Bit(GPIOB->IDR,Copy_uddtPin);
		break;
	case PORTC:
		*Copy_Pu8Ptr=Get_Bit(GPIOC->IDR,Copy_uddtPin);
		break;
	default:
		LOC_u8ErrorState=1;
		break;
	}
	return LOC_u8ErrorState;


}

void MGPIO_void_SetPinValue(PORTS Copy_uddtPort,PINS Copy_uddtPin,OUTPUT_VALUE Copy_uddtOutputValue)
{
	switch (Copy_uddtPort)
	{
	case PORTA:
		if(Copy_uddtOutputValue==High)
		{
			GPIOA->ODR |=(1<<Copy_uddtPin);
		}
		else if(Copy_uddtOutputValue==LOW)
		{
			GPIOA->ODR &=~(1<<Copy_uddtPin);
		}
		break;
	case PORTB:
		if(Copy_uddtOutputValue==High)
		{
			GPIOB->ODR |=(1<<Copy_uddtPin);
		}
		else if(Copy_uddtOutputValue==LOW)
		{
			GPIOB->ODR &=~(1<<Copy_uddtPin);
		}
		break;
	case PORTC:
		if(Copy_uddtOutputValue==High)
		{
			GPIOC->ODR |=(1<<Copy_uddtPin);
		}
		else if(Copy_uddtOutputValue==LOW)
		{
			GPIOC->ODR &=~(1<<Copy_uddtPin);
		}
		break;
	default:
		break;
	}

}

void MGPIO_void_AtomicSetPinValue(PORTS Copy_uddtPort,PINS Copy_uddtPin,OUTPUT_VALUE Copy_uddtOutputValue)
{

	switch (Copy_uddtPort)
	{
	case PORTA:
		if(Copy_uddtOutputValue==High)
		{
			GPIOA->BSRR =(1<<Copy_uddtPin);
		}
		else if(Copy_uddtOutputValue==LOW)
		{
			GPIOA->BSRR =(1<<(Copy_uddtPin+16));
		}
		break;
	case PORTB:
		if(Copy_uddtOutputValue==High)
		{
			GPIOB->BSRR =(1<<Copy_uddtPin);
		}
		else if(Copy_uddtOutputValue==LOW)
		{
			GPIOB->BSRR =(1<<(Copy_uddtPin+16));
		}
		break;
	case PORTC:
		if(Copy_uddtOutputValue==High)
		{
			GPIOC->BSRR =(1<<Copy_uddtPin);
		}
		else if(Copy_uddtOutputValue==LOW)
		{
			GPIOC->BSRR =(1<<(Copy_uddtPin+16));
		}
		break;
	default:
		break;
	}
}


void MGPIO_void_SetOutputPinMode(PORTS Copy_uddtPort,PINS Copy_uddtPin,OUTPUT_Type COPY_uddtOutputType,OUTPUT_SPEED COPY_uddtOutputSpeed)
{
	switch (Copy_uddtPort) {
	case PORTA:
		GPIOA->OTYPER &=~(1<<Copy_uddtPin);
		GPIOA->OTYPER |=(COPY_uddtOutputType<<Copy_uddtPin);
		GPIOA->OSPEEDER &=~(GPIO_MUSK<<(Copy_uddtPin*2));
		GPIOA->OSPEEDER |=(COPY_uddtOutputSpeed<<(Copy_uddtPin*2));
		break;
	case PORTB:
		GPIOB->OTYPER &=~(1<<Copy_uddtPin);
		GPIOB->OTYPER |=(COPY_uddtOutputType<<Copy_uddtPin);
		GPIOB->OSPEEDER &=~(GPIO_MUSK<<(Copy_uddtPin*2));
		GPIOB->OSPEEDER |=(COPY_uddtOutputSpeed<<(Copy_uddtPin*2));
		break;
	case PORTC:
		GPIOC->OTYPER &=~(1<<Copy_uddtPin);
		GPIOC->OTYPER |=(COPY_uddtOutputType<<Copy_uddtPin);
		GPIOC->OSPEEDER &=~(GPIO_MUSK<<(Copy_uddtPin*2));
		GPIOC->OSPEEDER |=(COPY_uddtOutputSpeed<<(Copy_uddtPin*2));
		break;
	default:
		break;
	}
}


void MGPIO_void_SetAlternativeFunctionMode(PORTS Copy_uddtPort,PINS Copy_uddtPin,Alternative_Functions Copy_uddtAlternativeFunction)
{
	if(Copy_uddtPin<=7)
	{
		switch (Copy_uddtPort) {
		case PORTA:
			GPIOA->AFRL &=~(ALT_FUNC_MUSK<<(Copy_uddtPin*4));
			GPIOA->AFRL |=(Copy_uddtAlternativeFunction<<(Copy_uddtPin*4));
			break;
		case PORTB:
			GPIOB->AFRL &=~(ALT_FUNC_MUSK<<(Copy_uddtPin*4));
			GPIOB->AFRL |=(Copy_uddtAlternativeFunction<<(Copy_uddtPin*4));
			break;
		case PORTC:
			GPIOC->AFRL &=~(ALT_FUNC_MUSK<<(Copy_uddtPin*4));
			GPIOC->AFRL |=(Copy_uddtAlternativeFunction<<(Copy_uddtPin*4));
			break;
		default:
			break;
		}
	}
	else if((Copy_uddtPin>=8) && (Copy_uddtPin<=15))
	{
		switch (Copy_uddtPort) {
		case PORTA:
			GPIOA->AFRH &=~(ALT_FUNC_MUSK<<((Copy_uddtPin-8)*4));
			GPIOA->AFRH |=(Copy_uddtAlternativeFunction<<((Copy_uddtPin-8)*4));
			break;
		case PORTB:
			GPIOB->AFRH &=~(ALT_FUNC_MUSK<<((Copy_uddtPin-8)*4));
			GPIOB->AFRH |=(Copy_uddtAlternativeFunction<<((Copy_uddtPin-8)*4));
			break;
		case PORTC:
			GPIOC->AFRH &=~(ALT_FUNC_MUSK<<((Copy_uddtPin-8)*4));
			GPIOC->AFRH |=(Copy_uddtAlternativeFunction<<((Copy_uddtPin-8)*4));
			break;
		default:
			break;
		}

	}




}
