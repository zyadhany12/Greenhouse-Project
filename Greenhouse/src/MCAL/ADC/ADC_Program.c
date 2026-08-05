#include "ADC_Interface.h"


 
void ADC_Init(Adc_Config_t  Configuration)
{
    if(Configuration.ReferenceSelection==Adc_AREF)
    {
        ClearBit(ADCSRA_Reg,Adc_REFS0);
        ClearBit(ADCSRA_Reg,Adc_REFS1);
    }
    else if(Configuration.ReferenceSelection==Adc_AVCC)
    {
        SetBit(ADCSRA_Reg,Adc_REFS0);
        ClearBit(ADCSRA_Reg,Adc_REFS1);
    }
    else if(Configuration.ReferenceSelection==Adc_Internal)
    {
        SetBit(ADCSRA_Reg,Adc_REFS0);
        SetBit(ADCSRA_Reg,Adc_REFS1);     
    }
    if(Configuration.AdjustResult==Adc_LeftAdjust)
    {
        SetBit(ADMUX_Reg,Adc_ADLAR);
    }
    else if (Configuration.AdjustResult==Adc_RightAdjust)
    {
        ClearBit(ADMUX_Reg,Adc_ADLAR);
    }
    if(Configuration.InterruptState==Enable)
    {
        SetBit(ADCSRA_Reg,Adc_ADIE);
    }
    else if(Configuration.InterruptState==Disable)
    {
        ClearBit(ADCSRA_Reg,Adc_ADIE);
    }
    if (Configuration.AutomaticModel==AutoMode)
    {
        SetBit(ADCSRA_Reg,Adc_ADATE);
        // Select Trigger Source 
    }
    else if (Configuration.AutomaticModel==SingleMode)
    {
        ClearBit(ADCSRA_Reg,Adc_ADATE);
    }
    // Reg=(Reg&~Mask)|Value
    ADCSRA_Reg=(ADCSRA_Reg&~Adc_PrescalerMask)|(Configuration.PrescallerSelection);
    //Enable for ADC 
    SetBit(ADCSRA_Reg,Adc_ADEN);
}

// 
uint16_t ADC_ReadChannelPolling(uint8_t Channel)
{
    // Update Channel ADMUX 4 - 0 
    ADMUX_Reg=(ADMUX_Reg&~Adc_ChannelMask)|Channel;
    // Start Conversion 
    SetBit(ADCSRA_Reg,Adc_ADSC);

    while(ReadFlag(ADCSRA_Reg,Adc_ADIF)!=FlagUp); //waiting 
    //Manual Flag Clear 
    ClearFlag(ADCSRA_Reg,Adc_ADIF);

    return ADCData_Reg;
}
// 
void ADC_StartConvserionInterrupt(uint8_t Channel)
{
    ADMUX_Reg=(ADMUX_Reg&~Adc_ChannelMask)|Channel;
    SetBit(ADCSRA_Reg,Adc_ADSC);
}