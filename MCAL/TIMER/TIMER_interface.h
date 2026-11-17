/*
 * TIMER_interface.h
 *
 *  Created on: Nov 3, 2026
 *      Author: Hamdi
 */

#ifndef MCAL_TIMER_TIMER_INTERFACE_H_
#define MCAL_TIMER_TIMER_INTERFACE_H_

#define DISABLE 0
#define ENABLE 1

#define TIMER0 0
#define TIMER1 1
#define TIMER2 2

#define TIMER0_OVF_ID 11
#define TIMER0_CTC_ID 10

#define TIMER1_OVF_ID 9
#define TIMER1_CTC_B_ID 8
#define TIMER1_CTC_A_ID 7
#define TIMER1_ICU_ID 6

#define TIMER2_OVF_ID 5
#define TIMER2_CTC_ID 4

// TIMER0 modes
#define TIMER0_MODE_NORMAL 0
#define TIMER0_MODE_PHASE_CORRECT_PWM 1
#define TIMER0_MODE_CTC 2
#define TIMER0_MODE_FAST_PWM 3

// TIMER1 modes
#define TIMER1_MODE_NORMAL 0
#define TIMER1_MODE_PHASE_CORRECT_PWM_8BIT 1
#define TIMER1_MODE_PHASE_CORRECT_PWM_9BIT 2
#define TIMER1_MODE_PHASE_CORRECT_PWM_10BIT 3
#define TIMER1_MODE_CTC_OCR1A 4
#define TIMER1_MODE_FAST_PWM_8BIT 5
#define TIMER1_MODE_FAST_PWM_9BIT 6
#define TIMER1_MODE_FAST_PWM_10BIT 7
#define TIMER1_MODE_PHASE_FREQUENCY_CORRECT_PWM_ICR1 8
#define TIMER1_MODE_PHASE_FREQUENCY_CORRECT_PWM_OCR1A 9
#define TIMER1_MODE_PHASE_CORRECT_PWM_ICR1 11
#define TIMER1_MODE_PHASE_CORRECT_PWM_OCR1A 10
#define TIMER1_MODE_CTC_ICR1 12
#define TIMER1_MODE_FAST_PWM_ICR1 14
#define TIMER1_MODE_FAST_PWM_OCR1A 15

// TIMER2 modes
#define TIMER2_MODE_NORMAL 0
#define TIMER2_MODE_PHASE_CORRECT_PWM 1
#define TIMER2_MODE_CTC 2
#define TIMER2_MODE_FAST_PWM 3

// TIMER1 input capture edge selection
#define TIMER1_ICU_FALLING_EDGE 0
#define TIMER1_ICU_RISING_EDGE 1

#define TIMER0_PRESCALER_NO_CLOCK 0
#define TIMER0_PRESCALER_NO_PRESCALER 1
#define TIMER0_PRESCALER_8 8
#define TIMER0_PRESCALER_64 64
#define TIMER0_PRESCALER_256 256
#define TIMER0_PRESCALER_1024 1024
#define TIMER0_PRESCALER_EXTERNAL_FALLING 6
#define TIMER0_PRESCALER_EXTERNAL_RISING 7

#define TIMER1_PRESCALER_NO_CLOCK 0
#define TIMER1_PRESCALER_NO_PRESCALER 1
#define TIMER1_PRESCALER_8 2
#define TIMER1_PRESCALER_64 3
#define TIMER1_PRESCALER_256 4
#define TIMER1_PRESCALER_1024 5
#define TIMER1_PRESCALER_EXTERNAL_FALLING 6
#define TIMER1_PRESCALER_EXTERNAL_RISING 7

#define TIMER2_PRESCALER_NO_CLOCK 0
#define TIMER2_PRESCALER_NO_PRESCALER 1
#define TIMER2_PRESCALER_8 2
#define TIMER2_PRESCALER_32 3
#define TIMER2_PRESCALER_64 4
#define TIMER2_PRESCALER_128 5
#define TIMER2_PRESCALER_256 6
#define TIMER2_PRESCALER_1024 7

