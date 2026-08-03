#include "GIE_Interface.h"



void GIE_Enable()
{
    SetBit(SERG_Reg,I_Bit);
}
void GIE_Disable()
{
    ClearBit(SERG_Reg,I_Bit);
}