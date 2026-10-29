/*
 * CLCD_interface.h
 *
 *  Created on: Oct 28, 2026
 *      Author: Hamdi
 */

#ifndef HAL_CLCD_CLCD_INTERFACE_H_
#define HAL_CLCD_CLCD_INTERFACE_H_

#include "MCAL/DIO/DIO_interface.h"

#define CLCD_ROW_1 1
#define CLCD_ROW_2 2

#define CLCD_COLUMN_1 1
#define CLCD_COLUMN_2 2
#define CLCD_COLUMN_3 3
#define CLCD_COLUMN_4 4
#define CLCD_COLUMN_5 5
#define CLCD_COLUMN_6 6
#define CLCD_COLUMN_7 7
#define CLCD_COLUMN_8 8
#define CLCD_COLUMN_9 9
#define CLCD_COLUMN_10 10
#define CLCD_COLUMN_11 11
#define CLCD_COLUMN_12 12
#define CLCD_COLUMN_13 13
#define CLCD_COLUMN_14 14
#define CLCD_COLUMN_15 15
#define CLCD_COLUMN_16 16

typedef enum {
	CLCD_OK = 0,
	CLCD_NOK,
	CLCD_NULLPTR,
	CLCD_INVALID_DATA,
	CLCD_INVALID_POSITION
}CLCD_errorStatus;

void CLCD_voidInitialize(void);
CLCD_errorStatus CLCD_enumSendCommand(uint8 cmd);
CLCD_errorStatus CLCD_enumSendData(uint8 data);
CLCD_errorStatus CLCD_enumSendString(const uint8 *str);
CLCD_errorStatus CLCD_enumSendNumber(uint64 number);
void CLCD_voidClearDisplay(void);
CLCD_errorStatus CLCD_enumSetCursor(uint8 row, uint8 col);
CLCD_errorStatus CLCD_enumCursorOnOff(uint8 mask);
CLCD_errorStatus CLCD_enumCursorBlink(uint8 mask);
CLCD_errorStatus CLCD_enumCreateCustomChar(uint8 row, uint8 col, uint8 *ch);


#endif /* HAL_CLCD_CLCD_INTERFACE_H_ */
