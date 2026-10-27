/*
 * SSD_interface.h
 *
 *  Created on: Oct 27, 2026
 *      Author: Hamdi
 */

#ifndef HAL_SSD_SSD_INTERFACE_H_
#define HAL_SSD_SSD_INTERFACE_H_

#include "MCAL/DIO/DIO_interface.h"

#define SSD_COMMON_CATHODE 0
#define SSD_COMMON_ANODE 1

typedef enum
{
    SSD_OK = 0,
    SSD_NOK,
    SSD_NULLPTR,
    SSD_INVALID_DATA,
    SSD_INVALID_MODE
}SSD_errorStatus;

typedef struct
{
    uint8 control_port;
    uint8 control_pin;
    uint8 data_port;
    uint8 mode;
} SSD_t;

SSD_errorStatus SSD_enumInitialize(SSD_t *seg);
SSD_errorStatus SSD_enumWriteData(SSD_t *seg, uint8 data);
SSD_errorStatus SSD_enumTurnOff(SSD_t *seg);
SSD_errorStatus SSD_enumTurnOn(SSD_t *seg);


#endif /* HAL_SSD_SSD_INTERFACE_H_ */
