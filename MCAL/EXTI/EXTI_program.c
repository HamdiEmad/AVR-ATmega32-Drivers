/*
 * EXTI_program.c
 *
 *  Created on: Oct 29, 2026
 *      Author: Hamdi
 */

#include "EXTI_private.h"
#include "EXTI_config.h"
#include "EXTI_interface.h"

void (*EXTI_callBack[3])(void) = {NULL};

void EXTI_voidInitialize(void)
{
    SET_BIT(SREG, 7);

#if EXTI_LINE == EXTI_LINE0
#if EXTI_TRIGGER == EXTI_LOW_LEVEL
    CLR_BIT(MCUCR, 0);
    CLR_BIT(MCUCR, 1);
#elif EXTI_TRIGGER == EXTI_ON_CHANGE
    SET_BIT(MCUCR, 0);
    CLR_BIT(MCUCR, 1);
#elif EXTI_TRIGGER == EXTI_FALLING_EDGE
    CLR_BIT(MCUCR, 0);
    SET_BIT(MCUCR, 1);
#elif EXTI_TRIGGER == EXTI_RISING_EDGE
    SET_BIT(MCUCR, 0);
    SET_BIT(MCUCR, 1);
#else
#error "INVALID SENSING MODE FOR INT0!"
#endif

#elif EXTI_LINE == EXTI_LINE1
#if EXTI_TRIGGER == EXTI_LOW_LEVEL
    CLR_BIT(MCUCR, 2);
    CLR_BIT(MCUCR, 3);
#elif EXTI_TRIGGER == EXTI_ON_CHANGE
    SET_BIT(MCUCR, 2);
    CLR_BIT(MCUCR, 3);
#elif EXTI_TRIGGER == EXTI_FALLING_EDGE
    CLR_BIT(MCUCR, 2);
    SET_BIT(MCUCR, 3);
#elif EXTI_TRIGGER == EXTI_RISING_EDGE
    SET_BIT(MCUCR, 2);
    SET_BIT(MCUCR, 3);
#else
#error "INVALID SENSING MODE FOR INT1!"
#endif

#elif EXTI_LINE == EXTI_LINE2
#if EXTI_TRIGGER == EXTI_FALLING_EDGE
    CLR_BIT(MCUCSR, 6);
#elif EXTI_TRIGGER == EXTI_RISING_EDGE
    SET_BIT(MCUCSR, 6);
#else
#error "INVALID SENSING MODE FOR INT2!"
#endif

#else
#error "INVALID EXTI LINE!"
#endif
}

EXTI_errorStatus EXTI_enumSetSignalLatch(uint8 mode, uint8 line)
{
    EXTI_errorStatus status = EXTI_OK;

    if (line == EXTI_LINE0 || line == EXTI_LINE1)
    {
        uint8 copy_line = (line - 6) * 2;

        switch (mode)
        {
        case EXTI_LOW_LEVEL:
            CLR_BIT(MCUCR, line);
            CLR_BIT(MCUCR, line + 1);
            break;
        case EXTI_ON_CHANGE:
            SET_BIT(MCUCR, line);
            CLR_BIT(MCUCR, line + 1);
            break;
        case EXTI_FALLING_EDGE:
            CLR_BIT(MCUCR, line);
            SET_BIT(MCUCR, line + 1);
            break;
        case EXTI_RISING_EDGE:
            SET_BIT(MCUCR, line);
            SET_BIT(MCUCR, line + 1);
            break;
        default:
            status = EXTI_INVALID_MODE;
            break;
        }
    }
    else if (line == EXTI_LINE2)
    {
        switch (mode)
        {
        case EXTI_FALLING_EDGE:
            CLR_BIT(MCUCSR, 6);
            break;
        case EXTI_RISING_EDGE:
            SET_BIT(MCUCSR, 6);
            break;
        default:
            status = EXTI_INVALID_MODE;
            break;
        }
    }
    else
        status = EXTI_INVALID_LINE;

    return status;
}

EXTI_errorStatus EXTI_enumEnableInterrupt(uint8 line)
{
    EXTI_errorStatus status = EXTI_OK;

    if (line >= EXTI_LINE2 && line <= EXTI_LINE1)
    {
        SET_BIT(SREG, 7);
        SET_BIT(GICR, line);
    }
    else
        status = EXTI_INVALID_LINE;

    return status;
}

EXTI_errorStatus EXTI_enumDisableInterrupt(uint8 line)
{
    EXTI_errorStatus status = EXTI_OK;

    if (line >= EXTI_LINE2 && line <= EXTI_LINE1)
        CLR_BIT(GICR, line);
    else
        status = EXTI_INVALID_LINE;

    return status;
}

EXTI_errorStatus EXTI_enumSetCallBack(void (*ptr)(void), uint8 line)
{
    EXTI_errorStatus status = EXTI_OK;

    if (ptr != NULL)
    {
        switch (line)
        {
        case EXTI_LINE0:
            EXTI_callBack[0] = ptr;
            break;
        case EXTI_LINE1:
            EXTI_callBack[1] = ptr;
            break;
        case EXTI_LINE2:
            EXTI_callBack[2] = ptr;
            break;
        default:
            status = EXTI_INVALID_LINE;
            break;
        }
    }
    else
        status = EXTI_NULLPTR;

    return status;
}

EXTI_errorStatus EXTI_enumClearFlag(uint8 line)
{
    EXTI_errorStatus status = EXTI_OK;

    if (line >= EXTI_LINE2 && line <= EXTI_LINE1)
        SET_BIT(GIFR, line);
    else
        status = EXTI_INVALID_LINE;

    return status;
}

EXTI_errorStatus EXTI_enumGetFlag(uint8 line, uint8 *flag)
{
    EXTI_errorStatus status = EXTI_OK;

    if (line >= EXTI_LINE2 && line <= EXTI_LINE1)
        *flag = GET_BIT(GIFR, line);
    else
        status = EXTI_INVALID_LINE;

    return status;
}

void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
    if (EXTI_callBack[0] != NULL)
    {
        EXTI_callBack[0]();
        EXTI_enumClearFlag(EXTI_LINE0);
    }
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
    if (EXTI_callBack[1] != NULL)
    {
        EXTI_callBack[1]();
        EXTI_enumClearFlag(EXTI_LINE1);
    }
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
    if (EXTI_callBack[2] != NULL)
    {
        EXTI_callBack[2]();
        EXTI_enumClearFlag(EXTI_LINE2);
    }
}
