/*
 * DIO_interface.h
 *
 *  Created on: Apr 25, 2022
 *      Author: KARIM
 */

#ifndef DIO_DIO_INTERFACE_H_
#define DIO_DIO_INTERFACE_H_

#define DIO_PORTA   0 // kaatabtaha hna badal el private 3ashan ana 3aiz asta5dmha fl function call fl main
#define DIO_PORTB   1
#define DIO_PORTC   2
#define DIO_PORTD   3

#define DIO_PIN0	0
#define DIO_PIN1	1
#define DIO_PIN2    2
#define DIO_PIN3    3
#define DIO_PIN4    4
#define DIO_PIN5    5
#define DIO_PIN6    6
#define DIO_PIN7    7

#define DIO_INPUT   0
#define DIO_OUTPUT  1

#define DIO_HIGH    1
#define DIO_LOW     0

void DIO_voidSetPinDirection(u8 cpy_u8PortNumber, u8 cpy_u8PinNo, u8 cpy_u8Direction);
void DIO_voidSetPinValue(u8 cpy_u8PortNumber, u8 cpy_u8PinNo, u8 cpy_u8Value);
u8   DIO_u8GetPinValue(u8 cpy_u8PortNumber, u8 cpy_u8PinNo);
void DIO_voidTogglePinValue(u8 cpy_u8PortNumber, u8 cpy_u8PinNo);

void DIO_voidSetPortDirection(u8 cpy_u8PortNumber, u8 cpy_u8Direction);
void DIO_voidSetPortValue(u8 cpy_u8PortNumber, u8 cpy_u8Value);
u8 DIO_u8GetPortValue(u8 cpy_u8PortNumber);

#endif /* DIO_DIO_INTERFACE_H_ */