// OC0 pin configuration
#define OC0_DISCONNECTED 0
#define OC0_TOGGLE_ON_COMPARE_MATCH 1
#define OC0_CLEAR_ON_COMPARE_MATCH 2 // Non-inverting
#define OC0_SET_ON_COMPARE_MATCH 3 // Inverting

// OC1A pin configuration
#define OC1A_DISCONNECTED 0
#define OC1A_TOGGLE_ON_COMPARE_MATCH 1
#define OC1A_CLEAR_ON_COMPARE_MATCH 2 // Non-inverting
#define OC1A_SET_ON_COMPARE_MATCH 3   // Inverting

// OC1B pin configuration
#define OC1B_DISCONNECTED 0
#define OC1B_TOGGLE_ON_COMPARE_MATCH 1
#define OC1B_CLEAR_ON_COMPARE_MATCH 2 // Non-inverting
#define OC1B_SET_ON_COMPARE_MATCH 3   // Inverting

// OC2 pin configuration
#define OC2_DISCONNECTED 0
#define OC2_TOGGLE_ON_COMPARE_MATCH 1
#define OC2_CLEAR_ON_COMPARE_MATCH 2 // Non-inverting
#define OC2_SET_ON_COMPARE_MATCH 3  // Inverting

// Watchdog Timer prescaler configuration
#define WDT_PRESCALER_16_3_MS 0
#define WDT_PRESCALER_32_5_MS 1
#define WDT_PRESCALER_65_MS 2
#define WDT_PRESCALER_0_13_S 3
#define WDT_PRESCALER_0_26_S 4
#define WDT_PRESCALER_0_52_S 5
#define WDT_PRESCALER_1_S 6
#define WDT_PRESCALER_2_1_S 7

typedef enum
{
    TIMER_OK,
    TIMER_NOK,
    TIMER_INVALID_NUMBER,
    TIMER_INVALID_VALUE,
    TIMER_INVALID_PRESCALER,
    TIMER_NULL_POINTER
} TIMER_errorStatus;

void TIMER0_voidInit(void);
void TIMER0_voidSetPreload(uint8 timer_preload);
void TIMER0_voidSetCTC(uint8 value);
TIMER_errorStatus TIMER0_enumGetTimerCounterValue(uint8 *timer_preload);
void TIMER0_voidStopTimer(void);

void TIMER1_voidInit(void);
void TIMER1_voidSetPreload(uint16 timer_preload);
void TIMER1_voidSetCTCA(uint16 value);
void TIMER1_voidSetCTCB(uint16 value);
void TIMER1_voidSetICR(uint16 value);
TIMER_errorStatus TIMER1_enumGetTimerCounterValue(uint16 *timer_preload);
void TIMER1_voidStopTimer(void);
void TIMER1_voidICUInit(void);
TIMER_errorStatus TIMER1_enumSetTriggerEdge(uint8 icu_edge);
void TIMER1_voidEnableICUInterrupt(void);
void TIMER1_voidDisableICUInterrupt(void);
TIMER_errorStatus TIMER1_enumGetICRValue(uint16 *icr_value);

void TIMER2_voidInit(void);
void TIMER2_voidSetPreload(uint8 timer_preload);
void TIMER2_voidSetCTC(uint8 value);
TIMER_errorStatus TIMER2_enumGetTimerCounterValue(uint8 *timer_preload);
void TIMER2_voidStopTimer(void);

TIMER_errorStatus TIMER_enumSetCallBack(void (*ptr)(void), uint8 timer_id);

void TIMER_voidWDTSleep(void);
void TIMER_voidWDTEnable (void);
void TIMER_voidWDTDisable(void);

#endif /* MCAL_TIMER_TIMER_INTERFACE_H_ */
