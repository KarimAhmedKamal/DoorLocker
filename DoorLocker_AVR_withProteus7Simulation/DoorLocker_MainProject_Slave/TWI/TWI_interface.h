/*
 * TWI_interface.h
 *
 *  Created on: Aug 30, 2022
 *      Author: KARIM
 */

#ifndef TWI_TWI_INTERFACE_H_
#define TWI_TWI_INTERFACE_H_

#define TWI_READ	1
#define TWI_WRITE	0
#define TWI_ACK		1
#define TWI_NACK	0

/* Status codes */
#define TWI_START	0x08
#define TWI_RESTART	0x10

void TWI_voidInit( void );
u8 TWI_u8SendStart( void );
u8 TWI_u8SendSlaveAddress( u8 cpy_u8Sla, u8 cpy_u8RW );
u8 TWI_u8SendData( u8 cpy_u8Data );
u8 TWI_u8ReadData( u8 * cpy_puData, u8 cpy_u8Ack );
u8 TWI_u8StopCondition( void );

#endif /* TWI_TWI_INTERFACE_H_ */
