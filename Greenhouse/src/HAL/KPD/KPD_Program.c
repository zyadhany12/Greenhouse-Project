#include <stdint.h>
#include "KPD_Interface.h"

static uint8_t KeypadValue[4][3] =
    {
        {'7', '8', '9'},
        {'4', '5', '6'},
        {'1', '2', '3'},
        {'#', '0', '*'},
};

void KPD_Init()
{
    // Coloum Direction
    DIO_InitPin(Dio_GroupC, Dio_Pin0, Output);
    DIO_InitPin(Dio_GroupC, Dio_Pin1, Output);
    DIO_InitPin(Dio_GroupC, Dio_Pin2, Output);
    // Init value for coloum
    DIO_WritePin(Dio_GroupC, Dio_Pin0, High);
    DIO_WritePin(Dio_GroupC, Dio_Pin1, High);
    DIO_WritePin(Dio_GroupC, Dio_Pin2, High);
    // ROW
    DIO_InitPin(Dio_GroupC, Dio_Pin3, Input);
    DIO_InitPin(Dio_GroupC, Dio_Pin4, Input);
    DIO_InitPin(Dio_GroupC, Dio_Pin5, Input);
    DIO_InitPin(Dio_GroupC, Dio_Pin6, Input);
    // Enable Internal Pull UP
    DIO_WritePin(Dio_GroupC, Dio_Pin3, High);
    DIO_WritePin(Dio_GroupC, Dio_Pin4, High);
    DIO_WritePin(Dio_GroupC, Dio_Pin5, High);
    DIO_WritePin(Dio_GroupC, Dio_Pin6, High);
}

uint8_t KPD_GetButtonValue()
{
    uint8_t Result = 0;
    for (uint8_t C = 0; C < 3; C++)
    {
        DIO_WritePin(Dio_GroupC, C, Low);
        for (uint8_t R = 3; R < 7; R++)
        {
            DIO_ReadPin(Dio_GroupC, R, &Result);
            if (Result == Pressed)
            {
                return KeypadValue[R - 3][C];
            }
        }
        DIO_WritePin(Dio_GroupC, C, High);
    }
    
}

