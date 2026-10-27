/*
 * SW.program.c
 *
 *  Created on: Oct 27, 2026
 *      Author: Hamdi
 */

/*
 * P_BTN.c
 *
 *  Created on: Sep 16, 2026
 *      Author: Hamdi
 */

#include "SW_interface.h"

SW_errorStatus SW_enumInitialize(SW_t *btn)
{
    SW_errorStatus ret_val = SW_OK;

    if (NULL == btn)
        ret_val = SW_NULLPTR;
    else
    {
        if (SW_PULLUP == btn->mode || SW_PULLDOWN == btn->mode)
        {
            if (DIO_enumInitializePin(btn->port, btn->pin, DIO_INPUT))
            {
                ret_val = SW_NOK;
            }
        }
        else if (SW_INPUT_PULLUP == btn->mode)
        {
            if (DIO_enumInitializePin(btn->port, btn->pin, DIO_INPUT_PULLUP))
            {
                ret_val = SW_NOK;
            }
        }
        else
        {
            ret_val = SW_INVALID_STATE;
        }
    }
    return ret_val;
}

SW_errorStatus SW_enumIsClicked(SW_t *btn, uint8 *state)
{
    SW_errorStatus ret_val = SW_OK;
    sint8 get_pressed = 0;
    uint8 status = SW_NOT_PRESSED;

    if (NULL == btn || NULL == state)
        ret_val = SW_NULLPTR;
    else
    {
        if (DIO_enumReadPinValue(btn->port, btn->pin, &get_pressed))
        {
            ret_val = SW_NOK;
        }
        else
        {
            if (btn->mode == SW_INPUT_PULLUP || btn->mode == SW_PULLUP)
            {
                if (get_pressed == DIO_LOW)
                {
                    status = SW_PRESSED;
                }
                else if (get_pressed == DIO_HIGH)
                {
                    status = SW_NOT_PRESSED;
                }
                else
                    ret_val = SW_NOK;
            }
            else if (btn->mode == SW_PULLDOWN)
            {
                if (get_pressed == DIO_LOW)
                {
                    status = SW_NOT_PRESSED;
                }
                else if (get_pressed == DIO_HIGH)
                {
                    status = SW_PRESSED;
                }
                else
                    ret_val = SW_NOK;
            }
            else
                ret_val = SW_INVALID_STATE;
        }
    }

    *state = status;

    return ret_val;
}
