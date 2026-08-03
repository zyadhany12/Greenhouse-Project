#ifndef _EXTI_INTERFACE_H
#define _EXTI_INTERFACE_H

#include <stdint.h>
#include "../DIO/DIO_Interface.h"
#include "EXTI_Private.h"
#include "EXTI_Config.h"

void EXTI_Init(uint8_t Interrupt, uint8_t SensConfig);
void EXTI_Enable(uint8_t Interrupt);
void EXTI_Disable(uint8_t Interrupt);

#endif