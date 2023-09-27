/*
 * TIMERS_program.c
 *
 *  Created on: Apr 8, 2023
 *      Author: Karim
 */

#include "../LIB/std_types.h"
#include "../LIB/bitmath.h"
#include "../DIO/DIO_interface.h"

#include "TIMERS_interface.h"
#include "TIMERS_private.h"
#include "TIMERS_config.h"

static void (*Global_Timer0_Callbacks[2])(void) = {NULL };
static void (*Global_Timer2_Callbacks[2])(void) = {NULL };

void TIMERS_voidInit(void) {
	/* TIMER 0 */
	// 1 - Force Output compare (This bit, when set to ‘1’ forces an immediate compare match and affects the behaviour of OC0 pin. For ensuring compatibility with future devices, this bit must be set to ‘0’.)
	CLR_BIT(TCCR0, FOC0);
	// 2 - Waveform Generation Mode
#if TIMER0_MODE == TIMER0_NORMAL
	CLR_BIT(TCCR0, WGM00);
	CLR_BIT(TCCR0, WGM01);
#elif TIMER0_MODE == TIMER0_PHASECORRECT_PWM
	SET_BIT(TCCR0, WGM00);
	CLR_BIT(TCCR0, WGM01);
#elif TIMER0_MODE == TIMER0_CTC
	CLR_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);
#elif TIMER0_MODE == TIMER0_FAST_PWM
	SET_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);
#else
#error "TIMER0_MODE must be chosen from these options : (TIMER0_NORMAL - TIMER0_PHASECORRECT_PWM - TIMER0_CTC - TIMER0_FAST_PWM)"
#endif
	// 3 - Compare Match Output Mode
#if TIMER0_COMPARE_MODE == TIMER0_NORMAL
	CLR_BIT(TCCR0, COM00);
	CLR_BIT(TCCR0, COM01);
#elif TIMER0_COMPARE_MODE == NON_PWM_TOGGLE_ON_COMPARE_MATCH
	SET_BIT(TCCR0, COM00);
	CLR_BIT(TCCR0, COM01);
#elif TIMER0_COMPARE_MODE == NON_PWM_CLR_ON_COMPARE_MATCH || TIMER0_COMPARE_MODE == FAST_PWM_CLR_ON_COMPARE_MATCH_TOP || TIMER0_COMPARE_MODE == PHASE_CORRECT_PWM_CLR_UP_SET_DOWN
	CLR_BIT(TCCR0, COM00);
	SET_BIT(TCCR0, COM01);
#elif TIMER0_COMPARE_MODE == NON_PWM_SET_ON_COMPARE_MATCH || TIMER0_COMPARE_MODE == FAST_PWM_SET_ON_COMPARE_MATCH_TOP || TIMER0_COMPARE_MODE == PHASE_CORRECT_PWM_CLR_DOWN_SET_UP
	SET_BIT(TCCR0, COM00);
	SET_BIT(TCCR0, COM01);
#else
#error "TIMER0_COMPARE_MODE must be chosen from these options : (NON_PWM_NORMAL_PORT_OPERATION - NON_PWM_TOGGLE_ON_COMPARE_MATCH \
		- NON_PWM_CLR_ON_COMPARE_MATCH - NON_PWM_SET_ON_COMPARE_MATCH - FAST_PWM_CLR_ON_COMPARE_MATCH_TOP - FAST_PWM_SET_ON_COMPARE_MATCH_TOP \
		- PHASE_CORRECT_PWM_CLR_UP_SET_DOWN - PHASE_CORRECT_PWM_CLR_DOWN_SET_UP)"
#endif
	// 4 - Output Compare Match Interrupt Enable
#if TIMER0_CTC_INTERRUPT_EN == ENABLE
	SET_BIT(TIMSK, OCIE0);
#elif TIMER0_CTC_INTERRUPT_EN == DISABLE
	CLR_BIT(TIMSK, OCIE0);
#else
#error "TIMER0_CTC_INTERRUPT_EN must be chosen from these options : (ENABLE - DISABLE)"
#endif
	// 5 - Overflow Interrupt Enable
#if TIMER0_OVERFLOW_INTERRUPT_EN == ENABLE
	SET_BIT(TIMSK, TOIE0);
#elif TIMER0_OVERFLOW_INTERRUPT_EN == DISABLE
	CLR_BIT(TIMSK, TOIE0);
#else
#error "TIMER0_CTC_INTERRUPT_EN must be chosen from these options : (ENABLE - DISABLE)"
#endif
	// 6 - Stop timer
	TCCR0 = (TCCR0 & 0xF8) | 0;

	/**************************************************************************************************************************************************/
	/* TIMER 2 */
	// 1 - Force Output compare (This bit, when set to ‘1’ forces an immediate compare match and affects the behaviour of OC0 pin. For ensuring compatibility with future devices, this bit must be set to ‘0’.)
	CLR_BIT(TCCR2, FOC2);
	// 2 - Waveform Generation Mode
#if TIMER2_MODE == TIMER2_NORMAL
	CLR_BIT(TCCR2, WGM20);
	CLR_BIT(TCCR2, WGM21);
