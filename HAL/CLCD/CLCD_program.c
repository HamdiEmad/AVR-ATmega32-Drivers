/*
 * CLCD_program.c
 *
 *  Created on: Oct 28, 2026
 *      Author: Hamdi
 */

#define F_CPU 8000000UL

#include <util/delay.h>
#include "CLCD_private.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_extrachar.h"

static uint8 ROW = 1;
static uint8 COL = 1;

static CLCD_errorStatus CLCD_enumSendFallingEdge(void);

void CLCD_voidInitialize(void)
{
		_delay_ms(50);
		DIO_enumInitializePin(CLCD_RS_PORT, CLCD_RS_PIN, DIO_OUTPUT);
		DIO_enumInitializePin(CLCD_RW_PORT, CLCD_RW_PIN, DIO_OUTPUT);
		DIO_enumInitializePin(CLCD_EN_PORT, CLCD_EN_PIN, DIO_OUTPUT);

	#if CLCD_MODE == 8
		DIO_enumInitializePort(CLCD_DATA_PORT, DIO_OUTPUT);

		CLCD_enumSendCommand(RETURN_HOME);
		_delay_ms(1);

		CLCD_enumSendCommand(EIGHT_BIT_MODE);
		_delay_ms(1);

	#elif CLCD_MODE == 4
		DIO_enumInitializePin(CLCD_DATA_PORT, DIO_PIN4, DIO_OUTPUT);
		DIO_enumInitializePin(CLCD_DATA_PORT, DIO_PIN5, DIO_OUTPUT);
		DIO_enumInitializePin(CLCD_DATA_PORT, DIO_PIN6, DIO_OUTPUT);
		DIO_enumInitializePin(CLCD_DATA_PORT, DIO_PIN7, DIO_OUTPUT);

		CLCD_enumSendCommand(RETURN_HOME);
		_delay_ms(10);

		CLCD_enumSendCommand(FOUR_BIT_MODE);
		_delay_ms(1);

	#else
		#error "CLCD INVALID MODE!"
	#endif

		CLCD_enumSendCommand(DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
		_delay_ms(1);

		CLCD_voidClearDisplay();

		CLCD_enumSendCommand(ENTRY_MODE);
		_delay_ms(1);

}

CLCD_errorStatus CLCD_enumSendCommand(uint8 cmd)
{
	CLCD_errorStatus status = CLCD_OK;

	if (DIO_enumSetPinValue(CLCD_RS_PORT, CLCD_RS_PIN, DIO_LOW))
		status = CLCD_NOK;
	if (DIO_enumSetPinValue(CLCD_RW_PORT, CLCD_RW_PIN, DIO_LOW))
		status = CLCD_NOK;

	#if CLCD_MODE == 8
		if (DIO_enumSetPortValue(CLCD_DATA_PORT, cmd))
			status = CLCD_NOK;
		CLCD_enumSendFallingEdge();

	#elif CLCD_MODE == 4
		DIO_enumWriteHighNipples(CLCD_DATA_PORT, cmd >> 4);
		CLCD_enumSendFallingEdge();
		DIO_enumWriteHighNipples(CLCD_DATA_PORT, cmd);
		CLCD_enumSendFallingEdge();

	#else
		#error "CLCD INVALID MODE!"

	#endif

	_delay_ms(1);

	return status;
}

CLCD_errorStatus CLCD_enumSendData(uint8 data)
{
	CLCD_errorStatus status = CLCD_OK;

	if (DIO_enumSetPinValue(CLCD_RS_PORT, CLCD_RS_PIN, DIO_HIGH))
		status = CLCD_NOK;
	if (DIO_enumSetPinValue(CLCD_RW_PORT, CLCD_RW_PIN, DIO_LOW))
		status = CLCD_NOK;

	if (data >= 0 && data < 256)
	{
		#if CLCD_MODE == 8
			if (DIO_enumSetPortValue(CLCD_DATA_PORT, data))
				status = CLCD_NOK;
			CLCD_enumSendFallingEdge();

		#elif CLCD_MODE == 4
			DIO_enumWriteHighNipples(CLCD_DATA_PORT, (data >> 4));
			CLCD_enumSendFallingEdge();
			DIO_enumWriteHighNipples(CLCD_DATA_PORT, data);
			CLCD_enumSendFallingEdge();

		#else
			#error "CLCD INVALID MODE"

		#endif
	}
	else
		status = CLCD_INVALID_DATA;

	_delay_ms(1);

	return status;
}

CLCD_errorStatus CLCD_enumSendNumber(uint64 number)
{
	CLCD_errorStatus status = CLCD_OK;

	uint64 copy = 1;

	if (number == 0)
	{
		if (CLCD_enumSendData('0'))
			status = CLCD_NOK;
	}
	else
	{
		while (number != 0)
		{
			copy = copy * 10 + number % 10;
			number /= 10;
		}
		while (copy != 1)
		{
			if (CLCD_enumSendData((copy % 10) + 48))
				status = CLCD_NOK;
			copy /= 10;
		}
	}

	CLCD_enumSetCursor(ROW, COL);

	return status;
}

void CLCD_voidClearDisplay(void)
{
	CLCD_enumSendCommand(CLEAR_DISPLAY);
	_delay_ms(10);
}

CLCD_errorStatus CLCD_enumSendString(const uint8 *str)
{
	CLCD_errorStatus status = CLCD_OK;

	if (NULL == str)
		status = CLCD_NOK;
	else
	{
		uint8 counter = 0;
		while (str[counter] != '\0')
			if (CLCD_enumSendData(str[counter++]))
				status = CLCD_NOK;
	}

	CLCD_enumSetCursor(ROW, COL);

	return status;
}

CLCD_errorStatus CLCD_enumSetCursor(uint8 row, uint8 col)
{
	CLCD_errorStatus status = CLCD_OK;
	uint8 pos;

	if (row < 1 || row > CLCD_ROWS || col < 1 || col > CLCD_COLUMNS)
	{
		status = CLCD_INVALID_POSITION;
		pos = CURSOR_DEFAULT_POS;
	}
	else
	{
		if (row == CLCD_ROW_1)
			pos = CURSOR_DEFAULT_POS + col - 1;
		else
			pos = 0xC0 + col - 1;
	}

	if (CLCD_enumSendCommand(pos))
		status = CLCD_NOK;

	_delay_ms(1);

	COL = col;
	ROW = row;

	return status;
}

CLCD_errorStatus CLCD_enumCreateCustomChar(uint8 row, uint8 col, uint8 *ch)
{
	CLCD_errorStatus status = CLCD_OK;

	if (CLCD_enumSendCommand(CGRAM_ADDRESS))
		status = CLCD_NOK;

	for (uint8 it = 0; it < 8; it++)
		if (CLCD_enumSendData(ch[it]))
			status = CLCD_NOK;

	if (CLCD_enumSetCursor(row, col))
			status = CLCD_NOK;

	for (uint8 it = 0; it < 8; it++)
		if (CLCD_enumSendData(it))
			status = CLCD_NOK;

	ROW = row;
	COL = col;

	return status;
}

CLCD_errorStatus CLCD_enumCursorOnOff(uint8 mask)
{
	CLCD_errorStatus status = CLCD_OK;

	if (mask == CURSOR_ON)
		CLCD_enumSendCommand(DISPLAY_ON_CURSOR_ON_BLINK_OFF);

	_delay_ms(1);

	return status;
}

CLCD_errorStatus CLCD_enumCursorBlink(uint8 mask)
{
	CLCD_errorStatus status = CLCD_OK;

		if (mask == CUSRSOR_BLINK)
			CLCD_enumSendCommand(DISPLAY_ON_CURSOR_ON_BLINK_ON);

		_delay_ms(1);

		return status;
}

static CLCD_errorStatus CLCD_enumSendFallingEdge(void)
{
	CLCD_errorStatus status = CLCD_OK;

	if (DIO_enumSetPinValue(CLCD_EN_PORT, CLCD_EN_PIN, DIO_HIGH))
		status = CLCD_NOK;
	_delay_ms(1);
	if (DIO_enumSetPinValue(CLCD_EN_PORT, CLCD_EN_PIN, DIO_LOW))
		status = CLCD_NOK;
	_delay_ms(1);

	return status;
}
