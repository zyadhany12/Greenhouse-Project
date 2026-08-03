#include "EXTI_Interface.h"

void EXTI_Init(uint8_t Interrupt, uint8_t SensConfig)
{
    if (Interrupt > Exti_Interrupt2 || Interrupt < Exti_Interrupt0)
    {
        return;
    }
    else
    {
        if (Interrupt == Exti_Interrupt1)
        {
            if (SensConfig == Exti_LowLevel)
            {
                ClearBit(MCUCR_Reg, Exti_ISC11);
                ClearBit(MCUCR_Reg, Exti_ISC10);
            }
            if (SensConfig == Exti_AnyChange)
            {
                ClearBit(MCUCR_Reg, Exti_ISC11);
                SetBit(MCUCR_Reg, Exti_ISC10);
            }
            if (SensConfig == Exti_FallingEdge)
            {
                SetBit(MCUCR_Reg, Exti_ISC11);
                ClearBit(MCUCR_Reg, Exti_ISC10);
            }
            if (SensConfig == Exti_RisingEdge)
            {
                SetBit(MCUCR_Reg, Exti_ISC11);
                SetBit(MCUCR_Reg, Exti_ISC10);
            }
        }

        else if (Interrupt == Exti_Interrupt1)
        {
            if (SensConfig == Exti_LowLevel)
            {
                ClearBit(MCUCR_Reg, Exti_ISC01);
                ClearBit(MCUCR_Reg, Exti_ISC00);
            }
            if (SensConfig == Exti_AnyChange)
            {
                ClearBit(MCUCR_Reg, Exti_ISC01);
                SetBit(MCUCR_Reg, Exti_ISC00);
            }
            if (SensConfig == Exti_FallingEdge)
            {
                SetBit(MCUCR_Reg, Exti_ISC01);
                ClearBit(MCUCR_Reg, Exti_ISC00);
            }
            if (SensConfig == Exti_RisingEdge)
            {
                SetBit(MCUCR_Reg, Exti_ISC01);
                SetBit(MCUCR_Reg, Exti_ISC00);
            }
        }
        else if (Interrupt == Exti_Interrupt2)
        {
            if (SensConfig == Exti_FallingEdge)
            {
                ClearBit(MCUCSR_Reg, Exti_ISC2);
            }
            if (SensConfig == Exti_RisingEdge)
            {
                SetBit(MCUCSR_Reg, Exti_ISC2);
            }
        }
    }
}

void EXTI_Enable(uint8_t Interrupt)
{
    if (Interrupt == Exti_Interrupt1)
    {
        SetBit(GICR_Reg, Exti_INT1);
    }
    if (Interrupt == Exti_Interrupt0)
    {
        SetBit(GICR_Reg, Exti_INT0);
    }
    if (Interrupt == Exti_Interrupt2)
    {
        SetBit(GICR_Reg, Exti_INT2);
    }
}

void EXTI_Disable(uint8_t Interrupt)
{
    if (Interrupt == Exti_Interrupt1)
    {
        ClearBit(GICR_Reg, Exti_INT1);
    }
    if (Interrupt == Exti_Interrupt0)
    {
        ClearBit(GICR_Reg, Exti_INT0);
    }
    if (Interrupt == Exti_Interrupt2)
    {
        ClearBit(GICR_Reg, Exti_INT2);
    }
}