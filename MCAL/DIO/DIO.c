/*
 * DIO.c
 *
 *  Created on: Sep 16, 2026
 *      Author: Hamdi
 */

#include "DIO.h"

DIO_errorStatus DIO_enumInitializePin(uint8 port, uint8 pin, uint8 direction)
{
    DIO_errorStatus ret_val = DIO_OK;

    if (pin < DIO_PIN0 || pin > DIO_PIN7)
        ret_val = DIO_INVALID_PIN;
    else
    {
        switch (port)
        {
        case DIO_PORTA:
            if (direction == DIO_INPUT)
            {
                CLR_BIT(DDRA, pin);
            }
            else if (direction == DIO_INPUT_PULLUP)
            {
                CLR_BIT(DDRA, pin);
                SET_BIT(PORTA, pin);
            }
            else if (direction == DIO_OUTPUT)
            {
                SET_BIT(DDRA, pin);
            }
            else
                ret_val = DIO_NOK;
            break;
        case DIO_PORTB:
            if (direction == DIO_INPUT)
            {
                CLR_BIT(DDRB, pin);
                CLR_BIT(PORTB, pin);
            }
            else if (direction == DIO_INPUT_PULLUP)
            {
                CLR_BIT(DDRB, pin);
                SET_BIT(PORTB, pin);
            }
            else if (direction == DIO_OUTPUT)
            {
                SET_BIT(DDRB, pin);
            }
            else
                ret_val = DIO_NOK;
            break;
        case DIO_PORTC:
            if (direction == DIO_INPUT)
            {
                CLR_BIT(DDRC, pin);
                CLR_BIT(PORTC, pin);
            }
            else if (direction == DIO_INPUT_PULLUP)
            {
                CLR_BIT(DDRC, pin);
                SET_BIT(PORTC, pin);
            }
            else if (direction == DIO_OUTPUT)
            {
                SET_BIT(DDRC, pin);
            }
            else
                ret_val = DIO_NOK;
            break;
        case DIO_PORTD:
            if (direction == DIO_INPUT)
            {
                CLR_BIT(DDRD, pin);
                CLR_BIT(PORTD, pin);
            }
            else if (direction == DIO_INPUT_PULLUP)
            {
                CLR_BIT(DDRD, pin);
                SET_BIT(PORTD, pin);
            }
            else if (direction == DIO_OUTPUT)
            {
                SET_BIT(DDRD, pin);
            }
            else
                ret_val = DIO_NOK;
            break;
        default:
            ret_val = DIO_INVALID_PORT;
            break;
        }
    }
    return ret_val;
}

DIO_errorStatus DIO_enumSetPinValue(uint8 port, uint8 pin, uint8 value)
{
    DIO_errorStatus ret_val = DIO_OK;

    if (pin < DIO_PIN0 || pin > DIO_PIN7)
        ret_val = DIO_INVALID_PIN;

    else
    {
        switch (port)
        {
        case DIO_PORTA:
            if (value == DIO_HIGH)
            {
                SET_BIT(PORTA, pin);
            }
            else if (value == DIO_LOW)
            {
                CLR_BIT(PORTA, pin);
            }
            else
                ret_val = DIO_NOK;
            break;
        case DIO_PORTB:
            if (value == DIO_HIGH)
            {
                SET_BIT(PORTB, pin);
            }
            else if (value == DIO_LOW)
            {
                CLR_BIT(PORTB, pin);
            }
            else
                ret_val = DIO_NOK;
            break;
        case DIO_PORTC:
            if (value == DIO_HIGH)
            {
                SET_BIT(PORTC, pin);
            }
            else if (value == DIO_LOW)
            {
                CLR_BIT(PORTC, pin);
            }
            else
                ret_val = DIO_NOK;
            break;
        case DIO_PORTD:
            if (value == DIO_HIGH)
            {
                SET_BIT(PORTD, pin);
            }
            else if (value == DIO_LOW)
            {
                CLR_BIT(PORTD, pin);
            }
            else
                ret_val = DIO_NOK;
            break;
        default:
            ret_val = DIO_INVALID_PORT;
        }
    }
    return ret_val;
}

DIO_errorStatus DIO_enumTogglePinValue(uint8 port, uint8 pin)
{
    DIO_errorStatus ret_val = DIO_OK;

    if (port < DIO_PORTA || port > DIO_PORTD)
        ret_val = DIO_INVALID_PORT;
    else
    {
        if (pin < DIO_PIN0 || pin > DIO_PIN7)
            ret_val = DIO_INVALID_PIN;
        else
        {
            switch (port)
            {
            case DIO_PORTA:
                TOG_BIT(PORTA, pin);
                break;
            case DIO_PORTB:
                TOG_BIT(PORTB, pin);
                break;
            case DIO_PORTC:
                TOG_BIT(PORTC, pin);
                break;
            case DIO_PORTD:
                TOG_BIT(PORTD, pin);
                break;
            default:
                ret_val = DIO_NOK;
            }
        }
    }
    return ret_val;
}

