#ifndef BTN_INTERFACE_H
#define BTN_INTERFACE_H

#include <stdint.h>
#include "../../MCAL/DIO/DIO_Interface.h"
#include "BTN_Private.h"
#include "BTN_Config.h"



void Button_Init(uint8_t GroupName, uint8_t PinNumber);



uint8_t Button_GetState(uint8_t GroupName, uint8_t PinNumber);

#endif 