/*
 * BUZZER.c
 *
 *  Created on: Sep 17, 2026
 *      Author: Hamdi
 */

#include "BUZZER.h"

BUZZER_errorStatus BUZZER_enumInitialize(BUZZER_t *buzzer)
{
    BUZZER_errorStatus ret_val = BUZZER_OK;

    if (NULL == buzzer)
        ret_val = BUZZER_NULLPTR;
    else
    {
        if (DIO_enumInitializePin(buzzer->port, buzzer->pin, DIO_OUTPUT))
        {
            ret_val = BUZZER_NOK;
        }
    }
    return ret_val;
}

BUZZER_errorStatus BUZZER_enumTurnOn(BUZZER_t *buzzer)
{
    BUZZER_errorStatus ret_val = BUZZER_OK;
    uint8 val = DIO_LOW;

    if (buzzer->mode == ACTIVE_HIGH_MODE)
        val = DIO_HIGH;
    else if (buzzer->mode == ACTIVE_LOW_MODE)
        val = DIO_LOW;
    else
        ret_val = BUZZER_INVALID_MODE;

    if (NULL == buzzer)
        ret_val = BUZZER_NULLPTR;
    else
    {
        if (DIO_enumSetPinValue(buzzer->port, buzzer->pin, val))
        {
            ret_val = BUZZER_NOK;
        }
    }
    return ret_val;
}

BUZZER_errorStatus BUZZER_enumTurnOff(BUZZER_t *buzzer)
{
    BUZZER_errorStatus ret_val = BUZZER_OK;
    uint8 val = DIO_LOW;

    if (buzzer->mode == ACTIVE_HIGH_MODE)
        val = DIO_LOW;
    else if (buzzer->mode == ACTIVE_LOW_MODE)
        val = DIO_HIGH;
    else
        ret_val = BUZZER_INVALID_MODE;

    if (NULL == buzzer)
        ret_val = BUZZER_NULLPTR;
    else
    {
        if (DIO_enumSetPinValue(buzzer->port, buzzer->pin, val))
        {
            ret_val = BUZZER_NOK;
        }
    }
    return ret_val;
}

BUZZER_errorStatus BUZZER_enumToggle(BUZZER_t *buzzer)
{
    BUZZER_errorStatus ret_val = BUZZER_OK;

    if (NULL == buzzer)
        ret_val = BUZZER_NULLPTR;
    else
    {
        if (DIO_enumTogglePinValue(buzzer->port, buzzer->pin))
        {
            ret_val = BUZZER_NOK;
        }
    }
    return ret_val;
}