#elif TIMER2_MODE == TIMER2_PHASECORRECT_PWM
	SET_BIT(TCCR2, WGM20);
	CLR_BIT(TCCR2, WGM21);
#elif TIMER2_MODE == TIMER2_CTC
	CLR_BIT(TCCR2, WGM20);
	SET_BIT(TCCR2, WGM21);
#elif TIMER2_MODE == TIMER2_FAST_PWM
	SET_BIT(TCCR2, WGM20);
	SET_BIT(TCCR2, WGM21);
#else
#error "TIMER2_MODE must be chosen from these options : (TIMER0_NORMAL - TIMER0_PHASECORRECT_PWM - TIMER0_CTC - TIMER0_FAST_PWM)"
#endif
	// 3 - Compare Match Output Mode
#if TIMER2_COMPARE_MODE == TIMER2_NORMAL
	CLR_BIT(TCCR2, COM20);
	CLR_BIT(TCCR2, COM21);
#elif TIMER2_COMPARE_MODE == TIMER2_CTC_TOGGLE
	SET_BIT(TCCR2, COM20);
	CLR_BIT(TCCR2, COM21);
#elif TIMER2_COMPARE_MODE == TIMER2_CTC_CLEAR || TIMER2_COMPARE_MODE == TIMER2_FASTPWM_CLEAR || TIMER2_COMPARE_MODE == TIMER2_PHASECORRECT_CLEAR
	CLR_BIT(TCCR2, COM20);
	SET_BIT(TCCR2, COM21);
#elif TIMER2_COMPARE_MODE == TIMER2_CTC_SET || TIMER2_COMPARE_MODE == TIMER2_FASTPWM_SET || TIMER2_COMPARE_MODE == TIMER2_PHASECORRECT_SET
	SET_BIT(TCCR2, COM20);
	SET_BIT(TCCR2, COM21);
#else
#error "TIMER2_COMPARE_MODE must be chosen from these options : (TIMER2_NORMAL - TIMER2_CTC_TOGGLE \
		- TIMER2_CTC_SET - TIMER2_FASTPWM_CLEAR - TIMER2_FASTPWM_SET - TIMER2_PHASECORRECT_CLEAR \
		- TIMER2_PHASECORRECT_SET)"
#endif
	// 4 - Output Compare Match Interrupt Enable
#if TIMER2_CTC_INTERRUPT_EN == ENABLE
	SET_BIT(TIMSK, OCIE2);
#elif TIMER2_CTC_INTERRUPT_EN == DISABLE
	CLR_BIT(TIMSK, OCIE2);
#else
#error "TIMER2_CTC_INTERRUPT_EN must be chosen from these options : (ENABLE - DISABLE)"
#endif
	// 5 - Overflow Interrupt Enable
#if TIMER2_OVERFLOW_INTERRUPT_EN == ENABLE
	SET_BIT(TIMSK, TOIE2);
#elif TIMER2_OVERFLOW_INTERRUPT_EN == DISABLE
	CLR_BIT(TIMSK, TOIE2);
