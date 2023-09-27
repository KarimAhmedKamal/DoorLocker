/*
 * LCD_program.c
 *
 *  Created on: May 17, 2022
 *      Author: KARIM
 */

#include "../LIB/std_types.h"
#include "../DIO/DIO_interface.h"
#include <util/delay.h>

#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"

void LCD_voidInit(void)
{
	// init Pins direction
	// RS
	DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_RS_PIN, DIO_OUTPUT);
	// RW
	DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_RW_PIN, DIO_OUTPUT);
	// E
	DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_EN_PIN, DIO_OUTPUT);
	// Data Pins
	DIO_voidSetPortDirection(LCD_DATA_PORT, 0xff);

	// LCD initialization
	_delay_ms(50);
	// Function set
	LCD_voidSendCommand(LCD_FUNCTION_SET);
	_delay_ms(1);
	// Display ON/OFF Control
	LCD_voidSendCommand(LCD_ENTRY_MODE_SET | (LCD_CURSOR_SHOW<<1) | (LCD_CURSOR_BLINK<<1));
	_delay_ms(1);
	// Display Clear
	LCD_voidSendCommand(LCD_CLEAR_DISPLAY);
	_delay_ms(2);
	// Entry Mode Set
	LCD_voidSendCommand(LCD_SEND_COMMAND);
	_delay_ms(5);
}

void LCD_voidSendCommand(u8 cpy_u8Command)
{
	// RS -> LOW
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, DIO_LOW);
	// RW -> LOW
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, DIO_LOW);
	// DB pins -> command
	DIO_voidSetPortValue(LCD_DATA_PORT, cpy_u8Command);
	// Pulse Enable
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, DIO_HIGH);
	_delay_ms(1);
	// Pulse Disable
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, DIO_LOW);
	_delay_ms(1);
}

void LCD_voidSendChar(u8 cpy_u8Character)
{
	// RS -> HIGH
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, DIO_HIGH);
	// RW -> LOW
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, DIO_LOW);
	// DB pins -> command
	DIO_voidSetPortValue(LCD_DATA_PORT, cpy_u8Character);
	// Pulse Enable
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, DIO_HIGH);
	_delay_ms(1);
	// Pulse Disable
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, DIO_LOW);
	_delay_ms(1);
}

void LCD_voidPrintString(u8 ptr_u8ArrCharacter[])
{
	for (u8 i = 0; ptr_u8ArrCharacter[i] != '\0'; i++)
	{
		LCD_voidSendChar(ptr_u8ArrCharacter[i]);
	}
}

void LCD_voidSaveCustomChar(u8 u8_arr[], u8 cpy_u8cgram_address)
{
	//set CGRAM Address
	if(cpy_u8cgram_address < 8)
	{
		//0b01000000 -> 0x40
		LCD_voidSendCommand(0x40 + (8*cpy_u8cgram_address));

		for(u8 i=0; i<8; i++)
		{
			LCD_voidSendChar(u8_arr[i]);
		}
		//0b10000000 -> 0x80
		LCD_voidSendCommand(0x80);
	}
}

void LCD_voidPrintNumber(s32 cpy_s32Number)
{
	u32 reversedNo = 0;
	u8 rightZeroesCounter = 0;
	// handling negative sign on screen
	if (cpy_s32Number < 0 )
	{
		LCD_voidSendChar('-');
		cpy_s32Number *= -1;
	}
	// reversing number
	while (cpy_s32Number > 0)
	{
		reversedNo = reversedNo * 10 + (cpy_s32Number%10);
		cpy_s32Number /= 10;
		if(reversedNo == 0)
		{
			rightZeroesCounter ++;
		}
	}
	// printing number
	while (reversedNo > 0)
	{
		LCD_voidSendChar( (reversedNo%10) +'0' );
		reversedNo /= 10;
	}
	for(u8 i = 0; i < rightZeroesCounter; i++)
	{
		LCD_voidSendChar( '0' );
	}
}

void LCD_voidPrintFloat(f32 cpy_f32Number)
{
	u32 noAfterDecimalPt = 0;
	// Print number before point
	LCD_voidPrintNumber((s32) cpy_f32Number);
	// print point
	LCD_voidSendChar('.');

	// print number after point
	// we know that float f32 Precision = 6 digits
	if (cpy_f32Number<0) cpy_f32Number *= -1; // convert it to +ve
	noAfterDecimalPt = (u32) ( ( cpy_f32Number - ( (u32) cpy_f32Number ) ) * (10^6) );
	while(noAfterDecimalPt != 0 && noAfterDecimalPt % 10 == 0) //check the number after point is not zero and check for right zeroes to remove pefore printing
	{
		noAfterDecimalPt %= 10;
	}
	// print number after point
	LCD_voidPrintNumber(noAfterDecimalPt);
}

void LCD_voidSetCursorPosition(u8 cpy_u8LineNumber, u8 cpy_u8CharacterPosition)
{
	switch(cpy_u8LineNumber)
	{
		case 0:
			LCD_voidSendCommand(0x80 + (cpy_u8CharacterPosition + 0) );
			break;
		case 1:
			LCD_voidSendCommand(0x80 + (cpy_u8CharacterPosition + 64) );
			break;
	}
}
