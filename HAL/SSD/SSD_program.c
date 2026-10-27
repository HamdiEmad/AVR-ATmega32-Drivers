/*
 * SSD_program.c
 *
 *  Created on: Oct 27, 2026
 *      Author: Hamdi
 */

/*
 * SSD.c
 *
 *  Created on: Sep 16, 2026
 *      Author: Hamdi
 */

#include "SSD_interface.h"
#include "SSD_config.h"

static uint8 nums[10] = SSD_NUMBER_ARR;

SSD_errorStatus SSD_enumInitialize(SSD_t *seg)
{
    SSD_errorStatus ret_val = SSD_OK;
    uint8 val = DIO_LOW;

    if (seg->mode == SSD_COMMON_ANODE)
        val = DIO_HIGH;
    else if (seg->mode == SSD_COMMON_CATHODE)
        val = DIO_LOW;
    else
        ret_val = SSD_INVALID_MODE;

    if (NULL == seg)
    {
        ret_val = SSD_NULLPTR;
    }
    else
    {
        if (DIO_enumInitializePort(seg->data_port, DIO_OUTPUT))
        {
            ret_val = SSD_NOK;
        }
        if (DIO_enumInitializePin(seg->control_port, seg->control_pin, DIO_OUTPUT))
        {
            ret_val = SSD_NOK;
        }
        if (DIO_enumSetPortValue(seg->data_port, val))
        {
            ret_val = SSD_NOK;
        }
        if (DIO_enumSetPinValue(seg->control_port, seg->control_pin, val))
        {
            ret_val = SSD_NOK;
        }
    }
    return ret_val;
}

SSD_errorStatus SSD_enumWriteData(SSD_t *seg, uint8 data)
{
    SSD_errorStatus ret_val = SSD_OK;
    uint8 val = 0;

    if (seg->mode == SSD_COMMON_ANODE)
        val = nums[data] ^ 0xFF;
    else if (seg->mode == SSD_COMMON_CATHODE)
        val = nums[data];
    else
        ret_val = SSD_INVALID_MODE;

    if (NULL == seg)
    {
        ret_val = SSD_NULLPTR;
    }
    else
    {
        if (data < 0 || data > 9)
        {
            ret_val = SSD_INVALID_DATA;
        }
        else
        {
            if (DIO_enumSetPortValue(seg->data_port, val))
            {
                ret_val = SSD_NOK;
            }
        }
    }

    return ret_val;
}

SSD_errorStatus SSD_enumTurnOff(SSD_t *seg)
{
    SSD_errorStatus ret_val = SSD_OK;
    uint8 val = DIO_LOW;

    if (seg->mode == SSD_COMMON_ANODE)
        val = DIO_LOW;
    else if (seg->mode == SSD_COMMON_CATHODE)
        val = DIO_HIGH;
    else
        ret_val = SSD_INVALID_MODE;

    if (NULL == seg)
    {
        ret_val = SSD_NULLPTR;
    }
    else
    {
        if (DIO_enumSetPinValue(seg->control_port, seg->control_pin, val))
        {
            ret_val = SSD_NOK;
        }
    }
    return ret_val;
}

SSD_errorStatus SSD_enumTurnOn(SSD_t *seg)
{
    SSD_errorStatus ret_val = SSD_OK;
    uint8 val = DIO_LOW;

    if (seg->mode == SSD_COMMON_ANODE)
        val = DIO_HIGH;
    else if (seg->mode == SSD_COMMON_CATHODE)
        val = DIO_LOW;
    else
        ret_val = SSD_INVALID_MODE;

    if (NULL == seg)
    {
        ret_val = SSD_NULLPTR;
    }
    else
    {
        if (DIO_enumSetPinValue(seg->control_port, seg->control_pin, val))
        {
            ret_val = SSD_NOK;
        }
    }
    return ret_val;
}
