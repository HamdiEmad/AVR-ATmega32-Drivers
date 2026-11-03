/*
 * ADC_program.c
 *
 *  Created on: Oct 31, 2026
 *      Author: Hamdi
 */

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/DIO/DIO_interface.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

static volatile uint8 ADC_state = ADC_IDLE;
static volatile uint8 ADC_ISR_state = SINGLE_CHANNEL_ASYNCH;
static void (*notification)(void) = NULL;
static uint16 *ADC_result = NULL;
static uint8 *chainArray = NULL;
static uint8 chainIndex = 0;
static uint8 chainSize = 0;

void ADC_voidInitialize(void)
{
#if ADC_REF == ADC_EXTERNAL_AREF
    CLR_BIT(ADMUX, 6);
    CLR_BIT(ADMUX, 7);
#elif ADC_REF == ADC_EXTERNAL_AVCC
    SET_BIT(ADMUX, 6);
    CLR_BIT(ADMUX, 7);
#elif ADC_REF == ADC_INTERNAL_2_56
    SET_BIT(ADMUX, 6);
    SET_BIT(ADMUX, 7);
#else
#error "INVALID ADC REFERENCE!"
#endif

#if ADC_ADJUST == ADC_RIGHT_ADJUST
    CLR_BIT(ADMUX, 5);
#elif ADC_ADJUST == ADC_LEFT_ADJUST
    SET_BIT(ADMUX, 5);
#else
#error "INVALID ADC ADJUST!"
#endif

#if ADC_CHANNEL >= ADC_CHANNEL_0 && ADC_CHANNEL <= ADC_CHANNEL_7
    ADMUX = (ADMUX & ADC_CHANNEL_MASK) | ADC_CHANNEL;
#else
#error "INVALID ADC CHANNEL!"
#endif

#if ADC_PRE >= ADC_PRESCALLER_0 && ADC_PRE <= ADC_PRESCALLER_128
    ADCSRA = (ADCSRA & ADC_PRESCALER_MASK) | ADC_PRE;
#else
#error "INVALID ADC PRESCALLER!"
#endif

#if ADC_STATUS == ADC_ENABLE
    SET_BIT(ADCSRA, 7);
#elif ADC_STATUS == ADC_DISABLE
    CLR_BIT(ADCSRA, 7);
#else
#error "INVALID ADC STATUS!"
#endif

#if ADC_INT_STATUS == ADC_INT_OFF
    CLR_BIT(ADCSRA, 3);
#elif ADC_INT_STATUS == ADC_INT_ON
    SET_BIT(ADCSRA, 3);
#else
#error "INVALID ADC INTERRUPT MODE!"
#endif
}

void ADC_voidEnable(void)
{
    SET_BIT(ADCSRA, 7);
}

void ADC_voidDisable(void)
{
    CLR_BIT(ADCSRA, 7);
}

ADC_errorStatus ADC_enumSetPrescallar(uint8 pre)
{
    ADC_errorStatus status = ADC_OK;

    if (pre <= ADC_PRESCALER_128)
        ADCSRA = (ADCSRA & ADC_PRESCALER_MASK) | pre;
    else
        status = ADC_INVALID_PRESCALER;

    return status;
}

void ADC_voidInterruptEnable(void)
{
    SET_BIT(ADCSRA, 3);
}

void ADC_voidInterruptDisable(void)
{
    CLR_BIT(ADCSRA, 3);
}

