#include "SOIL_SENSOR_Interface.h"

static uint8_t Pin = 0;
void POT_Init(uint8_t PinNumber)
{
    DIO_InitPin(Dio_GroupA,PinNumber,Input);
    Pin = PinNumber;
}

uint8_t POT_GetMoisture()
{
    uint8_t ADC_Value = ADC_ReadChannelPolling(Pin);
    uint8_t humidity = (uint8_t)(((uint32_t) ADC_Value * ScaledMax) / (uint32_t)RawMax) ;
    return humidity;
}
