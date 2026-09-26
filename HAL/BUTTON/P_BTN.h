/*
 * P_BTN.h
 *
 *  Created on: Sep 16, 2026
 *      Author: Hamdi
 */

#include "MCAL/DIO/DIO.h"

#ifndef HAL_PUSH_BUTTON_P_BTN_H_
#define HAL_PUSH_BUTTON_P_BTN_H_

#define BUTTON_PULLUP 0
#define BUTTON_INPUT_PULLUP 1
#define BUTTON_PULLDOWN 2
#define BUTTON_FLOATING 3

#define BUTTON_NOT_PRESSED 0
#define BUTTON_PRESSED 1

typedef enum
{
    BUTTON_OK = 0,
    BUTTON_NOK,
    BUTTON_INVALID_STATE,
    BUTTON_NULLPTR
} BUTTON_errorStatus;

typedef struct
{
    uint8 port;
    uint8 pin;
    uint8 mode;
} BUTTON_t;

BUTTON_errorStatus BTN_enumInitialize(BUTTON_t *btn);
BUTTON_errorStatus BTN_enumIsClicked(BUTTON_t *btn, uint8 *state);

#endif /* HAL_PUSH_BUTTON_P_BTN_H_ */
