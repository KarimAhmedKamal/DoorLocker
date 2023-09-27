/*
 * TIMERS_private.h
 *
 *  Created on: Apr 8, 2023
 *      Author: Karim
 */

#ifndef TIMERS_REVISION_TIMERS_PRIVATE_H_
#define TIMERS_REVISION_TIMERS_PRIVATE_H_

#define ENABLE	1
#define DISABLE 0

#define TIMSK *((volatile u8*) (0x59))
#define TIFR  *((volatile u8*) (0x58))

/***************************************************/
/********************** TIMER 0 ********************/
#define TCCR0 *((volatile u8*) (0x53))
#define TCNT0 *((volatile u8*) (0x52))
#define OCR0  *((volatile u8*) (0x5C))

#define FOC0	7
#define WGM00	6
#define WGM01	3
#define COM00	4
#define COM01	5
#define CS00	0
#define CS01	1
#define CS02	2

#define TOIE0	0
#define OCIE0	1

#define TOV0	0
#define OCF0	1

#define TIMER0_NORMAL				0
#define TIMER0_PHASECORRECT_PWM		1
#define TIMER0_CTC					2
#define TIMER0_FAST_PWM				3

#define NON_PWM_TOGGLE_ON_COMPARE_MATCH		4
#define NON_PWM_CLR_ON_COMPARE_MATCH		5
#define NON_PWM_SET_ON_COMPARE_MATCH		6
#define FAST_PWM_CLR_ON_COMPARE_MATCH_TOP	7
#define FAST_PWM_SET_ON_COMPARE_MATCH_TOP	8
#define PHASE_CORRECT_PWM_CLR_UP_SET_DOWN	9
#define PHASE_CORRECT_PWM_CLR_DOWN_SET_UP	10

#define PS_1							0b001
#define PS_8							0b010
#define PS_64							0b011
#define PS_256							0b100
#define PS_1024							0b101
#define EXTERNAL_CLK_SRC_FALLINGEDGE	0b110
#define EXTERNAL_CLK_SRC_RISINGEDGE		0b111
/***************************************************/

/********************** TIMER 2 ********************/
#define TCCR2 *((volatile u8*) (0x45))
#define TCNT2 *((volatile u8*) (0x44))
#define OCR2  *((volatile u8*) (0x43))
#define ASSR  *((volatile u8*) (0x42))

#define FOC2	7
#define WGM20	6
#define WGM21	3
#define COM20	4
#define COM21	5
#define CS20	0
#define CS21	1
#define CS22	2

#define TOIE2	6
#define OCIE2	7

#define TOV2	6
#define OCF2	7

#define AS2		3
#define TCN2UB	2
#define OCR2UB	1
#define TCR2UB	0

#define TIMER2_NORMAL				0
#define TIMER2_PHASECORRECT_PWM		1
#define TIMER2_CTC					2
#define TIMER2_FAST_PWM				3

#define TIMER2_CTC_TOGGLE			4
#define TIMER2_CTC_CLEAR			5
#define TIMER2_CTC_SET				6
#define TIMER2_FASTPWM_CLEAR		7
#define TIMER2_FASTPWM_SET			8
#define TIMER2_PHASECORRECT_CLEAR	9
#define TIMER2_PHASECORRECT_SET		10

#define PS2_1							0b001
#define PS2_8							0b010
#define PS2_32							0b011
#define PS2_64							0b100
#define PS2_128							0b101
#define PS2_256							0b110
#define PS2_1024						0b111

#define TIMER2_INTERNAL_CLOCK	0
#define TIMER2_EXTERNAL_CLOCK	1

/***************************************************/

/********************** TIMER 1 ********************/
#define TCCR1A *((volatile u8*) 	(0x4F))
#define TCCR1B *((volatile u8*) 	(0x4E))
#define TCNT1L *((volatile u16*) 	(0x4C))
#define TCNT1H *((volatile u8*) 	(0x4D))
#define OCR1AL *((volatile u16*) 	(0x4A))
#define OCR1AH *((volatile u8*) 	(0x4B))
#define OCR1BL *((volatile u16*) 	(0x48))
#define OCR1BH *((volatile u8*) 	(0x49))
#define ICR1L  *((volatile u16*) 	(0x46))
#define ICR1H  *((volatile u8*) 	(0x47))

#define COM1A1	7
#define COM1A0	6
#define COM1B1	5
#define COM1B0	4
#define FOC1A	3
#define FOC1B	2
#define WGM11	1
#define WGM10	0

#define ICNC1	7
#define ICES1	6
/* pin 5 RESERVED*/
#define WGM13	4
#define WGM12	3
#define CS12	2
#define CS11	1
#define CS10	0

#define TICIE1	5
#define OCIE1A	4
#define OCIE1B	3
#define TOIE1	2

#define ICF1	5
#define OCF1A	4
#define OCF1B	3
#define TOV1	2

/***************************************************/
#endif /* TIMERS_REVISION_TIMERS_PRIVATE_H_ */
