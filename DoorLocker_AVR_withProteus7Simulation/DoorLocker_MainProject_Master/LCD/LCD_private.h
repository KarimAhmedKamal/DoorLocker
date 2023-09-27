/*
 * LCD_private.h
 *
 *  Created on: May 17, 2022
 *      Author: KARIM
 */

#ifndef LCD_LCD_PRIVATE_H_
#define LCD_LCD_PRIVATE_H_

#define ON 	1
#define OFF 0

#define LCD_FUNCTION_SET   0b00111000// Function set
#define LCD_ENTRY_MODE_SET 0b00001100 //Display ON/OFF Control
#define LCD_CLEAR_DISPLAY  0b00000001	// Display Clear
#define LCD_SEND_COMMAND   0b00000110 // Entry Mode Set

#endif /* LCD_LCD_PRIVATE_H_ */
