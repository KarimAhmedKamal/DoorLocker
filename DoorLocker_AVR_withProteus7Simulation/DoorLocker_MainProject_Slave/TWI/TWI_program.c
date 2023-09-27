/*
 * TWI_program.c
 *
 *  Created on: Aug 30, 2022
 *      Author: KARIM
 */


#include "../LIB/std_types.h"
#include "../LIB/bitmath.h"

#include "TWI_interface.h"
#include "TWI_private.h"
#include "TWI_config.h"

void TWI_voidInit( void )
{
	/* 1- Set Bit Rate and prescaler bits */
	TWBR = 10;// min 10
	TWSR = (TWSR & 0xF8) | TWI_PRESCALER;
	/* 2- En/Dis Interrupt */
	CLR_BIT(TWCR, TWIE);
	/* 3- Enable TWI peripheral */
	SET_BIT(TWCR, TWEN);
	/* 4- in slave mode load Own SLA */
	TWAR = TWI_OWN_SLA << 1;
	/* 5- General Call Recognition */

}

u8 TWI_u8SendStart( void )
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)))
	{}

	return (TWSR & 0xF8) ;
}

u8 TWI_u8SendSlaveAddress( u8 cpy_u8Sla, u8 cpy_u8RW )
{
	TWDR = (cpy_u8Sla<<1) | cpy_u8RW;
	TWCR = (1<<TWINT) | (1<<TWEN);
	/* TWSTA must be cleared by software when the START condition
has been transmitted */
	CLR_BIT(TWCR, TWSTA);
	while (!(TWCR & (1<<TWINT)))
	{}
	return (TWSR & 0xF8) ;
}

u8 TWI_u8SendData( u8 cpy_u8Data )
{
	TWDR = cpy_u8Data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)))
	{}
	return (TWSR & 0xF8) ;
}

u8 TWI_u8ReadData( u8 * cpy_puData, u8 cpy_u8Ack )
{
	/* - send Ack pulse */
	if(cpy_u8Ack == 1)
	{
		TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	}
	else
	{
		CLR_BIT(TWCR,TWEA);
		TWCR = (1<<TWINT) | (1<<TWEN);
	}
	/* - wait for flag */
	while (!(TWCR & (1<<TWINT)))
	{}
	/* - Read Data */
	*cpy_puData = TWDR;
	/* - Return status*/
	return (TWSR & 0xF8) ;
}

u8 TWI_u8StopCondition( void )
{
	TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);
	return (TWSR & 0xF8);
}
