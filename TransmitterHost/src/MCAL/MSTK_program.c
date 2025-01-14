#include <LIB/Bit_Math.h>
#include <LIB/STD_Types.h>
#include <MCAL/MSTK/MSTK_config.h>
#include <MCAL/MSTK/MSTK_interface.h>
#include <MCAL/MSTK/MSTK_private.h>

void(*Global_ptr)(void);

u8 systickflag=0;

void MSTK_voidInit(void)
{

#if (SYSTICK_CLKSOURCE==STK_AHB)
	STK->CTRL |=(1<<MSTK_ClockSource);
	STK->CTRL &=~(1<<MSTK_Enable);
	//62.5 nanosec
#elif (SYSTICK_CLKSOURCE==STK_AHBby8)
	STK->CTRL &=~(1<<MSTK_ClockSource);
	STK->CTRL &=~(1<<MSTK_Enable);
	//tick -->0.5 usec
#endif
}

void MSTK_voidStartTimer(u32 Copy_u32ReloadValue)
{
	STK->LOAD =Copy_u32ReloadValue;
	STK->VALUE =0;
	STK->CTRL |=(1<<MSTK_Enable);
}

void MSTK_voidStopTimer(void)
{
	STK->CTRL &=~(1<<1);
	STK->CTRL &=~(1<<MSTK_Enable);
	STK->LOAD =0;
	STK->VALUE =0;

}
u8   MSTK_u8ReadFlag(void)
{
	return Get_Bit(STK->CTRL,MSTK_CountFlag);
}

void MSTK_voidCtrlIntState(SYSTICKINTSTATE Copy_uddtSYSTICKINT)
{
	switch (Copy_uddtSYSTICKINT) {
	case SYSTICKINTENABLE:
		STK->CTRL|=(1<<MSTK_TickINT);
		break;
	case SYSTICKINTDISABLE:
		STK->CTRL &=~(1<<MSTK_TickINT);
		break;
	default:
		break;
	}

}

u32  MSTK_u32GetElapsedTicksSingleShot(void)
{
	return ((STK->LOAD)-(STK->VALUE));
}

u32  MSTK_u32GetRemainingTicksSingleShot(void)
{
	return STK->VALUE;
}

void MSTK_voidDelayms(u32 Copy_u32DelayByMS) //1m-->2000
{
	u32 LOC_u32Counter=0;
	f64 LOC_F64PreloadValue=0;
	u8 LOC_u8Flag=0;
	MSTK_voidCtrlIntState(SYSTICKINTDISABLE);
	if(Copy_u32DelayByMS<=8388)
	{
		MSTK_voidStartTimer(Copy_u32DelayByMS*2000);
		while(MSTK_u8ReadFlag()==0);
		STK->CTRL &=~(1<<MSTK_Enable);
	}
	else if((Copy_u32DelayByMS %8388) !=0)
	{
		LOC_u32Counter=(Copy_u32DelayByMS/8388)+1;
		LOC_F64PreloadValue=(((Copy_u32DelayByMS %8388) / 8388) * 16777216);
		while(LOC_u32Counter>0)
		{
			if(LOC_u8Flag==0)
			{
				MSTK_voidStartTimer(LOC_F64PreloadValue);
				LOC_u8Flag=1;
			}
			else
			{
				MSTK_voidStartTimer(16777215);
			}
			while(MSTK_u8ReadFlag()==0);
			LOC_u32Counter--;
		}
		STK->CTRL &=~(1<<MSTK_Enable);
	}
	else
	{
		LOC_u32Counter=(Copy_u32DelayByMS/8388);
		for(u32 i=0;i<LOC_u32Counter;i++)
		{
			MSTK_voidStartTimer(16777215);
			while(MSTK_u8ReadFlag()==0);
		}
		STK->CTRL &=~(1<<MSTK_Enable);
	}


}
void MSTK_voidDelayus(u32 Copy_u32DelayByUS)
{
	u32 LOC_u32Counter=0;
		f64 LOC_F64PreloadValue=0;
		u8 LOC_u8Flag=0;
		MSTK_voidCtrlIntState(SYSTICKINTDISABLE);
		if(Copy_u32DelayByUS<=8388608)
		{
			MSTK_voidStartTimer(Copy_u32DelayByUS*2);
			while(MSTK_u8ReadFlag()==0);
			STK->CTRL &=~(1<<MSTK_Enable);
		}
		else if((Copy_u32DelayByUS %8388608) !=0)
		{
			LOC_u32Counter=(Copy_u32DelayByUS/8388608)+1;
			LOC_F64PreloadValue=(((Copy_u32DelayByUS %8388608) / 8388608) * 16777216);
			while(LOC_u32Counter>0)
			{
				if(LOC_u8Flag==0)
				{
					MSTK_voidStartTimer(LOC_F64PreloadValue);
					LOC_u8Flag=1;
				}
				else
				{
					MSTK_voidStartTimer(16777215);
				}
				while(MSTK_u8ReadFlag()==0);
				LOC_u32Counter--;
			}
			STK->CTRL &=~(1<<MSTK_Enable);

		}

		else
		{
			LOC_u32Counter=(Copy_u32DelayByUS/8388608);
			for(u32 i=0;i<LOC_u32Counter;i++)
			{
				MSTK_voidStartTimer(16777215);
				while(MSTK_u8ReadFlag()==0);
			}
			STK->CTRL &=~(1<<MSTK_Enable);
		}

}

void MSTK_void_CallBack(void(*ptr)(void),u32 TickTimeUS)
{
	systickflag=0;
	MSTK_voidCtrlIntState(SYSTICKINTENABLE);
	Global_ptr=ptr;
	MSTK_voidStartTimer(TickTimeUS*2);

}

void MSTK_void_CallBacksingle(void(*ptr)(void),u32 TickTimeUS)
{
	systickflag=1;
	Global_ptr=ptr;
	MSTK_voidStartTimer(TickTimeUS*2);


}


void SysTick_Handler(void)
{
	Global_ptr();
	MSTK_u8ReadFlag();
	if(systickflag==1)
	{
	MSTK_voidCtrlIntState(SYSTICKINTDISABLE);
	}

}




