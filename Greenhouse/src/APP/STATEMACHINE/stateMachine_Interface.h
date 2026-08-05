#ifndef STATEMAHINE_H_
#define STATEMAHINE_H_

#include <stdint.h>
#include "stateMahcine_Config.h"
#include <util/delay.h>
#include "stateMachine_Private.h"
#include "../CLIMATECONTROL/climateControl_Interface.h"
#include "../../MCAL/GIE/GIE_Interface.h"
#include "../../MCAL/ADC/ADC_Interface.h"
#include "../../HAL/KPD/KPD_Interface.h"
#include "../../HAL/LCD/LCD_Interface.h"
#include "../../HAL/LED/LED_Interface.h"
#include "../../HAL/LM35/LM35_Interface.h"
#include "../../HAL/SOIL_SENSOR/SOIL_SENSOR_Interface.h"
#include "../../HAL/RELAY/RELAY_Interface.h"
#include "../../HAL/RELAY/RELAY_Interface.h"
#include "../../HAL/BTN/BTN_Interface.h"
#include "../../MCAL/TIMER0/TIMER0_Interface.h"

typedef enum
{
    GreenHouse_Monitoring,
    GreenHouse_Manual,
    GreenHouse_Automatic,
    GreenHouse_Configuration,
    GreenHouse_Alarm,
} GreenHouse_States_t;

typedef enum
{
    MENU_HOME,
    MENU_EDITING,
} ConfigMenuState_t;


void GreenHouse_Init();
void System_Timer();
void GreenHouse_Update();

#endif