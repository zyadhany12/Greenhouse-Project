#ifndef SENSOR_INTERFACE_H_
#define SENSOR_INTERFACE_H_

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/ADC/ADC_Interface.h"
#include <stdint.h>
#include "SOIL_SENSOR_Private.h"



void POT_Init(uint8_t PinNumber);

uint8_t POT_GetMoisture();


#endif