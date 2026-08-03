#include "RELAY_Interface.h"

static uint8_t WaterPump_Group;
static uint8_t WaterPump_Pin;
static uint8_t Heater_Group;
static uint8_t Heater_Pin;
static uint8_t Fan_Group;
static uint8_t Fan_Pin;
void WaterPump_Init(uint8_t GroupName, uint8_t PinNumber)
{
    DIO_InitPin(GroupName,PinNumber,Low);
    WaterPump_Group = GroupName;
    WaterPump_Pin = PinNumber;
}
void Heater_Init(uint8_t GroupName, uint8_t PinNumber)
{
        DIO_InitPin(GroupName,PinNumber,Low);
    Heater_Group = GroupName;
    Heater_Pin = PinNumber;
}
void Fan_Init(uint8_t GroupName, uint8_t PinNumber)
{
        DIO_InitPin(GroupName,PinNumber,Low);
    Fan_Group = GroupName;
    Fan_Pin = PinNumber;
}
void WaterPump_Toggle()
{
    ToggleBit(WaterPump_Group,WaterPump_Pin);
}

void Heater_Toggle()
{
    ToggleBit(Heater_Group,Heater_Pin);
}

void Fan_Toggle()
{
    ToggleBit(Fan_Group,Fan_Pin);
}

void WaterPump_On()
{
    DIO_WritePin(WaterPump_Group,WaterPump_Pin,High);
}
void Heater_On()
{
    DIO_WritePin(Heater_Group,Heater_Pin,High);
}
void Fan_On()
{
    DIO_WritePin(Fan_Group,Fan_Pin,High);
}

void WaterPump_Off()
{
        DIO_WritePin(WaterPump_Group,WaterPump_Pin,Low);

}
void Heater_Off()
{
    DIO_WritePin(Heater_Group,Heater_Pin,Low);
   
}
void Fan_Off()
{
    DIO_WritePin(Fan_Group,Fan_Pin,Low);

}