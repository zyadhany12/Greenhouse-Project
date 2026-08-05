#include "BTN_Interface.h"
#include <stdint.h>



void Button_Init(uint8_t GroupName, uint8_t PinNumber)
{
    DIO_InitPin(GroupName, PinNumber, Input);
    DIO_WritePin(GroupName,PinNumber,Low);
}

                                                      

uint8_t Button_GetState(uint8_t GroupName, uint8_t PinNumber)
{
    return  ReadBit(GroupName,PinNumber);
}
