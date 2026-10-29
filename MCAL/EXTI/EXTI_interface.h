/*
 * EXTI_interface.h
 *
 *  Created on: Oct 29, 2026
 *      Author: Hamdi
 */

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

#include "MCAL/DIO/DIO_interface.h"

#define EXTI_LINE0 6
#define EXTI_LINE1 7
#define EXTI_LINE2 5

#define EXTI_LOW_LEVEL 0
#define EXTI_ON_CHANGE 1
#define EXTI_FALLING_EDGE 2
#define EXTI_RISING_EDGE 3

typedef enum
{
    EXTI_OK = 0,
    EXTI_NOK,
    EXTI_NULLPTR,
    EXTI_INVALID_LINE,
    EXTI_INVALID_MODE
} EXTI_errorStatus;

void EXTI_voidInitialize(void);
EXTI_errorStatus EXTI_enumEnableInterrupt(uint8 line);
EXTI_errorStatus EXTI_enumDisableInterrupt(uint8 line);
EXTI_errorStatus EXTI_enumSetCallBack(void (*ptr)(void), uint8 line);
EXTI_errorStatus EXTI_setSignalLatch(uint8 mode, uint8 line);
EXTI_errorStatus EXTI_enumClearFlag(uint8 line);
EXTI_errorStatus EXTI_enumGetFlag(uint8 line, uint8 *flag);

#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
