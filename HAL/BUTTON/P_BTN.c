/*
 * P_BTN.c
 *
 *  Created on: Sep 16, 2026
 *      Author: Hamdi
 */

#include "P_BTN.h"

BUTTON_errorStatus BTN_enumInitialize(BUTTON_t *btn)
{
    BUTTON_errorStatus ret_val = BUTTON_OK;

    if (NULL == btn)
        ret_val = BUTTON_NULLPTR;
    else
    {
        if (BUTTON_PULLUP == btn->mode || BUTTON_PULLDOWN == btn->mode)
        {
            if (DIO_enumInitializePin(btn->port, btn->pin, DIO_INPUT))
            {
                ret_val = BUTTON_NOK;
            }
        }
        else if (BUTTON_INPUT_PULLUP == btn->mode)
        {
            if (DIO_enumInitializePin(btn->port, btn->pin, DIO_INPUT_PULLUP))
            {
                ret_val = BUTTON_NOK;
            }
        }
        else
        {
            ret_val = BUTTON_INVALID_STATE;
        }
    }
    return ret_val;
}

BUTTON_errorStatus BTN_enumIsClicked(BUTTON_t *btn, uint8 *state)
{
    BUTTON_errorStatus ret_val = BUTTON_OK;
    sint8 get_clicked = 0;
    uint8 status = BUTTON_NOT_PRESSED;

    if (NULL == btn || NULL == state)
        ret_val = BUTTON_NULLPTR;
    else
    {
        if (DIO_enumReadPinValue(btn->port, btn->pin, &get_clicked))
        {
            ret_val = BUTTON_NOK;
        }
        else
        {
            if (btn->mode == BUTTON_INPUT_PULLUP || btn->mode == BUTTON_PULLUP)
            {
                if (get_clicked == DIO_LOW)
                {
                    status = BUTTON_PRESSED;
                }
                else if (get_clicked == DIO_HIGH)
                {
                    status = BUTTON_NOT_PRESSED;
                }
                else
                    ret_val = BUTTON_NOK;
            }
            else if (btn->mode == BUTTON_PULLDOWN)
            {
                if (get_clicked == DIO_LOW)
                {
                    status = BUTTON_NOT_PRESSED;
                }
                else if (get_clicked == DIO_HIGH)
                {
                    status = BUTTON_PRESSED;
                }
                else
                    ret_val = BUTTON_NOK;
            }
            else
                ret_val = BUTTON_INVALID_STATE;
        }
    }

    *state = status;

    return ret_val;
}
