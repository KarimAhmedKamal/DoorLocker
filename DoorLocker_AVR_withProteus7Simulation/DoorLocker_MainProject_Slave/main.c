/*
 * main.c
 *
 *  Created on: May 31, 2022
 *      Author: KARIM
 */

#include "LIB/std_types.h"
#include "DIO/DIO_interface.h"
#include "GIE/GIE_interface.h"
#include "UART/UART_interface.h"
#include "TWI/TWI_interface.h"
#include "TIMERS_revision/TIMERS_interface.h"
#include "util/delay.h"

#define BUZZER					10
#define DOOR_OPEN				11
#define CHANGE_PASS				12

#define EEPROM_ADDR	0b01010000
#define user_length 10

volatile u8 buzzer_flag = 0;
volatile u8 door_flag = 0;
volatile u8 changePass_flag = 0;

volatile u8 buffer[user_length]={0};
volatile u8 buffer_index = 0;

void EEPROM_WriteByte(u8 byte, u16 addr)
{
	TWI_u8SendStart();
	TWI_u8SendSlaveAddress(EEPROM_ADDR, TWI_WRITE);
	TWI_u8SendData(addr);
	TWI_u8SendData(byte);
	TWI_u8StopCondition();
}

u8 EEPROM_ReadByte(u16 addr)
{
	u8 byte = 0;
	TWI_u8SendStart();
	TWI_u8SendSlaveAddress(EEPROM_ADDR, TWI_WRITE);
	TWI_u8SendData(addr);
	TWI_u8SendStart();
	TWI_u8SendSlaveAddress(EEPROM_ADDR, TWI_READ);

	TWI_u8ReadData(&byte, TWI_NACK);
	TWI_u8StopCondition();
	return byte;
}

void uart_rx(u8 data){
	if(data == BUZZER){
		buzzer_flag = 1;
	}
	else if(data == DOOR_OPEN){
		door_flag = 1;
	}
	else if(data == CHANGE_PASS){
		changePass_flag = 1;
	}
	else{
		buffer[buffer_index] = data;
		buffer_index = (buffer_index + 1)%user_length;
	}
}

int main(void) {
	u8 readPasswordFlag = 0;
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN2, DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN5, DIO_OUTPUT);
	UART_voidInit();
	UART_voidSetCallback(uart_rx);
	TIMERS_voidInit();
	TIMERS_voidSetICR1Value(TIMER1, 2500); // Tovf = 20ms as required for this servo used
	TIMERS_voidStartTimer(TIMER1);
	TWI_voidInit();
	GIE_voidEnableGlobalInterrupts();
	_delay_ms(10);

	// set default password as ten 1's to use in proteus eeprom
	for(u8 i = 0; i < user_length; i++){
		EEPROM_WriteByte(1,i);
		_delay_ms(20);
	}

	while (1) {
		if(readPasswordFlag == 0){
			readPasswordFlag = 1;
			for(u8 i = 0; i < user_length; i++){
				UART_voidSendByte(EEPROM_ReadByte(i));
			}
		}
//		UART_voidSendByte(1);
		if(buzzer_flag == 1 && changePass_flag == 0){
			buzzer_flag = 0;
			DIO_voidSetPinValue(DIO_PORTD, DIO_PIN2, DIO_HIGH);
			_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);
			DIO_voidSetPinValue(DIO_PORTD, DIO_PIN2, DIO_LOW);
		}
		else if(door_flag == 1){
			door_flag = 0;
			// open door
			TIMERS_voidSetOCRValue(TIMER1, 186); // [124 - 249] --> 180° range
			_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);
			_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);_delay_ms(200);
			// close door
			TIMERS_voidSetOCRValue(TIMER1, 124); // [124 - 249] --> 180° range
		}
		else if(changePass_flag == 1){
//			changePass_flag = 0;
			while(buffer[0] == 0){
				// wait
			}
			for(u8 i = 0; i < user_length; i++){
				EEPROM_WriteByte(buffer[i], i);
				_delay_ms(20);
				buffer[i] = 0; // clear buffer
			}
			buffer_index = 0;
			changePass_flag = 0;
			readPasswordFlag = 0; // send new pass
		}
	}
}
