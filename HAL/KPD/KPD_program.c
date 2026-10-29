/*
 * KPD_program.c
 *
 *  Created on: Oct 29, 2026
 *      Author: Hamdi
 */

#include "MCAL/DIO/DIO_interface.h"
#include "KPD_config.h"
#include "KPD_interface.h"

KPD_errorStatus KPD_enumInitialize(KPD_t *kpd)
{
    KPD_errorStatus status = KPD_OK;

    if (NULL == kpd)
        status = KPD_NULLPTR;
    else
    {
        if (kpd->port >= DIO_PORTA && kpd->port <= DIO_PORTD)
        {
            if (DIO_enumInitializePort(kpd->port, 0x0F))
            {
                status = KPD_NOK;
            }
            if (DIO_enumSetPortValue(kpd->port, 0xFF))
            {
                status = KPD_NOK;
            }
        }
    }

    return status;
}

KPD_errorStatus KPD_enumGetPressed(KPD_t *kpd, uint8 *data)
{
    KPD_errorStatus status = KPD_OK;
    uint8 read = KPD_NOT_PRESSED;

    if (NULL == kpd || NULL == data)
        status = KPD_NULLPTR;
    else
    {
        for (uint8 row = 0; row < 4; row++)
        {
            uint8 val = 0;

            if (DIO_enumSetPinValue(kpd->port, row, DIO_LOW))
            {
                status = KPD_NOK;
            }

            for (uint8 col = 0; col < 4; col++)
            {
                if (DIO_enumReadPinValue(kpd->port, (col + 4), &val))
                {
                    status = KPD_NOK;
                }
                if (val == DIO_LOW)
                {
                    read = KPD_BTNS[row][col];
                }
            }
            if (DIO_enumSetPinValue(kpd->port, row, DIO_HIGH))
            {
                status = KPD_NOK;
            }
        }
    }

    *data = read;

    return status;
}
