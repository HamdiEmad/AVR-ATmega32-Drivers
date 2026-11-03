/*
 * ADC_private.h
 *
 *  Created on: Oct 31, 2026
 *      Author: Hamdi
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

#define ADMUX *((volatile uint8 *)0x27)
#define ADCSRA *((volatile uint8 *)0x26)
#define SFIOR *((volatile uint8 *)0x50)
#define ADCL *((volatile uint16 *)0x24)
#define ADCH *((volatile uint16 *)0x25)
#define SREG *((volatile uint8 *)0x5F)

#define ADC_PRESCALER_MASK 0xF8
#define ADC_CHANNEL_MASK 0xE0

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */