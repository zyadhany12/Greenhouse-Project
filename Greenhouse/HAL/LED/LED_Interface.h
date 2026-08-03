#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_


#include <stdint.h>
#include "LED_Config.h"
#include "LED_Private.h"
#include "../../MCAL/DIO/DIO_Interface.h"


void Led_Init(uint8_t GroupName, uint8_t PinNumber);

void Led_on(uint8_t GroupName,
            uint8_t PinNumber,
            uint8_t ConnectionType);

void Led_off(uint8_t GroupName, uint8_t PinNumber, uint8_t ConnectionType);

void All_Led_Controll(uint8_t GroupName, uint8_t type);

#endif