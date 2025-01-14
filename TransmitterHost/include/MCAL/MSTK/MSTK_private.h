/*
 * MSTK_private.h
 *
 *  Created on: Dec 4, 2024
 *      Author: ZBOOK
 */

#ifndef MSTK_PRIVATE_H_
#define MSTK_PRIVATE_H_


#define STK_BASE_ADRESS (0xE000E010)

typedef struct
{
	u32 CTRL;
	u32 LOAD;
	u32 VALUE;
	u32 CALIB;
}STK_t;

#define STK    ((volatile STK_t*)STK_BASE_ADRESS)


#define MSTK_Enable      0
#define MSTK_TickINT     1
#define MSTK_ClockSource 2
#define MSTK_CountFlag   16


#define STK_AHBby8  0
#define STK_AHB    1


#if SYSTICK_CLKSOURCE == STK_AHB
    #define STK_AHB_CLK       16000000   /* Processor clock (AHB clock) divided by 1 */
#elif SYSTICK_CLKSOURCE == STK_AHBby8
    #define STK_AHB_CLK       2000000   /**< Processor clock (AHB clock) divided by 8 */
#endif

#endif /* MSTK_PRIVATE_H_ */
