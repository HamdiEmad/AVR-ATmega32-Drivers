/*
 * DIO.interface.h
 *
 *  Created on: Oct 26, 2026
 *      Author: Hamdi
 *      SWC   : DIO/GPIO
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

typedef enum
{
	DIO_OK = 0,
	DIO_NOK,
	DIO_INVALID_PIN,
	DIO_INVALID_PORT,
	DIO_INVALID_VALUE,
	DIO_NULLPTR
} DIO_errorStatus;

#define DIO_LOW 0
#define DIO_HIGH 1

#define DIO_INPUT 0
#define DIO_INPUT_PULLUP 1
#define DIO_OUTPUT 2
#define DIO_FLOATING 3

#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7

#define DIO_LOW_NIPPLE 0
#define DIO_HIGH_NIPPLE 1

#define NULL ((void *)0)

DIO_errorStatus DIO_enumInitializePin(uint8 port, uint8 pin, uint8 direction);
DIO_errorStatus DIO_enumSetPinValue(uint8 port, uint8 pin, uint8 value);
DIO_errorStatus DIO_enumTogglePinValue(uint8 port, uint8 pin);
DIO_errorStatus DIO_enumReadPinValue(uint8 port, uint8 pin, sint8 *value);

DIO_errorStatus DIO_enumInitializePort(uint8 port, uint8 direction);
DIO_errorStatus DIO_enumSetPortValue(uint8 port, uint8 value);
DIO_errorStatus DIO_enumTogglePortValue(uint8 port);
DIO_errorStatus DIO_enumReadPortValue(uint8 port, sint8 *value);

DIO_errorStatus DIO_enumWriteHighNipples(uint8 port, uint8 value);
DIO_errorStatus DIO_enumWriteLowNipples(uint8 port, uint8 value);

#endif /* DIO_INTERFACE_H_ */
