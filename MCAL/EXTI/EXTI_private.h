/*
 * EXTI_private.h
 *
 *  Created on: Oct 29, 2026
 *      Author: Hamdi
 */

#ifndef MCAL_EXTI_EXTI_PRIVATE_H_
#define MCAL_EXTI_EXTI_PRIVATE_H_

#define MCUCR *((volatile uint8*)0x55)
#define MCUCSR *((volatile uint8*)0x54)
#define GICR *((volatile uint8*)0x5B)
#define GIFR *((volatile uint8*)0x5A)
#define SREG *((volatile uint8*)0x5F)

#endif /* MCAL_EXTI_EXTI_PRIVATE_H_ */
