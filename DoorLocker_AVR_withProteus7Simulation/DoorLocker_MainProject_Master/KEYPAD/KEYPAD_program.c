/*
 * KEYPAD_program.c
 *
 *  Created on: May 31, 2022
 *      Author: KARIM
 */

#include "../LIB/std_types.h"
#include "../DIO/DIO_interface.h"
#include <util/delay.h>

#include "KEYPAD_interface.h"
#include "KEYPAD_private.h"
#include "KEYPAD_config.h"


void KEYPAD_voidInit(void)
{
	DIO_voidSetPortDirection(KEYPAD_PORT, 0xF0);
	DIO_voidSetPortValue(KEYPAD_PORT, 0xFF);
//	DIO_voidSetPinDirection(DIO_PORTD, 0, 1);
}
u8 KEYPAD_u8GetPressedKey(void)
{
	u8 loc_u8pressed_key = 0;

	for(u8 loc_u8ColNo = 0; loc_u8ColNo < 4; loc_u8ColNo++)
	{
		DIO_voidSetPinValue(KEYPAD_PORT, loc_u8ColNo+4, DIO_LOW);
//		DIO_voidSetPinValue(DIO_PORTD, 0, 0);
		for(u8 loc_u8RowNo = 0; loc_u8RowNo < 4; loc_u8RowNo++)
		{
			if( DIO_u8GetPinValue(KEYPAD_PORT, loc_u8RowNo) == 0 )
			{
				loc_u8pressed_key = (loc_u8RowNo*4) + (loc_u8ColNo+1);
			}
			while( DIO_u8GetPinValue(KEYPAD_PORT, loc_u8RowNo) ==0 ) {}//do nothing (debouncing)
			_delay_ms(10);
		}
		DIO_voidSetPinValue(KEYPAD_PORT, loc_u8ColNo+4, DIO_HIGH);

	}
	return loc_u8pressed_key;
}
