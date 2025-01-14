#ifndef BIT_MATH_H
#define BIT_MATH_H

#define Set_Bit(Reg,Bitno)  (Reg|=(1<<Bitno))
#define Clr_Bit(Reg,Bitno)  (Reg&=~(1<<Bitno))
#define Tog_Bit(Reg,Bitno)  (Reg^=(1<<Bitno))
#define Get_Bit(Reg,Bitno)  ((Reg>>Bitno)&1)

#endif
