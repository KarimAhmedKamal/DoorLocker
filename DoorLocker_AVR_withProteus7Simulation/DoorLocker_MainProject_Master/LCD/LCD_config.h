/*
 * LCD_config.h
 *
 *  Created on: May 17, 2022
 *      Author: KARIM
 */

#ifndef LCD_LCD_CONFIG_H_
#define LCD_LCD_CONFIG_H_

// Task 4-bits mode

#define LCD_CTRL_PORT 		DIO_PORTC
#define LCD_DATA_PORT 		DIO_PORTA
#define LCD_RS_PIN	  		DIO_PIN0
#define LCD_RW_PIN	  		DIO_PIN1
#define LCD_EN_PIN	  		DIO_PIN2

#define LCD_CURSOR_SHOW		ON
#define LCD_CURSOR_BLINK 	OFF

#endif /* LCD_LCD_CONFIG_H_ */
