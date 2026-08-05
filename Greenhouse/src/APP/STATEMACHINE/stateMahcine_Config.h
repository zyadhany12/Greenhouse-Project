#ifndef STATEMACHINE_CONFIG_H_
#define STATEMACHINE_CONFIG_H_



#define WaterPump_Group     Dio_GroupD
#define WaterPump_Pin       2
#define Heater_Group        Dio_GroupD
#define Heater_Pin          1
#define Fan_Group           Dio_GroupD
#define Fan_Pin             0

#define HotLed_Group        Dio_GroupD
#define HotLed_Pin          Dio_Pin3

#define ColdLed_Group       Dio_GroupD
#define ColdLed_Pin         Dio_Pin4

#define MoistLed_Group      Dio_GroupD
#define MoistLed_Pin        Dio_Pin5


#define TempSens_Pin    Dio_Pin0
#define MoistSens_Pin   Dio_Pin1


#define FanButton_Group Dio_GroupA
#define FanButton_Pin   Dio_Pin0
#define HeaterButton_Group Dio_GroupA
#define HeaterButton_Pin Dio_Pin1
#define PumpButton_Group Dio_GroupA
#define PumpButton_Pin Dio_Pin2
#define UserButton_Group Dio_GroupA
#define UserButton_Pin  Dio_Pin6

#endif