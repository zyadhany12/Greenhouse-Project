#ifndef LM35_INTERFACE_H
#define LM35_INTERFACE_H
#include <stdint.h>
#include "../../MCAL/ADC/ADC_Interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "LM35_Private.h"


void LM35_Init(uint8_t PinNumber);
uint8_t LM35_GetTemp(void);

#endif
