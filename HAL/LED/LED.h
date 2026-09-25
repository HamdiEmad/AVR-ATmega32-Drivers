/*
 * LED.h
 *
 *  Created on: Sep 16, 2026
 *      Author: Hamdi
 */

#ifndef HAL_LED_LED_H_
#define HAL_LED_LED_H_

#include "MCAL/DIO/DIO.h"

#define ACTIVE_LOW_MODE 0
#define ACTIVE_HIGH_MODE 1

typedef struct
{
    uint8 port;
    uint8 pin;
    uint8 mode;
} LED_t;

typedef enum
{
    LED_OK = 0,
    LED_NOK,
    LED_INVALID_MODE,
    LED_NULLPTR
} LED_errorStatus;

LED_errorStatus LED_enumInitializeLed(LED_t *led);
LED_errorStatus LED_enumTurnOn(LED_t *led);
LED_errorStatus LED_enumTurnOff(LED_t *led);
LED_errorStatus LED_enumBlink(LED_t *led);

#endif /* HAL_LED_LED_H_ */
