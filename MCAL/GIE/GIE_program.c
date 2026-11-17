/*
 * GIE_program.c
 *
 *  Created on: Nov 18, 2026
 *      Author: Hamdi
 */

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "GIE_private.h"
#include "GIE_interface.h"

void GIE_voidEnable(void)
{
	SET_BIT(SREG, I);
}

void GIE_voidDisable(void)
{
	CLR_BIT(SREG, I);
}
