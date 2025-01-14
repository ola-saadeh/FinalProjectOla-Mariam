#include <LIB/Bit_Math.h>
#include <LIB/STD_Types.h>
#include <MCAL/MRCC/MRCC_config.h>
#include <MCAL/MRCC/MRCC_interface.h>
#include <MCAL/MRCC/MRCC_private.h>


void MRCC_void_Init(void)
{
	/*clock selection*/
#if(SYSTEM_CLK==HSI_CLOCK)
	//HSI ON
	RCC->CR |=(1<<MRCC_HSION);
	//Set_Bit(RCC->CR,MRCC_HSION);
	//wait till HSI ready
	while(!Get_Bit(RCC->CR,MRCC_HSIRDY));
	//while(Get_Bit(RCC->CR,MRCC_HSIRDY)==0);
	//switch to HSI
	RCC->CFGR &=~SWITCH_MUSK;
	RCC->CFGR |=SWITCH_HSI;

#elif(SYSTEM_CLK==HSE_CLOCK)
	#if(HSE_OSC==MECHANICAL_HSE)
		RCC->CR &=~(1<<MRCC_HSEBYP);
	#elif(HSE_OSC==ELECTRICAL_HSE)
		RCC->CR |=(1<<MRCC_HSEBYP);
	#endif

	//HSE ON
	RCC->CR |=(1<<MRCC_HSEON);
	//Set_Bit(RCC->CR,MRCC_HSEON);
	//wait till HSE ready
	while(!Get_Bit(RCC->CR,MRCC_HSERDY));
	//while(Get_Bit(RCC->CR,MRCC_HSERDY)==0);
	//switch to HSE
	RCC->CFGR &=~SWITCH_MUSK;
	RCC->CFGR |=SWITCH_HSE;
	//disable HSI clock
	RCC->CR &=~(1<<MRCC_HSION);


#endif
}

void MRCC_void_EnablePeriperalClock(SYSTEM_BUS Copy_uddtAdressBus,u32 Copy_u32Peripheral)
{
	switch (Copy_uddtAdressBus) {
		case AHB1_BUS:
			RCC->AHB1ENR |=(1<<Copy_u32Peripheral);
			break;
		case AHB2_BUS:
			RCC->AHB2ENR |=(1<<Copy_u32Peripheral);
					break;
		case APB1_BUS:
			RCC->APB1ENR |=(1<<Copy_u32Peripheral);
					break;
		case APB2_BUS:
			RCC->APB2ENR |=(1<<Copy_u32Peripheral);
					break;
		default:
			break;
	}

}

void MRCC_void_DisablePeriperalClock(SYSTEM_BUS Copy_uddtAdressBus,u32 Copy_u32Peripheral)
{
	switch (Copy_uddtAdressBus) {
			case AHB1_BUS:
				RCC->AHB1ENR &=~(1<<Copy_u32Peripheral);
				break;
			case AHB2_BUS:
				RCC->AHB2ENR &=~(1<<Copy_u32Peripheral);
						break;
			case APB1_BUS:
				RCC->APB1ENR &=~(1<<Copy_u32Peripheral);
						break;
			case APB2_BUS:
				RCC->APB2ENR &=~(1<<Copy_u32Peripheral);
						break;
			default:
				break;
		}

}

