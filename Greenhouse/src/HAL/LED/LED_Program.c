#include "LED_Interface.h"

void Led_Init(uint8_t GroupName, uint8_t PinNumber)
{
    if(GroupName == GroupA)
    {
        DIO_InitPin(DDRA_Reg,PinNumber,Output);
    }
    else if(GroupName == GroupB)
    {
        DIO_InitPin(DDRB_Reg,PinNumber,Output) ;
    }
    else if(GroupName == GroupC)
    {
        DIO_InitPin(DDRC_Reg,PinNumber,Output) ;
    }
    else if(GroupName == GroupD)
    {
        DIO_InitPin(DDRD_Reg,PinNumber,Output) ;
    }
} 
// Replaced By the DIO_Init

void Led_on(uint8_t GroupName, uint8_t PinNumber, uint8_t ConnectionType)
{

    if (ConnectionType == SourceConnection)
    {
        DIO_WritePin(GroupName, PinNumber, High);
    }
    else if (ConnectionType == SinkConnection)
    {
        DIO_WritePin(GroupName, PinNumber, Low);
    }
}

void Led_off(uint8_t GroupName, uint8_t PinNumber, uint8_t ConnectionType)
{
    if (ConnectionType == SourceConnection)
    {
        DIO_WritePin(GroupName, PinNumber, Low);
    }
    else if (ConnectionType == SinkConnection)
    {
        DIO_WritePin(GroupName, PinNumber, High);
    }
}


//Sets The Whole of Group# to be On/Off
void All_Led_Controll(uint8_t GroupName, uint8_t type)
{
    if (type == STATE_OFF)
    {
        if (GroupName == GroupA)
        {
            for (uint8_t i = 0; i < 8; i++)
            {
                Led_off(GroupA, i, SourceConnection);
            }
        }
        else if (GroupName == GroupB)
        {
            for (uint8_t i = 0; i < 8; i++)
            {
                Led_off(GroupB, i, SourceConnection);
            };
        }
        else if (GroupName == GroupC)
        {
            for (uint8_t i = 0; i < 8; i++)
            {
                Led_off(GroupC, i, SourceConnection);
            }
        }
        else if (GroupName == GroupD)
        {
            for (uint8_t i = 0; i < 8; i++)
            {
                Led_off(GroupD, i, SourceConnection);
            }
        }
    }
    else if (type == STATE_ON)
    {
        if (GroupName == GroupA)
        {
            for (uint8_t i = 0; i < 8; i++)
            {
                Led_on(GroupA, i, SourceConnection);
            }
        }
        else if (GroupName == GroupB)
        {
            for (uint8_t i = 0; i < 8; i++)
            {
                Led_on(GroupB, i, SourceConnection);
            };
        }
        else if (GroupName == GroupC)
        {
            for (uint8_t i = 0; i < 8; i++)
            {
                Led_on(GroupC, i, SourceConnection);
            }
        }
        else if (GroupName == GroupD)
        {
            for (uint8_t i = 0; i < 8; i++)
            {
                Led_on(GroupD, i, SourceConnection);
            }
        }
    }
}