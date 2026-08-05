#include "LM35_Interface.h"

static uint8_t Pin = 0;
void LM35_Init(uint8_t PinNumber)
{
    DIO_InitPin(Dio_GroupA,PinNumber,Input);
    Pin = PinNumber;
}

uint8_t LM35_GetTemp()
{
    uint16_t Digital_Value;
    uint16_t Temp_in_Cels;

    Digital_Value = ADC_ReadChannelPolling(Pin);
    Temp_in_Cels = (Digital_Value * (uint32_t)Voltage) / resolution;
    return Temp_in_Cels;
}