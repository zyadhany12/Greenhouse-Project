#ifndef RELAY_INTERFACE_H_
#define RELAY_INTERFACE_H_
#include "../../MCAL/DIO/DIO_Interface.h"


void WaterPump_Init(uint8_t GroupName, uint8_t PinNumber);
void Heater_Init(uint8_t GroupName, uint8_t PinNumber);
void Fan_Init(uint8_t GroupName, uint8_t PinNumber);

void WaterPump_On();
void Heater_On();
void Fan_On();

void WaterPump_Off();
void Heater_Off();
void Fan_Off();


void Fan_Toggle();
void Heater_Toggle();
void WaterPump_Toggle();


#endif