ADC_errorStatus ADC_enumGetResultSync(uint8 channel, uint16 *result)
{
    ADC_errorStatus status = ADC_OK;

    uint32 timeOut = 0;

    if (result != NULL)
    {
        if (channel < 8)
        {
            if (ADC_state == ADC_IDLE)
            {
                ADC_state = ADC_BUSY;

                ADMUX = (ADMUX & ADC_CHANNEL_MASK) | channel;

                // Start ADC conversion
                SET_BIT(ADCSRA, 6);

                // Check for EOC flag
                while (!(GET_BIT(ADCSRA, 4)) && timeOut < ADC_TIMEOUT)
                    timeOut++;

                if (timeOut >= ADC_TIMEOUT)
                    status = ADC_TIME_OUT;
                else
                {
                    // Clear EOC flag by writing one
                    SET_BIT(ADCSRA, 4);

#if ADC_ADJUST == ADC_RIGHT_ADJUST
                    *result = (ADCL | (ADCH << 8));
#elif ADC_ADJUST == ADC_LEFT_ADJUST
                    *result = ADCH;
#else
#error "INVALID ADC ADJUST!"
#endif
                }

                ADC_state = ADC_IDLE;
            }
            else
                status = ADC_BUSY_STATE;
        }
        else
            status = ADC_INVALID_CHANNEL;
    }
    else
        status = ADC_NULLPTR;

    return status;
}

ADC_errorStatus ADC_enumStartConversionAsynch(uint8 channel, uint16 *reading, void (*notificationFunc)(void))
{
    ADC_errorStatus status = ADC_OK;

    if (reading != NULL && notificationFunc != NULL)
    {
        if (channel < 8)
        {
            if (ADC_state == ADC_IDLE)
            {
                ADC_state = ADC_BUSY;

                ADC_ISR_state = SINGLE_CHANNEL_ASYNCH;

                ADC_result = reading;

                notification = notificationFunc;

                // Set the required channel
                ADMUX = (ADMUX & ADC_CHANNEL_MASK) | channel;

                // Global interrupt enable
                SET_BIT(SREG, 7);

                // ADC interrupt enable
                SET_BIT(ADCSRA, 3);

                // Start conversion
                SET_BIT(ADCSRA, 6);
            }
            else
                status = ADC_BUSY_STATE;
        }
        else
            status = ADC_INVALID_CHANNEL;
    }
    else
        status = ADC_NULLPTR;

    return status;
}

ADC_errorStatus ADC_enumStartChainAsynch(ADC_t *chain)
{
    ADC_errorStatus status = ADC_OK;

    if (chain != NULL && chain->Channel != NULL && chain->notificationFunc != NULL && chain->Result && chain->Size)
    {
        if (ADC_state == ADC_IDLE)
        {
            ADC_state = ADC_BUSY;

            ADC_ISR_state = CHAIN_CHANNEL_ASYNCH;
            notification = chain->notificationFunc;
            chainSize = chain->Size;
            ADC_result = chain->Result;
            chainArray = chain->Channel;

            chainIndex = 0;

            // Set ADC channel every chain object
            ADMUX = (ADMUX & ADC_CHANNEL_MASK) | chainArray[chainIndex];

            // ADC start conversion
            SET_BIT(ADCSRA, 6);

            // Global interrupt enable
            SET_BIT(SREG, 7);

            // ADC interrupt enable
            SET_BIT(ADCSRA, 3);
        }
        else
            status = ADC_BUSY_STATE;
    }
    else
        status = ADC_NULLPTR;

    return status;
}

void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
    uint16 localResult;

#if ADC_ADJUST == ADC_RIGHT_ADJUST
    localResult = (ADCL | (ADCH << 8));

#elif ADC_ADJUST == ADC_LEFT_ADJUST
    localResult = ADCH;
#else
#error "Wrong ADC_ADJUSTMENT config"
#endif

    if (ADC_ISR_state == SINGLE_CHANNEL_ASYNCH)
    {
        *ADC_result = localResult;

        // Disable ADC interrupt
        CLR_BIT(ADCSRA, 3);

        ADC_state = ADC_IDLE;

        notification();
    }
    else
    {
        ADC_result[chainIndex] = localResult;

        chainIndex++;

        if (chainIndex == chainSize)
        {
            // Disable ADC interrupt
            CLR_BIT(ADCSRA, 3);

            ADC_state = ADC_IDLE;

            notification();
        }
        else
        {
            ADMUX = (ADMUX & ADC_CHANNEL_MASK) | chainArray[chainIndex];

            // ADC start conversion
            SET_BIT(ADCSRA, 6);
        }
    }
}