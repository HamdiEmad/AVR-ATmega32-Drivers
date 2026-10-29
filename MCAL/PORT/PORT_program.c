/*
 * PORT_program.c
 *
 *  Created on: Oct 29, 2026
 *      Author: Hamdi
 */

#include "LIB/STD_TYPES.h"

#include "PORT_config.h"
#include "PORT_private.h"
#include "PORT_interface.h"

void PORT_voidInitialize(void)
{
    DDRA_Register = PORTA_DIR;
    DDRB_Register = PORTB_DIR;
    DDRC_Register = PORTC_DIR;
    DDRD_Register = PORTD_DIR;

    PORTA_Register = PORTA_INITIAL_VALUE;
    PORTB_Register = PORTB_INITIAL_VALUE;
    PORTC_Register = PORTC_INITIAL_VALUE;
    PORTD_Register = PORTD_INITIAL_VALUE;
} 
