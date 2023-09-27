/*
 * main.c
 *
 *  Created on: May 31, 2022
 *      Author: KARIM
 */

#include "LIB/std_types.h"
#include "GIE/GIE_interface.h"
#include "UART/UART_interface.h"
#include "KEYPAD/KEYPAD_interface.h"
#include "LCD/LCD_interface.h"
#include "util/delay.h"

// queue -> FIFO buffer: first In First Out
//#define BUF_SZ 	10
//volatile u8 byte = 0;
//volatile u8 buffer[BUF_SZ]={0};
//volatile u8 buffer_index = 0;

#define ENTER_KEY				16
#define PASS_LENGTH				10
#define MAX_WRONG_PASS_COUNT	3
#define BUZZER					10
#define DOOR_OPEN				1
#define CHANGE_PASS				2
#define DOOR_OPEN_S				11
#define CHANGE_PASS_S			12

//void uart_rx(u8 data)
//{
//	buffer[buffer_index] = data;
//	buffer_index = (buffer_index + 1)%BUF_SZ;
//}

void DefaultMessage(void);
void ClearUserPassword(u8* password);
//void uart_rx(u8 data);

int main(void) {
	// 1- Set and get default pass from eeprom
	// 2- login. If failed 3, times buzzer works for 10 secs.
	// 3- If login succeeded, show 2 options: open door, change pass. Opening door requires pass again.
	// 4- After finishing close door and show after logging options

	u8 DEFAULT_PASSWORD[PASS_LENGTH] = { 0 };
	u8 newPassFlag = 1;
	UART_voidInit();
	KEYPAD_voidInit();
	LCD_voidInit();
//	UART_voidSetCallback(uart_rx);
//	GIE_voidEnableGlobalInterrupts();
	// read password from UART communication
//	for (u8 i = 0; i < PASS_LENGTH; i++) {
//		UART_voidReadByte(DEFAULT_PASSWORD + i);
//	}

	u8 key = 0;
	u8 clrLCD = 0;
	u8 pressedKeysCounter = 0;
	u8 password[PASS_LENGTH] = { 0 };
	u8 passCheckMatchingFlag = 1;
	u8 wrongPassCheckCounter = 0; // 0-2
	u8 changePasswordFullyEnteredFlag = 0;
	// First message shown to user
	DefaultMessage();

	while (1) {
		// password read if changed
		if(newPassFlag == 1){
			ClearUserPassword(password);
			newPassFlag = 0;
			ClearUserPassword(DEFAULT_PASSWORD);
			// read password from UART communication
			for (u8 i = 0; i < PASS_LENGTH; i++) {
				UART_voidReadByte(DEFAULT_PASSWORD + i);
			}
		}
		// Get Keypad Pressed Key
		key = KEYPAD_u8GetPressedKey();
		// Make sure that the user entered input type number
		if (key != 0 && key != ENTER_KEY && key < PASS_LENGTH - 1) {
			// Display Clear at first iteration
			if (clrLCD == 0) {
				clrLCD = 1;
				// CLR Screen
				LCD_voidSendCommand(1);
			} else {
				; // do nothing
			}
			// check length of entered pass as we accept first 10 inputs only
			if (pressedKeysCounter < PASS_LENGTH) {
				password[pressedKeysCounter] = key;
				LCD_voidSendChar('*');
				pressedKeysCounter++;
			} else {
				// do nothing////
			}

		} else if (key == ENTER_KEY) { // check password matching
			// Clear screen
			LCD_voidSendCommand(0b00000001);
			// Return LCD Cursor to first character
			LCD_voidSetCursorPosition(0, 0);
			// Check password byte by byte
			for (u8 i = 0; i < PASS_LENGTH; i++) {
				if (DEFAULT_PASSWORD[i] != password[i]) {
					passCheckMatchingFlag = 0;
					break;
				}
			}
			// clear Entered password after checking
			pressedKeysCounter = 0;
			// CLR password array
			ClearUserPassword(password);
			if (passCheckMatchingFlag == 1) { // if password is correct
				// show success message
				LCD_voidPrintString("Login Succeeded!");
				_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);
				// CLR Screen
				LCD_voidSendCommand(1);
				// Show two choides to user (1- Open Door 2- Change Pass)
				LCD_voidPrintString("1- Open Door");
				LCD_voidSetCursorPosition(1, 0);
				LCD_voidPrintString("2- Change Pass");
				// stuck here till chosing right choice
				while (key != DOOR_OPEN && key != CHANGE_PASS) {
					// keyboard pressed key
					key = KEYPAD_u8GetPressedKey();
					if (key == DOOR_OPEN) {
						// send open door order to the other avr
						UART_voidSendByte(DOOR_OPEN_S);
						_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);
						_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);
						DefaultMessage();
						clrLCD = 0;
					}
					else if(key == CHANGE_PASS){
						UART_voidSendByte(CHANGE_PASS_S);
						changePasswordFullyEnteredFlag = 0;
						// LCD CLR
						LCD_voidSendCommand(1);
						while( changePasswordFullyEnteredFlag == 0 ){
							// Get Keypad Pressed Key
							key = KEYPAD_u8GetPressedKey();
							if (key != 0 && key != ENTER_KEY && key < PASS_LENGTH - 1) {
								// check length of entered pass as we accept first 10 inputs only
								if (pressedKeysCounter < PASS_LENGTH) {
									password[pressedKeysCounter] = key;
									LCD_voidSendChar('*');
									pressedKeysCounter++;
								} else {
									// do nothing////
								}
							}
							else if(key == ENTER_KEY){
								UART_voidSendByte(CHANGE_PASS_S);
								// clear Entered password after checking
//								pressedKeysCounter = 0;
								for (u8 i = 0; i < PASS_LENGTH; i++) {
									UART_voidSendByte(password[i]);
								}
								ClearUserPassword(password);
								pressedKeysCounter = 0;
								changePasswordFullyEnteredFlag = 1;
								newPassFlag = 1;
								key = CHANGE_PASS;
							}
						}
						DefaultMessage();
						clrLCD = 0;
					}
				}
			} else { // wrong pass
				if (wrongPassCheckCounter == (MAX_WRONG_PASS_COUNT - 1)) {
					wrongPassCheckCounter = 0;
					passCheckMatchingFlag = 1;
					LCD_voidPrintString("Login Failed!!!!!!");
					UART_voidSendByte(BUZZER);
					_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);
					DefaultMessage();
					clrLCD = 0;
				} else {
					wrongPassCheckCounter++;
					passCheckMatchingFlag = 1;
					LCD_voidPrintString("Wrong Password");
					LCD_voidSetCursorPosition(1, 0);
					LCD_voidPrintString("Try again!");
					_delay_ms(200);
					LCD_voidSendCommand(1);
				}
			}
		} else {
			// do nothing
		}
	}
}

//void uart_rx(u8 data){
//	newPassFlag = 1;
//}

void DefaultMessage(void) {
	// First message shown to user
	LCD_voidSendCommand(1);
	LCD_voidSetCursorPosition(0, 0);
	LCD_voidPrintString("Enter Your Pass");
	LCD_voidSetCursorPosition(1, 1);
	LCD_voidPrintString("max 10 digits");
}

void ClearUserPassword(u8* password){
	// CLR password array
	for (u8 i = 0; i < PASS_LENGTH; i++) {
		password[i] = 0;
	}
}
