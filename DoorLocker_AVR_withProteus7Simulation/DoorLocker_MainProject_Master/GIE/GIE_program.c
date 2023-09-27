/*
 * GIE_program.c
 *
 *  Created on: Jun 11, 2022
 *      Author: KARIM
 */

#include  "../LIB/std_types.h"
#include  "../LIB/bitmath.h"

#include "GIE_interface.h"
#include "GIE_private.h"
#include "GIE_config.h"

void GIE_voidEnableGlobalInterrupts(void)
{
	// Enable Global Interrupt
	SET_BIT(SREG, 7);
}
void GIE_voidDisableGlobalInterrupts(void)
{
	// Disable Global Interrupt
	CLR_BIT(SREG, 7);
}
