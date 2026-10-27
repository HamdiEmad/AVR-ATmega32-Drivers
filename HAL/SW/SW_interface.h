/*
 * SW_interface.h
 *
 *  Created on: Oct 27, 2026
 *      Author: Hamdi
 */

#ifndef HAL_SW_SW_INTERFACE_H_
#define HAL_SW_SW_INTERFACE_H_

#include "MCAL/DIO/DIO_interface.h"

#define SW_PULLUP 0
#define SW_INPUT_PULLUP 1
#define SW_PULLDOWN 2
#define SW_FLOATING 3

#define SW_NOT_PRESSED 0
#define SW_PRESSED 1

typedef enum
{
    SW_OK = 0,
    SW_NOK,
    SW_INVALID_STATE,
    SW_NULLPTR
} SW_errorStatus;

typedef struct
{
    uint8 port;
    uint8 pin;
    uint8 mode;
} SW_t;

SW_errorStatus SW_enumInitialize(SW_t *btn);
SW_errorStatus SW_enumIsClicked(SW_t *btn, uint8 *state);


#endif /* HAL_SW_SW_INTERFACE_H_ */
