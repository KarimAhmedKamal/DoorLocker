/*
 * TWI_private.h
 *
 *  Created on: Aug 30, 2022
 *      Author: KARIM
 */

#ifndef TWI_TWI_PRIVATE_H_
#define TWI_TWI_PRIVATE_H_

#define TWBR	*((volatile u8*)(0x20))
#define TWCR	*((volatile u8*)(0x56))
#define TWSR	*((volatile u8*)(0x21))
#define TWDR	*((volatile u8*)(0x23))
#define TWAR	*((volatile u8*)(0x22))

/*#define TWBR0	0
#define TWBR1	1
#define TWBR2	2
#define TWBR3	3
#define TWBR4	4
#define TWBR5	5
#define TWBR6	6
#define TWBR7	7*/

#define TWIE	0
// reserved		1
#define TWEN	2
#define TWWC	3
#define TWSTO	4
#define TWSTA	5
#define TWEA	6
#define TWINT	7

#define TWPS0	0
#define TWPS1	1
/*#define TWS3	3
#define TWS4	4
#define TWS5	5
#define TWS6	6
#define TWS7	7*/

#define TWGCE	0



#endif /* TWI_TWI_PRIVATE_H_ */
