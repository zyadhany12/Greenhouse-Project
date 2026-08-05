#include "STATEMACHINE/stateMachine_Interface.h"

void main()
{
    WaterPump_Init(Dio_GroupD, Dio_Pin2);
    Heater_Init(Dio_GroupD, Dio_Pin1);
    Fan_Init(Dio_GroupD, Dio_Pin0);
    Button_Init(Dio_GroupA, Dio_Pin0);
    Button_Init(Dio_GroupA, Dio_Pin1);
    Button_Init(Dio_GroupA, Dio_Pin2);

    while (1)
    {
        if (Button_GetState(Dio_GroupA, Dio_Pin0) == BUTTON_PRESSED)
        {
            _delay_ms(50); // Simple software debounce

            while (Button_GetState(Dio_GroupD, 0) != BUTTON_NOT_PRESSED)
            {
                // To prevent freezing the whole system, you usually want to call
                // your sensor-reading or LCD-updating functions in here as well.
            }

            Fan_On();
            Heater_Off();
        }
        // 2. Check the correct HEATER button variables
        else if (Button_GetState(Dio_GroupA, Dio_Pin1) == BUTTON_PRESSED)
        {
            _delay_ms(50);

            while (Button_GetState(Dio_GroupA, Dio_Pin1) != BUTTON_NOT_PRESSED)
            {
            }

            Heater_Toggle();
            Fan_Off();
        }
        // 3. This one looks structurally correct, just added debounce
        if (Button_GetState(Dio_GroupA, Dio_Pin2) == BUTTON_PRESSED)
        {
            _delay_ms(50);

            while (Button_GetState(Dio_GroupA, Dio_Pin2) != BUTTON_NOT_PRESSED)
            {
            }
            WaterPump_Toggle();
        }
    }
}