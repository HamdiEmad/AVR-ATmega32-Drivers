/*
 * DIO_private.h
 *
 *  Created on: Oct 26, 2026
 *      Author: Hamdi
 *      SWC   : DIO/GPIO
 */

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

/* Group A */
#define DDRA *((volatile uint8 *)0x3A)
#define PORTA *((volatile uint8 *)0x3B)
#define PINA *((volatile uint8 *)0x39)

/* Group B */
#define DDRB *((volatile uint8 *)0x37)
#define PORTB *((volatile uint8 *)0x38)
#define PINB *((volatile uint8 *)0x36)

/* Group C */
#define DDRC *((volatile uint8 *)0x34)
#define PORTC *((volatile uint8 *)0x35)
#define PINC *((volatile uint8 *)0x33)

/* Group D */
#define DDRD *((volatile uint8 *)0x31)
#define PORTD *((volatile uint8 *)0x32)
#define PIND *((volatile uint8 *)0x30)

/* Pull Up */
#define SFIOR *((volatile uint8*)0x50)

#endif /* DIO_PRIVATE_H_ */
