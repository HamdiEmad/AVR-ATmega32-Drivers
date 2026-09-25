/*
 * DIO.h
 *
 *  Created on: Sep 16, 2026
 *      Author: Hamdi
 */

#ifndef MCAL_DIO_H_
#define MCAL_DIO_H_

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

typedef enum
{
	DIO_OK = 0,
	DIO_NOK,
	DIO_INVALID_PIN,
	DIO_INVALID_PORT,
	DIO_INVALID_VALUE,
	DIO_NULLPTR
} DIO_errorStatus;

#define NULL ((void *)0)

#define DIO_INPUT 0
#define DIO_INPUT_PULLUP 1
#define DIO_OUTPUT 2
#define DIO_FLOATING 3

#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

#define DIO_DDRA 0
#define DIO_DDRB 1
#define DIO_DDRC 2
#define DIO_DDRD 3

#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7

#define DIO_LOW 0
#define DIO_HIGH 1

#define DDRA *((volatile uint8 *)0x3A)
#define PORTA *((volatile uint8 *)0x3B)
#define PINA *((volatile uint8 *)0x39)
#define DDRB *((volatile uint8 *)0x37)
#define PORTB *((volatile uint8 *)0x38)
#define PINB *((volatile uint8 *)0x36)
#define DDRC *((volatile uint8 *)0x34)
#define PORTC *((volatile uint8 *)0x35)
#define PINC *((volatile uint8 *)0x33)
#define DDRD *((volatile uint8 *)0x31)
#define PORTD *((volatile uint8 *)0x32)
#define PIND *((volatile uint8 *)0x30)

DIO_errorStatus DIO_enumInitializePin(uint8 port, uint8 pin, uint8 direction);
DIO_errorStatus DIO_enumSetPinValue(uint8 port, uint8 pin, uint8 value);
DIO_errorStatus DIO_enumTogglePinValue(uint8 port, uint8 pin);
DIO_errorStatus DIO_enumReadPinValue(uint8 port, uint8 pin, sint8 *value);

DIO_errorStatus DIO_enumInitializePort(uint8 port, uint8 value);
DIO_errorStatus DIO_enumSetPortValue(uint8 port, uint8 value);
DIO_errorStatus DIO_enumTogglePortValue(uint8 port);
DIO_errorStatus DIO_enumReadPortValue(uint8 port, sint8 *value);

#endif /* MCAL_DIO_H_ */
