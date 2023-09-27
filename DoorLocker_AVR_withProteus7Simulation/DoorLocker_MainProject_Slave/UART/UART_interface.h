/*
 * UART_interface.h
 *
 *  Created on: Aug 13, 2022
 *      Author: KARIM
 */

#ifndef UART_UART_INTERFACE_H_
#define UART_UART_INTERFACE_H_

void UART_voidInit(void);
void UART_voidSetBaudRate(u16 cpy_u16Baudrate);
void UART_voidSendByte(u8 cpy_u8Byte);
void UART_voidReadByte(u8* cpy_pu8Byte);
void UART_voidPrintString(char str[]);
void UART_voidReadString(u8 str[], u16 size);

u8 UART_voidGetByte(void);

void UART_voidEnableInterrupts(void);
void UART_voidDisableInterrupts(void);
void UART_voidSetCallback(void (*CBFPTR)(u8));

#endif /* UART_UART_INTERFACE_H_ */
