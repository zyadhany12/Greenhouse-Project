#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

#define Adc_REFS0         6
#define Adc_REFS1         7 

#define Adc_AREF          0
#define Adc_AVCC          1
#define Adc_Internal      2 

#define Adc_ADEN          7
#define Adc_ADSC          6 
#define Adc_ADATE         5
#define Adc_ADIF          4
#define Adc_ADIE          3
#define Adc_ADPS0         0
#define Adc_ADPS1         1
#define Adc_ADPS2         2

#define Adc_ADTS0         5
#define Adc_ADTS1         6
#define Adc_ADTS2         7


#define Adc_ADLAR         5 

#define Adc_RightAdjust   0 
#define Adc_LeftAdjust    1 

#define SingleMode    1
#define AutoMode      0

#define Adc_Prescaler_2      1
#define Adc_Prescaler_4      2
#define Adc_Prescaler_8      3
#define Adc_Prescaler_16     4
#define Adc_Prescaler_32     5
#define Adc_Prescaler_64     6
#define Adc_Prescaler_128    7


#define Adc_ChannelMask        0x1F
#define Adc_PrescalerMask      0x07
#define Adc_ADTSMask           0xE0

#define Adc_SingleEndedChannel0       0 
#define Adc_SingleEndedChannel1       1
#define Adc_SingleEndedChannel2       2
#define Adc_SingleEndedChannel3       3
#define Adc_SingleEndedChannel4       4
#define Adc_SingleEndedChannel5       5
#define Adc_SingleEndedChannel6       6
#define Adc_SingleEndedChannel7       7


typedef struct 
{
    uint8_t ReferenceSelection;
    uint8_t AdjustResult;
    uint8_t AutomaticModel;
    uint8_t InterruptState;
    uint8_t PrescallerSelection;
    
}Adc_Config_t;

#endif