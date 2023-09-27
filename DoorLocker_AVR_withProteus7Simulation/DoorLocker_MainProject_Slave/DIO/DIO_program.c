/*
 * DIO_program.c
 *
 *  Created on: Apr 25, 2022
 *      Author: KARIM
 */

#include "../LIB/std_types.h"
#include "../LIB/bitmath.h"

#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"


void DIO_voidSetPinDirection(u8 cpy_u8PortNumber, u8 cpy_u8PinNo, u8 cpy_u8Direction)
{
	if((cpy_u8PortNumber <= DIO_PORTD) && (cpy_u8PinNo <= DIO_PIN7))
	{
		if(cpy_u8Direction == DIO_OUTPUT)
		{
			switch(cpy_u8PortNumber)
			{
			case DIO_PORTA:
				SET_BIT(DDRA,cpy_u8PinNo);
				break;
			case DIO_PORTB:
				SET_BIT(DDRB,cpy_u8PinNo);
				break;
			case DIO_PORTC:
				SET_BIT(DDRC,cpy_u8PinNo);
			break;
			case DIO_PORTD:
				SET_BIT(DDRD,cpy_u8PinNo);
				break;
			}
		}
		else if(cpy_u8Direction == DIO_INPUT)
		{
			switch(cpy_u8PortNumber)
			{
			case DIO_PORTA:
				CLR_BIT(DDRA,cpy_u8PinNo);
				break;
			case DIO_PORTB:
				CLR_BIT(DDRB,cpy_u8PinNo);
				break;
			case DIO_PORTC:
				CLR_BIT(DDRC,cpy_u8PinNo);
				break;
			case DIO_PORTD:
				CLR_BIT(DDRD,cpy_u8PinNo);
				break;
			}
		}
	}
	else
	{
		/* Do nothing, Wrong value to set */
	}
}

void DIO_voidSetPinValue(u8 cpy_u8PortNumber, u8 cpy_u8PinNo, u8 cpy_u8Value)
{
	if((cpy_u8PortNumber <= DIO_PORTD) && (cpy_u8PinNo <= DIO_PIN7))
	{
		if(cpy_u8Value == DIO_HIGH)
		{
			switch(cpy_u8PortNumber)
			{
			case DIO_PORTA:
				SET_BIT(PORTA,cpy_u8PinNo);
				break;
			case DIO_PORTB:
				SET_BIT(PORTB,cpy_u8PinNo);
				break;
			case DIO_PORTC:
				SET_BIT(PORTC,cpy_u8PinNo);
			break;
			case DIO_PORTD:
				SET_BIT(PORTD,cpy_u8PinNo);
				break;
			}
		}
		else if(cpy_u8Value == DIO_LOW)
		{
			switch(cpy_u8PortNumber)
			{
			case DIO_PORTA:
				CLR_BIT(PORTA,cpy_u8PinNo);
				break;
			case DIO_PORTB:
				CLR_BIT(PORTB,cpy_u8PinNo);
				break;
			case DIO_PORTC:
				CLR_BIT(PORTC,cpy_u8PinNo);
			break;
			case DIO_PORTD:
				CLR_BIT(PORTD,cpy_u8PinNo);
				break;
			}
		}
	}
	else
	{
		/* Do nothing , wrong direction required*/
	}

}

u8 DIO_u8GetPinValue(u8 cpy_u8PortNumber, u8 cpy_u8PinNo)
{
	/*define local variable for receiving bit value*/
	u8 u8PinValLocal = 0;
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if((cpy_u8PortNumber <= DIO_PORTD) && (cpy_u8PinNo <= DIO_PIN7))
	{
		switch(cpy_u8PortNumber)
		{
			case DIO_PORTA:
				u8PinValLocal = GET_BIT(PinA,cpy_u8PinNo);
				break;
			case DIO_PORTB:
				u8PinValLocal = GET_BIT(PinB,cpy_u8PinNo);
				break;
			case DIO_PORTC:
				u8PinValLocal = GET_BIT(PinC,cpy_u8PinNo);
				break;
			case DIO_PORTD:
				u8PinValLocal = GET_BIT(PinD,cpy_u8PinNo);
				break;
		}
	}
	else
	{
		u8PinValLocal = 0xFF;
	}
	return u8PinValLocal;
}

void DIO_voidTogglePinValue(u8 cpy_u8PortNumber, u8 cpy_u8PinNo)
{
	u8 pinValue;
	pinValue = DIO_u8GetPinValue(cpy_u8PortNumber, cpy_u8PinNo);
	pinValue = pinValue==DIO_LOW ? DIO_HIGH: DIO_LOW;
	DIO_voidSetPinValue(cpy_u8PortNumber, cpy_u8PinNo, pinValue);
}

void DIO_voidSetPortDirection(u8 cpy_u8PortNumber, u8 cpy_u8Direction)
{
	if((cpy_u8PortNumber <= DIO_PORTD))
	{
		switch(cpy_u8PortNumber)
		{
			case DIO_PORTA:
				DDRA = cpy_u8Direction;
				break;
			case DIO_PORTB:
				DDRB = cpy_u8Direction;
				break;
			case DIO_PORTC:
				DDRC = cpy_u8Direction;
				break;
			case DIO_PORTD:
				DDRD = cpy_u8Direction;
				break;
		}
	}
	else
	{
		/*wrong port*/
	}
}
void DIO_voidSetPortValue(u8 cpy_u8PortNumber, u8 cpy_u8Value)
{
	if((cpy_u8PortNumber <= DIO_PORTD))
		{
			switch(cpy_u8PortNumber)
			{
				case DIO_PORTA:
					PORTA = cpy_u8Value;
					break;
				case DIO_PORTB:
					PORTB = cpy_u8Value;
					break;
				case DIO_PORTC:
					PORTC = cpy_u8Value;
					break;
				case DIO_PORTD:
					PORTD = cpy_u8Value;
					break;
			}
		}
		else
		{
			/*wrong port*/
		}
}
u8 DIO_u8GetPortValue(u8 cpy_u8PortNumber)
{
	/*define local variable for receiving bit value*/
	u8 u8PinValLocal = 0;
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if((cpy_u8PortNumber <= DIO_PORTD))
	{
		switch(cpy_u8PortNumber)
		{
			case DIO_PORTA:
				u8PinValLocal = PinA;
				break;
			case DIO_PORTB:
				u8PinValLocal = PinB;
				break;
			case DIO_PORTC:
				u8PinValLocal = PinC;
				break;
			case DIO_PORTD:
				u8PinValLocal = PinD;
				break;
		}
	}
	else
	{
		u8PinValLocal = 0x00;
	}
	return u8PinValLocal;}
