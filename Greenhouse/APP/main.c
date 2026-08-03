#include "stateMachine_Interface.h"



void main()
{
    TIMER0_SetCallBackFunction(Timer0_CompareMatchInterrupt,System_Timer);
   GreenHouse_Init();
   while(1)
   {
    StateMachine_ClimateControll();
   }
   
   }
   /* 
   LCD_Init(Lcd_8bitMode);
   LCD_WriteString("Welcome :)",Lcd_8bitMode);  
   */
    

