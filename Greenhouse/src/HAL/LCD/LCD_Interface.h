#ifndef LCD_Interface_H
#define LCD_Interface_H

#include "../../MCAL/DIO/DIO_Interface.h"
#include "LCD_Private.h"
#include "LCD_Config.h"


void LCD_Init(uint8_t ModeType);
void LCD_WriteData(uint8_t Data,uint8_t ModeType);
void LCD_WriteInstruction(uint8_t Instruction,uint8_t ModeType);
void LCD_WriteString(char *String, uint8_t ModeType);
void LCD_GotoXY(uint8_t X , uint8_t Y);
void LCD_WriteNumber(uint8_t Number,uint8_t ModeType);
void LCD_Clear(void);


#endif