#else
#error "TIMER2_OVERFLOW_INTERRUPT_EN must be chosen from these options : (ENABLE - DISABLE)"
#endif
	// 6 - Stop timer
	TCCR2 = (TCCR2 & 0xF8) | 0;

	/**************************************************************************************************************************************************/
	/* TIMER 1 */

	CLR_BIT(TCCR1A, FOC1A);
	CLR_BIT(TCCR1A, FOC1B);

	CLR_BIT(TCCR1A, COM1A0);
	SET_BIT(TCCR1A, COM1A1);

	SET_BIT(TCCR1B, WGM13);
	SET_BIT(TCCR1B, WGM12);
	SET_BIT(TCCR1A, WGM11);
	CLR_BIT(TCCR1A, WGM10);

	CLR_BIT(TCCR1B, ICNC1);

	CLR_BIT(TCCR1B, ICES1);// icu rising
	CLR_BIT(TIMSK, TICIE1);// icu interrupt
	CLR_BIT(TIMSK, TOIE1);// ovf
	CLR_BIT(TIMSK, OCIE1A);// disable interrupt
	CLR_BIT(TIMSK, OCIE1B);// disable interrupt

}
void TIMERS_voidStartTimer(u8 cpy_u8TimerID) {
	//  - Pre-scaler (start timer)
	switch (cpy_u8TimerID) {
	case TIMER0:
		TCCR0 = (TCCR0 & 0xF8) | TIMER0_PRESCALER;
		break;
	case TIMER2:
		TCCR2 = (TCCR2 & 0xF8) | TIMER2_PRESCALER;
		break;
	case TIMER1:
		TCCR1B = (TCCR1B & 0xF8) | TIMER1_PRESCALER;
		break;
	}
}
void TIMERS_voidStopTimer(u8 cpy_u8TimerID) {
	//  - Pre-scaler (start timer)
	switch (cpy_u8TimerID) {
	case TIMER0:
		TCCR0 = (TCCR0 & 0xF8) | 0;
		break;
	case TIMER2:
		TCCR2 = (TCCR2 & 0xF8) | 0;
		break;
	case TIMER1:
		TCCR1B = (TCCR1B & 0xF8) | 0;
		break;
	}
}
void TIMERS_voidSetCallback(u8 cpy_u8TimerID, u8 cpy_u8CallbackType,
		void (*TimerCallback)(void)) {
	switch (cpy_u8TimerID) {
	case TIMER0:
		switch (cpy_u8CallbackType) {
		case TIMER0_CTC_INTERRUPT:
			Global_Timer0_Callbacks[cpy_u8CallbackType] = TimerCallback;
			break;
		case TIMER0_OVERFLOW_INTERRUPT:
			Global_Timer0_Callbacks[cpy_u8CallbackType] = TimerCallback;
			break;
		}
		break;
	case TIMER2:
		switch (cpy_u8CallbackType) {
		case TIMER2_CTC_INTERRUPT:
			Global_Timer2_Callbacks[cpy_u8CallbackType] = TimerCallback;
			break;
		case TIMER2_OVERFLOW_INTERRUPT:
			Global_Timer2_Callbacks[cpy_u8CallbackType] = TimerCallback;
			break;
		}
		break;
	}
}
void TIMERS_voidSetPreloadValue(u8 cpy_u8TimerID, u16 cpy_u16Preload) {
	switch (cpy_u8TimerID) {
	case TIMER0:
		TCNT0 = cpy_u16Preload;
		break;
	case TIMER2:
		TCNT2 = cpy_u16Preload;
		break;
	case TIMER1:
		TCNT1L = cpy_u16Preload;
		break;
	}
}
void TIMERS_voidSetOCRValue(u8 cpy_u8TimerID, u16 cpy_u16Value) {
	switch (cpy_u8TimerID) {
	case TIMER0:
		OCR0 = cpy_u16Value;
		break;
	case TIMER2:
		OCR2 = cpy_u16Value;
		break;
	case TIMER1:
		OCR1AL = cpy_u16Value;
		break;
	}
}
void TIMERS_voidEnableInterrupt(u8 cpy_u8TimerID, u8 cpy_u8InterruptID) {
	switch (cpy_u8TimerID) {
	case TIMER0:
		switch (cpy_u8InterruptID) {
		case TIMER0_CTC_INTERRUPT:
			SET_BIT(TIMSK, OCIE0);
			break;
		case TIMER0_OVERFLOW_INTERRUPT:
			SET_BIT(TIMSK, TOIE0);
			break;
		}
		break;
	case TIMER2:
		switch (cpy_u8InterruptID) {
		case TIMER2_CTC_INTERRUPT:
			SET_BIT(TIMSK, OCIE2);
			break;
		case TIMER2_OVERFLOW_INTERRUPT:
			SET_BIT(TIMSK, TOIE2);
			break;
		}
		break;
	}
}
void TIMERS_voidDisableInterrupt(u8 cpy_u8TimerID, u8 cpy_u8InterruptID) {
	switch (cpy_u8TimerID) {
	case TIMER0:
		switch (cpy_u8InterruptID) {
		case TIMER0_CTC_INTERRUPT:
			CLR_BIT(TIMSK, OCIE0);
			break;
		case TIMER0_OVERFLOW_INTERRUPT:
			CLR_BIT(TIMSK, TOIE0);
			break;
		case TIMER2_CTC_INTERRUPT:
			CLR_BIT(TIMSK, OCIE2);
			break;
		case TIMER2_OVERFLOW_INTERRUPT:
			CLR_BIT(TIMSK, TOIE2);
			break;
		}
		break;
	}
}
void TIMERS_voidSetICR1Value(u8 cpy_u8TimerID, u16 cpy_u16Value){
	ICR1L = cpy_u16Value;
}

void __vector_10(void) __attribute__((signal));
void __vector_10(void) {
	if (Global_Timer0_Callbacks[TIMER0_CTC_INTERRUPT] != NULL) {
		Global_Timer0_Callbacks[TIMER0_CTC_INTERRUPT]();
		SET_BIT(TIFR, OCF0);
	}
}

void __vector_11(void) __attribute__((signal));
void __vector_11(void) {
	if (Global_Timer0_Callbacks[TIMER0_OVERFLOW_INTERRUPT] != NULL) {
		Global_Timer0_Callbacks[TIMER0_OVERFLOW_INTERRUPT]();
		SET_BIT(TIFR, TOV0);
	}
}

void __vector_4(void) __attribute__((signal));
void __vector_4(void) {
	if (Global_Timer2_Callbacks[TIMER2_CTC_INTERRUPT] != NULL) {
		Global_Timer2_Callbacks[TIMER2_CTC_INTERRUPT]();
		SET_BIT(TIFR, OCF2);
	}
}

void __vector_5(void) __attribute__((signal));
void __vector_5(void) {
	if (Global_Timer2_Callbacks[TIMER2_OVERFLOW_INTERRUPT] != NULL) {
		Global_Timer2_Callbacks[TIMER2_OVERFLOW_INTERRUPT]();
		SET_BIT(TIFR, TOV2);
	}
}
