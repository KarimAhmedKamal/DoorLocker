/*
 * TIMERS_interface.h
 *
 *  Created on: Apr 8, 2023
 *      Author: Karim
 */

#ifndef TIMERS_REVISION_TIMERS_INTERFACE_H_
#define TIMERS_REVISION_TIMERS_INTERFACE_H_

#define TIMER0	0
#define TIMER1	1
#define TIMER2	2

#define TIMER0_CTC_INTERRUPT		0
#define TIMER0_OVERFLOW_INTERRUPT	1
#define TIMER2_CTC_INTERRUPT		2
#define TIMER2_OVERFLOW_INTERRUPT	3

void TIMERS_voidInit(void);
void TIMERS_voidStartTimer( u8 cpy_u8TimerID );
void TIMERS_voidStopTimer( u8 cpy_u8TimerID );
void TIMERS_voidSetCallback( u8 cpy_u8TimerID, u8 cpy_u8CallbackType, void (*TimerCallback)(void) );
void TIMERS_voidSetPreloadValue( u8 cpy_u8TimerID, u16 cpy_u16Preload );
void TIMERS_voidSetOCRValue( u8 cpy_u8TimerID, u16 cpy_u16Value );
void TIMERS_voidEnableInterrupt(u8 cpy_u8TimerID, u8 cpy_u8InterruptID);
void TIMERS_voidDisableInterrupt(u8 cpy_u8TimerID, u8 cpy_u8InterruptID);
void TIMERS_voidSetICR1Value(u8 cpy_u8TimerID, u16 cpy_u16Value);

#endif /* TIMERS_REVISION_TIMERS_INTERFACE_H_ */
