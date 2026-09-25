/*
 * LED.c
 *
 *  Created on: Sep 16, 2026
 *      Author: Hamdi
 */

#include "LED.h"

LED_errorStatus LED_enumInitializeLed(LED_t *led)
{
    LED_errorStatus ret_val = LED_OK;

    if (NULL == led)
    {
        ret_val = LED_NULLPTR;
    }
    else
    {
        if (DIO_enumInitializePin(led->port, led->pin, DIO_OUTPUT))
        {
            ret_val = LED_NOK;
        }
    }
    return ret_val;
}

LED_errorStatus LED_enumTurnOn(LED_t *led)
{
    LED_errorStatus ret_val = LED_OK;
    uint8 val = DIO_LOW;

    if (NULL == led)
    {
        ret_val = LED_NULLPTR;
    }
    else
    {
        if (led->mode == ACTIVE_LOW_MODE)
            val = DIO_LOW;
        else if (led->mode == ACTIVE_HIGH_MODE)
            val = DIO_HIGH;
        else
            ret_val = LED_INVALID_MODE;

        if (DIO_enumSetPinValue(led->port, led->pin, val))
        {
            ret_val = LED_NOK;
        }
    }
    return ret_val;
}

LED_errorStatus LED_enumTurnOff(LED_t *led)
{
    LED_errorStatus ret_val = LED_OK;
    uint8 val = DIO_LOW;

    if (NULL == led)
    {
        ret_val = LED_NULLPTR;
    }
    else
    {
        if (led->mode == ACTIVE_LOW_MODE)
            val = DIO_HIGH;
        else if (led->mode == ACTIVE_HIGH_MODE)
            val = DIO_LOW;
        else
            ret_val = LED_INVALID_MODE;

        if (DIO_enumSetPinValue(led->port, led->pin, val))
        {
            ret_val = LED_NOK;
        }
    }
    return ret_val;
}

LED_errorStatus LED_enumBlink(LED_t *led)
{
    LED_errorStatus ret_val = LED_OK;

    if (NULL == led)
    {
        ret_val = LED_NULLPTR;
    }
    else
    {
        if (DIO_enumTogglePinValue(led->port, led->pin))
        {
            ret_val = LED_NOK;
        }
    }
    return ret_val;
}
