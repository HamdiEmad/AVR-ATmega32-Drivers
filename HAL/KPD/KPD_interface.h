/*
 * KPD_interface.h
 *
 *  Created on: Oct 29, 2026
 *      Author: Hamdi
 */

#ifndef HAL_KPD_KPD_INTERFACE_H_
#define HAL_KPD_KPD_INTERFACE_H_

#include "MCAL/DIO/DIO_interface.h"

typedef enum
{
    KPD_OK = 0,
    KPD_NOK,
    KPD_NULLPTR
} KPD_errorStatus;

typedef struct {
    uint8 port;
} KPD_t;

#define KPD_NOT_PRESSED 0xFF

KPD_errorStatus KPD_enumInitialize(KPD_t *kpd);
KPD_errorStatus KPD_enumGetPressed(KPD_t *kpd, uint8 *data);

#endif /* HAL_KPD_KPD_INTERFACE_H_ */
