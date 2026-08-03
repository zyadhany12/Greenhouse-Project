#include "LCD_Interface.h"
#include <util/delay.h>

void LCD_WriteData(uint8_t Data, uint8_t ModeType)
{
    if (ModeType == Lcd_8bitMode)
    {
        // RS -> 1
        DIO_WritePin(Lcd_RSGroup, Lcd_RSPin, High);
        // RW -> 0
        DIO_WritePin(Lcd_RWGroup, Lcd_RWPin, Low);
        // Update Data
        DIO_WriteGroup(Lcd_DataGroup, Data);
        // E ->
        DIO_WritePin(Lcd_EGroup, Lcd_EPin, High);
        // wait
        _delay_ms(1);
        // E ->
        DIO_WritePin(Lcd_EGroup, Lcd_EPin, Low);
    }

    else if (ModeType == Lcd_4bitMode)
    {
        // 1. Set RS (1) for Data, Clear RW (0) for Write
        SetBit(PORTB_Reg, 0);
        ClearBit(PORTB_Reg, 1);

        // 2. Send HIGH Nibble (Top 4 bits)
        PORTB_Reg = (PORTB_Reg & 0x0F) | (Data & 0xF0);
        SetBit(PORTB_Reg, 2); // Pulse EN
        _delay_ms(1);
        ClearBit(PORTB_Reg, 2);
        _delay_ms(1);

        // 3. Send LOW Nibble (Bottom 4 bits shifted to the top)
        PORTB_Reg = (PORTB_Reg & 0x0F) | (Data << 4);
        SetBit(PORTB_Reg, 2); // Pulse EN
        _delay_ms(1);
        ClearBit(PORTB_Reg, 2);
        _delay_ms(2);
    }
}

void LCD_WriteInstruction(uint8_t Instruction, uint8_t ModeType)
{
    if(ModeType==Lcd_8bitMode)
    {
    // RS -> 1 
    DIO_WritePin(Lcd_RSGroup,Lcd_RSPin,Low);
    // RW -> 0
    DIO_WritePin(Lcd_RWGroup,Lcd_RWPin,Low);
    // Update Data 
    DIO_WriteGroup(Lcd_DataGroup,Instruction);
    // E -> 
    DIO_WritePin(Lcd_EGroup,Lcd_EPin,High);
    // wait 
    _delay_ms(1);
    // E -> 
    DIO_WritePin(Lcd_EGroup,Lcd_EPin,Low);
    }

    else if (ModeType == Lcd_4bitMode)
    {
        ClearBit(PORTB_Reg, 0);
        ClearBit(PORTB_Reg, 1);

        PORTB_Reg = (PORTB_Reg & 0x0F) | (Instruction & 0xF0);
        SetBit(PORTB_Reg, 2); // Pulse EN
        _delay_ms(1);
        ClearBit(PORTB_Reg, 2);
        _delay_ms(1);

        PORTB_Reg = (PORTB_Reg & 0x0F) | (Instruction << 4);
        SetBit(PORTB_Reg, 2);
        _delay_ms(1);
        ClearBit(PORTB_Reg, 2);
        _delay_ms(2);
    }
}

void LCD_Init(uint8_t ModeType)
{
    if (ModeType==Lcd_8bitMode)
    {
        //RS pin as output 
        DIO_InitPin(Lcd_RSGroup,Lcd_RSPin,Output);
        DIO_InitPin(Lcd_RWGroup,Lcd_RWPin,Output);
        DIO_InitPin(Lcd_EGroup,Lcd_EPin,Output);
        //Data
        DIO_InitGroup(Lcd_DataGroup,0xFF);
        // 8 bit Mode Init
        _delay_ms(35);
        LCD_WriteInstruction(Lcd_8bitMode2Line5x8F,Lcd_8bitMode);
        _delay_ms(1);
        LCD_WriteInstruction(Lcd_CursorOn,Lcd_8bitMode);
        _delay_ms(1);
        LCD_WriteInstruction(Lcd_ClearScreen,Lcd_8bitMode);
        _delay_ms(2);
        LCD_WriteInstruction(Lcd_EntryMode1,Lcd_8bitMode);
        _delay_ms(1);

    }
    else if (ModeType == Lcd_4bitMode)
    {
        DIO_InitPin(Lcd_RSGroup, Lcd_RSPin, Output);
        DIO_InitPin(Lcd_RWGroup, Lcd_RWPin, Output);
        DIO_InitPin(Lcd_EGroup, Lcd_EPin, Output);

        DIO_InitPin(Lcd_DataGroup, Dio_Pin4, Output);
        DIO_InitPin(Lcd_DataGroup, Dio_Pin5, Output);
        DIO_InitPin(Lcd_DataGroup, Dio_Pin6, Output);
        DIO_InitPin(Lcd_DataGroup, Dio_Pin7, Output);
        _delay_ms(35);


        LCD_WriteInstruction(0x33, Lcd_4bitMode);
        _delay_ms(5);
        LCD_WriteInstruction(0x32, Lcd_4bitMode);
        _delay_ms(1);

        // 0x28 = 4-bit mode, 2 lines, 5x8 font
        LCD_WriteInstruction(0x28, Lcd_4bitMode);
        _delay_ms(1);

        LCD_WriteInstruction(Lcd_4BitModeCursorOff, Lcd_4bitMode);
        _delay_ms(1);
        LCD_WriteInstruction(Lcd_ClearScreen, Lcd_4bitMode);
        _delay_ms(2);
        LCD_WriteInstruction(Lcd_4BitEntryMode1, Lcd_4bitMode);
        _delay_ms(1);
    }
}

void LCD_WriteString(char *String, uint8_t ModeType)
{
    if(String!=Null)
    {   
        uint8_t count = 0 ;
        while(String[count]!='\0')
        {
            LCD_WriteData(String[count],ModeType);
            count++;
        }
    }
}


void LCD_GotoXY(uint8_t X, uint8_t Y)
{
    uint8_t DigitAddress = 0;
    switch (X)
    {
    case 0:
        DigitAddress = 0x00 + Y;
        break;
    case 1:
        DigitAddress = 0x40 + Y;
        break;
    }
    LCD_WriteInstruction(DigitAddress | 0x80, Lcd_8bitMode);
    _delay_ms(1);
}


void LCD_Clear(void)
{
    LCD_WriteInstruction(Lcd_ClearScreen, Lcd_8bitMode);
    _delay_ms(2);
}


void LCD_WriteNumber(uint8_t number, uint8_t ModeType)
{
    char arr[10];
    int i = 0;

    if (number == 0)
    {
        LCD_WriteData('0', ModeType);
        return;
    }

    while (number > 0)
    {
        arr[i] = (number % 10) + '0'; 
        number = number / 10;        
        i++;
    }

    for (int j = i - 1; j >= 0; j--)
    {
        LCD_WriteData(arr[j], ModeType);
    }
}