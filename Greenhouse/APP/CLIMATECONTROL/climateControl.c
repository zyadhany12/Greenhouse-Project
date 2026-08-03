#include "climateControl_Interface.h"

static uint8_t Temp = 0;
static uint8_t Moist = 0;
static uint8_t ControlMode = GreenHouse_Automatic;
static uint8_t CurrentState = GreenHouse_Monitoring;
static uint8_t No_FullCycle = 0;
static uint8_t UI_Flag = 1;
uint8_t MaxTemp = 35;
uint8_t MinTemp = 15;
uint8_t MinMoist = 20;


void StateMachine_ClimateControl_Monitor()
{
    if (No_FullCycle % 2 == 0)
    {
        Temp = LM35_GetTemp();
        Moist = POT_GetMoisture();
    }
    if (No_FullCycle % 5 == 0)
    {
        LCD_WriteData(' ', Lcd_8bitMode);
        LCD_WriteString("Temp : ", Lcd_8bitMode);
        LCD_GotoXY(FirstRow, TempLocation);
        LCD_WriteString("        ", Lcd_8bitMode);
        LCD_GotoXY(FirstRow, TempLocation);
        LCD_WriteNumber(Temp, Lcd_8bitMode);
        LCD_GotoXY(SecondRow, Start_y);
        LCD_WriteString("Moist : ", Lcd_8bitMode);
        LCD_WriteNumber(Moist, Lcd_8bitMode);
        LCD_GotoXY(FirstRow, Start_y);
    }
    if (No_FullCycle >= 10)
    {
        No_FullCycle = 0; // Safely resets without breaking % 2 or % 5
    }
}

void StateMachine_ClimateControll_Controll()
{
    if (Temp > MaxTemp)
    {
        Fan_On();
        Heater_Off();
    }
    else if (Temp < MinTemp)
    {
        Fan_Off();
        Heater_On();
    }
    else
    {
        Fan_Off();
        Heater_Off();
    }
    if (Moist < MinMoist)
    {
        WaterPump_On();
    }
    else
    {
        WaterPump_Off();
    }
}