DIO_errorStatus DIO_enumReadPinValue(uint8 port, uint8 pin, sint8 *value)
{
    DIO_errorStatus ret_val = DIO_OK;

    if (NULL == value)
        ret_val = DIO_NULLPTR;
    else
    {
        if (pin < DIO_PIN0 || pin > DIO_PIN7)
            ret_val = DIO_INVALID_PIN;
        else
        {
            switch (port)
            {
            case DIO_PORTA:
                *value = READ_BIT(PINA, pin);
                break;
            case DIO_PORTB:
                *value = READ_BIT(PINB, pin);
                break;
            case DIO_PORTC:
                *value = READ_BIT(PINC, pin);
                break;
            case DIO_PORTD:
                *value = READ_BIT(PIND, pin);
                break;
            default:
                ret_val = DIO_INVALID_PORT;
                *value = -1;
            }
        }
    }
    return ret_val;
}

DIO_errorStatus DIO_enumInitializePort(uint8 port, uint8 value)
{
    DIO_errorStatus ret_val = DIO_OK;

    switch (port)
    {
    case DIO_PORTA:
        if (value == DIO_INPUT)
            DDRA = 0x00;
        else if (value == DIO_INPUT_PULLUP)
        {
            DDRA = 0x00;
            PORTA = 0xFF;
        }
        else if (value == DIO_OUTPUT)
            DDRA = 0xFF;
        else if (value > 0x00 && value < 0xFF)
        {
            DDRA = value;
        }
        else
            ret_val = DIO_INVALID_VALUE;
        break;
    case DIO_PORTB:
        if (value == DIO_INPUT)
            DDRB = 0x00;
        else if (value == DIO_INPUT_PULLUP)
        {
            DDRB = 0x00;
            PORTB = 0xFF;
        }
        else if (value == DIO_OUTPUT)
            DDRB = 0xFF;
        else if (value > 0x00 && value < 0xFF)
        {
            DDRB = value;
        }
        else
            ret_val = DIO_INVALID_VALUE;
        break;
    case DIO_PORTC:
        if (value == DIO_INPUT)
            DDRC = 0x00;
        else if (value == DIO_INPUT_PULLUP)
        {
            DDRC = 0x00;
            PORTC = 0xFF;
        }
        else if (value == DIO_OUTPUT)
            DDRC = 0xFF;
        else if (value > 0x00 && value < 0xFF)
        {
            DDRC = value;
        }
        else
            ret_val = DIO_INVALID_VALUE;
        break;
    case DIO_PORTD:
        if (value == DIO_INPUT)
            DDRD = 0x00;
        else if (value == DIO_INPUT_PULLUP)
        {
            DDRD = 0x00;
            PORTD = 0xFF;
        }
        else if (value == DIO_OUTPUT)
            DDRD = 0xFF;
        else if (value > 0x00 && value < 0xFF)
        {
            DDRA = value;
        }
        else
            ret_val = DIO_INVALID_VALUE;
        break;
    default:
        ret_val = DIO_INVALID_PORT;
    }
    return ret_val;
}

DIO_errorStatus DIO_enumSetPortValue(uint8 port, uint8 value)
{
    DIO_errorStatus ret_val = DIO_OK;
    uint8 reg = 0;

    if (value == DIO_HIGH)
        reg = 0xFF;
    else if (value == DIO_LOW)
        reg = 0;
    else
        reg = value;

    switch (port)
    {
    case DIO_PORTA:
        PORTA = reg;
        break;
    case DIO_PORTB:
        PORTB = reg;
        break;
    case DIO_PORTC:
        PORTC = reg;
        break;
    case DIO_PORTD:
        PORTD = reg;
        break;
    default:
        ret_val = DIO_INVALID_PORT;
        break;
    }
    return ret_val;
}

DIO_errorStatus DIO_enumTogglePortValue(uint8 port)
{
    DIO_errorStatus ret_val = DIO_OK;

    switch (port)
    {
    case DIO_PORTA:
        PORTA ^= 0xFF;
        break;
    case DIO_PORTB:
        PORTB ^= 0xFF;
        break;
    case DIO_PORTC:
        PORTC ^= 0xFF;
        break;
    case DIO_PORTD:
        PORTD ^= 0xFF;
        break;
    default:
        ret_val = DIO_INVALID_PORT;
        break;
    }
    return ret_val;
}

DIO_errorStatus DIO_enumRead_port_value(uint8 port, sint8 *value)
{
    DIO_errorStatus ret_val = DIO_OK;

    if (NULL == value)
        ret_val = DIO_NULLPTR;
    else
    {
        switch (port)
        {
        case DIO_PORTA:
            *value = PINA;
            break;
        case DIO_PORTB:
            *value = PINB;
            break;
        case DIO_PORTC:
            *value = PINC;
            break;
        case DIO_PORTD:
            *value = PIND;
            break;
        default:
            ret_val = DIO_INVALID_PORT;
            break;
        }
    }

    return ret_val;
}
