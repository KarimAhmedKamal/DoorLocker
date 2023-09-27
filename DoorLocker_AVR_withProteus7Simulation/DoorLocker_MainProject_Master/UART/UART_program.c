/*
 * UART_program.c
 *
 *  Created on: Aug 13, 2022
 *      Author: KARIM
 */


#include "../LIB/std_types.h"
#include "../LIB/bitmath.h"
#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"

static void (*Global_Rx_Callback)(u8) = {NULL};

void UART_voidInit(void)
{
	/* 1- interrupt enable */
	/* 1a- RX complete Int Enable*/
	/* 1b- TX complete Int Enable*/
	/* 1c- UDRE Interrupt enable*/
	CLR_BIT(UCSRB, RXCIE);
	CLR_BIT(UCSRB, TXCIE);
	CLR_BIT(UCSRB, UDRIE);
	/* 2- enable Reciever and Transmitter*/
	SET_BIT(UCSRB, RXEN);
	SET_BIT(UCSRB, TXEN);
	/* 3- select character size*/
	/* 4- select USART mode*/
	/* 5- select parity mode*/
	/* 6- select number if stop bits*/
	u8 UCSRC_setting = 0; // temp
	SET_BIT(UCSRC_setting, URSEL);
	SET_BIT(UCSRC_setting, UCSZ1);
	SET_BIT(UCSRC_setting, UCSZ0);
	UCSRC = UCSRC_setting ;
	CLR_BIT(UCSRB, UCSZ2);
	/* 7- select Baud rate*/
	// 9600 -> UBRR=51
	UBRRL = 51;
}

void UART_voidSetBaudRate(u16 cpy_u16Baudrate)
{

}

void UART_voidSendByte(u8 cpy_u8Byte)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR = cpy_u8Byte;
}

void UART_voidReadByte(u8* cpy_pu8Byte)
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) )
	;
	/* Get and return received data from buffer */
	*cpy_pu8Byte = UDR;
}

u8 UART_voidGetByte(void)
{
	return UDR;
}

void UART_voidPrintString(char str[])
{
	for(u16 i = 0; str[i] != '\0'; i++)
	{
		UART_voidSendByte(str[i]);
	}
}

void UART_voidReadString(u8 str[], u16 size)
{
	u8 flag = 0;
	for(u16 i = 0; i < size; i++)
	{
		UART_voidReadByte(&str[i]);
		if(str[i] == '\n')
		{
			flag = 1;
			str[i] = '\0';
			break;
		}
	}
	if(flag == 0)
	{
		str[size-1] = '\0';
	}
}

void UART_voidSetCallback(void (*CBFPTR)(u8))
{
	Global_Rx_Callback = CBFPTR;
}

void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
	if(Global_Rx_Callback != NULL)
	{
		Global_Rx_Callback(UDR);
	}
}
