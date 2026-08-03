#include "stateMachine_Interface.h"

static uint8_t Count = 0;           // 200 => 50ms
static uint16_t Interrupt_Flag = 0; // it sets to 1 every 50ms, When enters the System_Update it resets to zero
static GreenHouse_States_t CurrentState = GreenHouse_Monitoring;
static uint8_t ControlMode = GreenHouse_Automatic;
static uint8_t No_FullCycle = 0; // 1 full cycle is supposed to = 50ms
static uint16_t SensorSamplingTime;
static uint8_t Temp = 0;
static uint8_t Moist = 0;
static uint8_t MaxTemp = 45;
static uint8_t MinTemp = 25;
static uint8_t Critical_MaxTemp = 70;
static uint8_t Critical_MinTemp = 10;
static uint8_t MinMoist = 35;
static uint8_t Critical_Moist = 15;
static ConfigMenuState_t MenuState = MENU_HOME;
static uint8_t UserSelection = 0;
static uint16_t TempValue = 0; // Temporarily holds the digits the user types
static uint8_t NeedDisplayUpdate = 1;
uint8_t CurrState_Fan = 0;
uint8_t CurrState_Heater = 0;
uint8_t CurrState_Pump = 0;
static uint8_t PrevState_Fan = 0;
static uint8_t PrevState_Heater = 0;
static uint8_t PrevState_Pump = 0;
static char Current_Value = 0;
static char Previous_Value = 0;

Adc_Config_t Adc_Config =
    {
        .ReferenceSelection = Adc_AVCC,
        .AdjustResult = Adc_LeftAdjust,
        .AutomaticModel = AutoMode,
        .InterruptState = Disable,
        .PrescallerSelection = Adc_Prescaler_8,
};

TIMER0_Config_t Timer0_Config =
    {
        .TimerMode = Timer0_CTCMode,
        .PreloadValue = 0,
        .CompareMatchValue = 250,
        .PWMOutputMode = 0,
        .DutyCycleInitValue = 0,
};

void System_Timer()
{
    Count++;
    if (Count == 200) // 200 count = 50ms in the system
    {
        Interrupt_Flag = 1;
        Count = 0;
    }
}
void GreenHouse_Init()
{
    // Enabling MCAL
    GIE_Enable();
    ADC_Init(Adc_Config);
    TIMER0_Init(Timer0_Config);

    // Enabling HAL
    KPD_Init();
    Led_Init(HotLed_Group, HotLed_Pin);
    Led_Init(ColdLed_Group, ColdLed_Pin);
    Led_Init(MoistLed_Group, MoistLed_Pin);
    WaterPump_Init(WaterPump_Group, WaterPump_Pin);
    Heater_Init(Heater_Group, Heater_Pin);
    Fan_Init(Fan_Group, Fan_Pin);
    LCD_Init(Lcd_8bitMode);
    POT_Init(MoistSens_Pin);
    LM35_Init(TempSens_Pin);
    WaterPump_Off();
    Heater_Off();
    Fan_Off();
    LCD_WriteString("System Starting", Lcd_8bitMode2Line5x8F);
    _delay_ms(1500);
}

