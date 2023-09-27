/*
 * LCD_interface.h
 *
 *  Created on: May 17, 2022
 *      Author: KARIM
 */

#ifndef LCD_LCD_INTERFACE_H_
#define LCD_LCD_INTERFACE_H_

void LCD_voidInit(void);
void LCD_voidSendCommand(u8 cpy_u8Command);
void LCD_voidSendChar(u8 cpy_u8Character); // ASCII Character
void LCD_voidPrintString(u8 ptr_u8ArrCharacter[]); // ASCII Character
void LCD_voidSaveCustomChar(u8 u8_arr[], u8 cpy_u8cgram_address);//save char in CGRAM
void LCD_voidPrintNumber(s32 cpy_s32Number); // Sent Number Not String
void LCD_voidPrintFloat(f32 cpy_f32Number); // Sent Number Not String
void LCD_voidSetCursorPosition(u8 cpy_u8LineNumber, u8 cpy_u8CharacterPosition); // Sent Number Not String

#endif /* LCD_LCD_INTERFACE_H_ */
