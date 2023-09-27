#ifndef _BIT_MATH_H
#define _BIT_MATH_H
#define SET_BIT(byte,bit) ((byte) |=  (1<<(bit)))
#define CLR_BIT(byte,bit) ((byte) &=~ (1<<(bit)))
#define TOG_BIT(byte,bit) ((byte) ^=  (1<<(bit)))
#define GET_BIT(byte,bit) ( ( (byte) >> (bit) ) & 1 )
#endif