void GreenHouse_Update()
{
    if (Interrupt_Flag == 1) // to limit CPU spamming??
    {
        Interrupt_Flag = 0;
        No_FullCycle++;

        switch (CurrentState)
        {
        case GreenHouse_Monitoring:
            StateMachine_ClimateControl_Monitor();

            if (ControlMode == GreenHouse_Automatic)
            {
                CurrentState = GreenHouse_Automatic;
            }
            else if (ControlMode == GreenHouse_Manual)
            {
                CurrentState = GreenHouse_Manual;
            }
            if (No_FullCycle >= 10)
            {
                No_FullCycle = 0; // Safely resets without breaking % 2 or % 5
            }

            break;

        case GreenHouse_Automatic:

            StateMachine_ClimateControll_Controll();
            if (Temp >= Critical_MaxTemp || Moist <= Critical_Moist || Temp <= Critical_MinTemp)
            {
                CurrentState = GreenHouse_Alarm;
            }
            else if (KPD_GetButtonValue() == '*')
            {
                Fan_Off();
                Heater_Off();
                WaterPump_Off();
                CurrentState = GreenHouse_Configuration;
            }

            break;
        case GreenHouse_Manual:
        {
            CurrState_Fan = Button_GetState(Fan_Group, Fan_Pin);
            CurrState_Heater = Button_GetState(Heater_Group, Heater_Pin);
            CurrState_Pump = Button_GetState(WaterPump_Group, WaterPump_Pin);
            PrevState_Fan = 0;
            PrevState_Heater = 0;
            PrevState_Pump = 0;

            if (CurrState_Fan == BUTTON_PRESSED && PrevState_Fan == 0 && Button_GetState(Fan_Group, Fan_Pin) == BUTTON_NOT_PRESSED)
            {
                Fan_Toggle();
                Heater_Off();
            }
            else if (CurrState_Heater == BUTTON_PRESSED && PrevState_Heater == 0 && Button_GetState(Heater_Group, Heater_Pin) == BUTTON_NOT_PRESSED)
            {
                Fan_Off();
                Heater_Toggle();
            }
            if (CurrState_Pump == BUTTON_PRESSED && PrevState_Pump == 0)
            {
                WaterPump_Toggle();
            }
            if (Temp >= Critical_MaxTemp || Moist <= Critical_Moist)
            {
                CurrentState = GreenHouse_Alarm;
            }
            else if (KPD_GetButtonValue() == '*')
            {
                Fan_Off();
                Heater_Off();
                WaterPump_Off();
                CurrentState = GreenHouse_Configuration;
            }
            PrevState_Fan = CurrState_Fan;
            PrevState_Heater = CurrState_Heater;
            PrevState_Pump = CurrState_Pump;

            break;
        }
        case GreenHouse_Configuration:
        {

            Current_Value = KPD_GetButtonValue();
            Previous_Value = 0;

            // KEYPAD EDGE DETECTION
            if (Current_Value != 0 && Previous_Value == 0)
            {
                if (MenuState == MENU_HOME)
                {
                    if (Current_Value >= '1' && Current_Value <= '5')
                    {
                        UserSelection = Current_Value - '0'; // Convert from Char to Int ex. '0' = 48  '1' = 49 => '1' - '0' = 1
                        TempValue = 0;                       // Reset the typed value
                        MenuState = MENU_EDITING;            // Switch to editing mode
                        NeedDisplayUpdate = 1;
                    }
                    else if (Current_Value == '*') // pressed to EXIT config mode
                    {
                        CurrentState = GreenHouse_Monitoring;
                        MenuState = MENU_HOME;
                        NeedDisplayUpdate = 1;
                        LCD_Clear();
                    }
                }

                else if (MenuState == MENU_EDITING)
                {
                    if (Current_Value >= '0' && Current_Value <= '9')
                    {
                        TempValue = (TempValue * 10) + (Current_Value - '0');
                        NeedDisplayUpdate = 1;
                    }
                    else if (Current_Value == '*') // pressed to SAVE
                    {
                        // Internal StateMachine
                        switch (UserSelection)
                        {
                        case 1:
                            MaxTemp = TempValue;
                            break;
                        case 2:
                            MinTemp = TempValue;
                            break;
                        case 3:
                            MinMoist = TempValue;
                            break;
                        case 4:
                            SensorSamplingTime = TempValue;
                            break;
                        case 5:
                            if (TempValue == 1)
                            {
                                ControlMode = GreenHouse_Automatic;
                            }
                            else
                            {
                                ControlMode = GreenHouse_Manual;
                            }
                            break;
                            MenuState = MENU_HOME; // Go back to the menu
                            NeedDisplayUpdate = 1;
                        }
                    }
                    else if (Current_Value == '#') //  pressed to CANCEL/BACKSPACE
                    {
                        MenuState = MENU_HOME; // Abort and go back
                        NeedDisplayUpdate = 1;
                    }
                }
            }

            // Save current state for the next cycle
            Previous_Value = Current_Value;

            // 3. DISPLAY RENDERING (ONLY ON CHANGES)
            if (NeedDisplayUpdate)
            {
                LCD_Clear();
                if (MenuState == MENU_HOME)
                {
                    // You might need a 4-line LCD, or just show 2 at a time!
                    LCD_GotoXY(0, 0);
                    LCD_WriteString("1:Max 2:Min 3:Mst", Lcd_8bitMode2Line5x8F);
                    LCD_GotoXY(1, 0);
                    LCD_WriteString("4:Time 5:Mode C:Ex", Lcd_8bitMode2Line5x8F);
                }
                else if (MenuState == MENU_EDITING)
                {
                    LCD_GotoXY(0, 0);
                    LCD_WriteString("Enter New Value:", Lcd_8bitMode2Line5x8F);
                    LCD_GotoXY(1, 0);
                    LCD_WriteNumber(TempValue, Lcd_8bitMode2Line5x8F);
                }
                NeedDisplayUpdate = 0;
            }

            break;
        }

        case GreenHouse_Alarm:
            if ((No_FullCycle % 4) == 0)
            {
                Temp = LM35_GetTemp();
                Moist = POT_GetMoisture();
            }
            if (Temp >= Critical_MaxTemp)
            {
                Led_on(HotLed_Group, HotLed_Pin, SourceConnection);
                Fan_On();
                Heater_Off();
            }
            else if (Temp <= Critical_MinTemp)
            {
                Led_on(ColdLed_Group, ColdLed_Pin, SourceConnection);
                Heater_On();
                Fan_Off();
            }
            if (Moist <= Critical_Moist)
            {
                Led_on(MoistLed_Group, MoistLed_Pin, SourceConnection);
                WaterPump_On();
            }
            if (Moist > Critical_Moist && Temp > Critical_MinTemp && Temp < Critical_MaxTemp)
            {
                Led_off(ColdLed_Group, ColdLed_Pin, SourceConnection);
                Led_off(MoistLed_Group, MoistLed_Pin, SourceConnection);
                Led_off(HotLed_Group, HotLed_Pin, SourceConnection);
                CurrentState = GreenHouse_Monitoring;
            }
            break;
        default:
            break;
        }
    }
}
