/*
 * ADC_interface.h
 *
 *  Created on: Oct 31, 2026
 *      Author: Hamdi
 */

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_

typedef enum
{

    ADC_OK = 0,
    ADC_NOK,
    ADC_INVALID_CHANNEL,
    ADC_INVALID_PRESCALER,
    ADC_NULLPTR,
    ADC_TIME_OUT,
    ADC_BUSY_STATE
} ADC_errorStatus;

#define ADC_CHANNEL_0 0
#define ADC_CHANNEL_1 1
#define ADC_CHANNEL_2 2
#define ADC_CHANNEL_3 3
#define ADC_CHANNEL_4 4
#define ADC_CHANNEL_5 4
#define ADC_CHANNEL_6 6
#define ADC_CHANNEL_7 7

#define ADC_EXTERNAL_AREF 0
#define ADC_EXTERNAL_AVCC 1
#define ADC_INTERNAL_2_56 2

#define ADC_RIGHT_ADJUST 0
#define ADC_LEFT_ADJUST 1

#define ADC_DISABLE 0
#define ADC_ENABLE 1

#define ADC_PRESCALER_2 0
#define ADC_PRESCALER_4 2
#define ADC_PRESCALER_8 3
#define ADC_PRESCALER_16 4
#define ADC_PRESCALER_32 5
#define ADC_PRESCALER_64 6
#define ADC_PRESCALER_128 7

#define ADC_INT_OFF 0
#define ADC_INT_ON 1

#define ADC_SINGLE_CONVERSION 0
#define ADC_FREE_RUNNING 1
#define ADC_ANALOG_COMPARATOR 2
#define ADC_EXTI0 3
#define ADC_TIMER0_CTC 4
#define ADC_TIMER0_OVF 5
#define ADC_TIMER1_CTC_CHANNEL_B 6
#define ADC_TIMER1_OVF 7
#define ADC_TIMER1_ICU 8

#define ADC_IDLE 0
#define ADC_BUSY 1

#define SINGLE_CHANNEL_ASYNCH 0
#define CHAIN_CHANNEL_ASYNCH 1

typedef struct
{
    uint8 *Channel;
    uint16 *Result;
    uint8 Size;
    void (*notificationFunc)(void);
} ADC_t;

void ADC_voidInitialize(void);
void ADC_voidEnable(void);
void ADC_voidDisable(void);
ADC_errorStatus ADC_enumSetPrescallar(uint8 pre);
void ADC_voidInterruptEnable(void);
void ADC_voidInterruptDisable(void);

ADC_errorStatus ADC_enumGetResultSync(uint8 channel, uint16 *result);
ADC_errorStatus ADC_enumStartConversionAsynch(uint8 channel, uint16 *reading, void (*notificationFunc)(void));
ADC_errorStatus ADC_enumStartChainAsynch(ADC_t *chain);

#endif /* MCAL_ADC_ADC_INTERFACE_H_ */