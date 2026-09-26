/*
 * BUZZER.h
 *
 *  Created on: Sep 17, 2026
 *      Author: Hamdi
 */

#ifndef HAL_BUZZER_H_
#define HAL_BUZZER_H_

#include "MCAL/DIO/DIO.h"

#define ACTIVE_LOW_MODE 0
#define ACTIVE_HIGH_MODE 1

typedef struct
{
    uint8 port;
    uint8 pin;
    uint8 mode;
} BUZZER_t;

typedef enum
{
    BUZZER_OK = 0,
    BUZZER_NOK,
    BUZZER_INVALID_MODE,
    BUZZER_NULLPTR,
} BUZZER_errorStatus;

BUZZER_errorStatus BUZZER_enumInitialize(BUZZER_t *buzzer);
BUZZER_errorStatus BUZZER_enumTurnOn(BUZZER_t *buzzer);
BUZZER_errorStatus BUZZER_enumTurnOff(BUZZER_t *buzzer);
BUZZER_errorStatus BUZZER_enumToggle(BUZZER_t *buzzer);

#endif /* HAL_BUZZER_H_ */
