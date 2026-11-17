/*
 * TIMER_private.h
 *
 *  Created on: Nov 3, 2026
 *      Author: Hamdi
 */

#ifndef MCAL_TIMER_TIMER_PRIVATE_H_
#define MCAL_TIMER_TIMER_PRIVATE_H_

#define TIMER_PRESCALER_MASK 0xF8

// TIMER0 Registers
#define TCNT0 *((volatile uint8 *)0x52)
#define OCR0 *((volatile uint8 *)0x5C)
#define TCCR0 *((volatile uint8 *)0x53)

// TCCR0 bits
#define CS00 0
#define CS01 1
#define CS02 2
#define WGM01 3
#define COM00 4
#define COM01 5
#define WGM00 6
#define FOC0 

// TIMER1 Registers
#define TCCR1A *((volatile uint8 *)0x4F)
#define TCCR1B *((volatile uint8 *)0x4E)
#define TCNT1 *((volatile uint16 *)0x4C)
#define OCR1A *((volatile uint16 *)0x4A)
#define OCR1B *((volatile uint16 *)0x48)
#define ICR1 *((volatile uint16 *)0x46)

// TCCR1A bits
#define WGM10 0
#define WGM11 1
#define FOC1B 2
#define FOC1A 3
#define COM1B0 4
#define COM1B1 5
#define COM1A0 6
#define COM1A1 7

// TCCR1B bits
#define CS10 0
#define CS11 1
#define CS12 2
#define WGM12 3
#define WGM13 4
#define ICES1 6
#define ICNC1 7

// TIMER2 Registers
#define TCCR2 *((volatile uint8 *)0x45)
#define TCNT2 *((volatile uint8 *)0x44)
#define OCR2 *((volatile uint8 *)0x43)
#define ASSR *((volatile uint8 *)0x42)

// TCCR2 bits
#define CS20 0
#define CS21 1
#define CS22 2
#define WGM21 3
#define COM20 4
#define COM21 5
#define WGM20 6
#define FOC2 7

// ASSR bits
#define TCR2UB 0
#define OCR2UB 1
#define TCN2UB 2
#define AS2 3


// Watchdog Timer Registers
#define WDTCR *((volatile uint8 *)0x41)

// WDTCR bits
#define WDP0 0
#define WDP1 1
#define WDP2 2
#define WDE 3
#define WDTOE 4

// Interrupt Registers
#define TIMSK *((volatile uint8 *)0x59)

#define TOIE0 0
#define OCIE0 1
#define TOIE1 2
#define OCIE1B 3
#define OCIE1A 4
#define TICIE1 5
#define TOIE2 6
#define OCIE2 7

#define TIFR *((volatile uint8 *)0x58)

// TIFR bits
#define TOV0 0
#define OCF0 1
#define TOV1 2
#define OCF1B 3
#define OCF1A 4
#define ICF1 5
#define TOV2 6
#define OCF2 7

// SREG Register
#define SREG *((volatile uint8 *)0x5F)

#define NULL ((void *)0)

#endif /* MCAL_TIMER_TIMER_PRIVATE_H_ */