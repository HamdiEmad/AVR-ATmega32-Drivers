/*
 * TIMER_program.c
 *
 *  Created on: Nov 3, 2026
 *      Author: Hamdi
 */

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_config.h"

static void (*callBacks[12])(void) = {NULL};

void TIMER0_voidInit(void)
{
    // Set TIMER0 prescaler
    TCCR0 &= TIMER_PRESCALER_MASK;

    #if TIMER0_PRESCALER == TIMER0_PRESCALER_NO_CLOCK
    #elif TIMER0_PRESCALER == TIMER0_PRESCALER_NO_PRESCALER
        SET_BIT(TCCR0, CS00);
    #elif TIMER0_PRESCALER == TIMER0_PRESCALER_8
        SET_BIT(TCCR0, CS01);
    #elif TIMER0_PRESCALER == TIMER0_PRESCALER_64
        SET_BIT(TCCR0, CS00);
        SET_BIT(TCCR0, CS01);
    #elif TIMER0_PRESCALER == TIMER0_PRESCALER_256
        SET_BIT(TCCR0, CS02);
    #elif TIMER0_PRESCALER == TIMER0_PRESCALER_1024
        SET_BIT(TCCR0, CS00);
        SET_BIT(TCCR0, CS02);
    #elif TIMER0_PRESCALER == TIMER0_PRESCALER_EXTERNAL_FALLING
        SET_BIT(TCCR0, CS01);
        SET_BIT(TCCR0, CS02);
    #elif TIMER0_PRESCALER == TIMER0_PRESCALER_EXTERNAL_RISING
        SET_BIT(TCCR0, CS00);
        SET_BIT(TCCR0, CS01);
        SET_BIT(TCCR0, CS02);
    #else
        #error "INVALID TIMER PRESCALER!"
    #endif

    // Set TIMER0 mode
    #if TIMER0_MODE == TIMER0_MODE_NORMAL
        CLR_BIT(TCCR0, WGM00);
        CLR_BIT(TCCR0, WGM01);
        // Set OC0 pin configuration - NORMAL mode
        #if OC0_CONFIGURATION == OC0_DISCONNECTED
            CLR_BIT(TCCR0, COM00);
            CLR_BIT(TCCR0, COM01);
        #elif OC0_CONFIGURATION == OC0_TOGGLE_ON_COMPARE_MATCH
            SET_BIT(TCCR0, COM00);
            CLR_BIT(TCCR0, COM01);
        #elif OC0_CONFIGURATION == OC0_CLEAR_ON_COMPARE_MATCH
            CLR_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);
        #elif OC0_CONFIGURATION == OC0_SET_ON_COMPARE_MATCH
            SET_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);
        #else
            #error "INVALID OC0 PIN CONFIGURATION"
        #endif
        #if TIMER0_OVERFLOW_INTERRUPT == ENABLE
            SET_BIT(TIMSK, TOIE0); // Enable TIMER0 overflow interrupt
        #elif TIMER0_OVERFLOW_INTERRUPT == DISABLE
            CLR_BIT(TIMSK, TOIE0); // Disable TIMER0 overflow interrupt
        #else
            #error "INVALID TIMER0 OVERFLOW INTERRUPT CONFIGURATION!"
        #endif

    #elif TIMER0_MODE == TIMER0_MODE_PHASE_CORRECT_PWM
        SET_BIT(TCCR0, WGM00);
        CLR_BIT(TCCR0, WGM01);
        // Set OC0 pin configuration - PHASE CORRECT PWM Mode
        #if OC0_CONFIGURATION == OC0_DISCONNECTED
            CLR_BIT(TCCR0, COM00);
            CLR_BIT(TCCR0, COM01);
        #elif OC0_CONFIGURATION == OC0_CLEAR_ON_COMPARE_MATCH
            CLR_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);
        #elif OC0_CONFIGURATION == OC0_SET_ON_COMPARE_MATCH
            SET_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);
        #else
            #error "INVALID OC0 PIN CONFIGURATION"
        #endif
        #if TIMER0_COMPARE_MATCH_INTERRUPT == ENABLE
            SET_BIT(TIMSK, OCIE0); // Enable TIMER0 output compare match interrupt
        #elif TIMER0_COMPARE_MATCH_INTERRUPT == DISABLE
            CLR_BIT(TIMSK, OCIE0); // Disable TIMER0 output compare match interrupt
        #else
            #error "INVALID TIMER0 COMPARE MATCH INTERRUPT CONFIGURATION!"
        #endif

    #elif TIMER0_MODE == TIMER0_MODE_CTC
        CLR_BIT(TCCR0, WGM00);
        SET_BIT(TCCR0, WGM01);
        // Set OC0 pin configuration - CTC Mode
        #if OC0_CONFIGURATION == OC0_DISCONNECTED
            CLR_BIT(TCCR0, COM00);
            CLR_BIT(TCCR0, COM01);
        #elif OC0_CONFIGURATION == OC0_TOGGLE_ON_COMPARE_MATCH
            SET_BIT(TCCR0, COM00);
            CLR_BIT(TCCR0, COM01);
        #elif OC0_CONFIGURATION == OC0_CLEAR_ON_COMPARE_MATCH
            CLR_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);
        #elif OC0_CONFIGURATION == OC0_SET_ON_COMPARE_MATCH
            SET_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);
        #else
            #error "INVALID OC0 PIN CONFIGURATION"
        #endif
        #if TIMER0_COMPARE_MATCH_INTERRUPT == ENABLE
            SET_BIT(TIMSK, OCIE0); // Enable TIMER0 output compare match interrupt
        #elif TIMER0_COMPARE_MATCH_INTERRUPT == DISABLE
            CLR_BIT(TIMSK, OCIE0); // Disable TIMER0 output compare match interrupt
        #else
            #error "INVALID TIMER0 COMPARE MATCH INTERRUPT CONFIGURATION!"
        #endif

    #elif TIMER0_MODE == TIMER0_MODE_FAST_PWM
        SET_BIT(TCCR0, WGM00);
        SET_BIT(TCCR0, WGM01);
        // Set OC0 pin configuration - FAST PWM Mode
        #if OC0_CONFIGURATION == OC0_DISCONNECTED
            CLR_BIT(TCCR0, COM00);
            CLR_BIT(TCCR0, COM01);
        #elif OC0_CONFIGURATION == OC0_CLEAR_ON_COMPARE_MATCH
            CLR_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);
        #elif OC0_CONFIGURATION == OC0_SET_ON_COMPARE_MATCH
            SET_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);
        #else
            #error "INVALID OC0 PIN CONFIGURATION"
        #endif
        #if TIMER0_COMPARE_MATCH_INTERRUPT == ENABLE
            SET_BIT(TIMSK, OCIE0); // Enable TIMER0 output compare match interrupt
        #elif TIMER0_COMPARE_MATCH_INTERRUPT == DISABLE
            CLR_BIT(TIMSK, OCIE0); // Disable TIMER0 output compare match interrupt
        #else
            #error "INVALID TIMER0 COMPARE MATCH INTERRUPT CONFIGURATION!"
        #endif
        #else
            #error "INVALID TIMER MODE!"
        #endif

        SET_BIT(SREG, 7); // Enable global interrupts
}

void TIMER0_voidSetPreload(uint8 timer_preload)
{
    TCNT0 = timer_preload;
}

void TIMER0_voidSetCTC(uint8 value)
{
    OCR0 = value;
}

TIMER_errorStatus TIMER0_enumGetTimerCounterValue(uint8 *timer_preload)
{
    TIMER_errorStatus status = TIMER_OK;

    if (timer_preload != NULL)
        *timer_preload = TCNT0;
    else
        status = TIMER_NULL_POINTER;

    return status;
}

void TIMER0_voidStopTimer(void)
{
    CLR_BIT(TCCR0, CS00);
    CLR_BIT(TCCR0, CS01);
    CLR_BIT(TCCR0, CS02);
}



void TIMER1_voidInit(void)
{
    // Set TIMER1 prescaler
    #if TIMER1_PRESCALER == TIMER1_PRESCALER_NO_CLOCK
        CLR_BIT(TCCR1B, CS10);
        CLR_BIT(TCCR1B, CS11);
        CLR_BIT(TCCR1B, CS12);
    #elif TIMER1_PRESCALER == TIMER1_PRESCALER_NO_PRESCALER
        SET_BIT(TCCR1B, CS10);
        CLR_BIT(TCCR1B, CS11);
        CLR_BIT(TCCR1B, CS12);
    #elif TIMER1_PRESCALER == TIMER1_PRESCALER_8
        CLR_BIT(TCCR1B, CS10);
        SET_BIT(TCCR1B, CS11);
        CLR_BIT(TCCR1B, CS12);
    #elif TIMER1_PRESCALER == TIMER1_PRESCALER_64
        SET_BIT(TCCR1B, CS10);
        SET_BIT(TCCR1B, CS11);
        CLR_BIT(TCCR1B, CS12);
    #elif TIMER1_PRESCALER == TIMER1_PRESCALER_256
        CLR_BIT(TCCR1B, CS10);
        CLR_BIT(TCCR1B, CS11);
        SET_BIT(TCCR1B, CS12);
    #elif TIMER1_PRESCALER == TIMER1_PRESCALER_1024
        SET_BIT(TCCR1B, CS10);
        CLR_BIT(TCCR1B, CS11);
        SET_BIT(TCCR1B, CS12);
    #elif TIMER1_PRESCALER == TIMER1_PRESCALER_EXTERNAL_FALLING
        CLR_BIT(TCCR1B, CS10);
        SET_BIT(TCCR1B, CS11);
        SET_BIT(TCCR1B, CS12);
    #elif TIMER1_PRESCALER == TIMER1_PRESCALER_EXTERNAL_RISING
        SET_BIT(TCCR1B, CS10);
        SET_BIT(TCCR1B, CS11);
        SET_BIT(TCCR1B, CS12);
    #else
    #error "INVALID TIMER1 PRESCALER!"
    #endif

    // TIMER1 mode configuration
    #if TIMER1_MODE == TIMER1_MODE_NORMAL
        CLR_BIT(TCCR1A, WGM10);
        CLR_BIT(TCCR1A, WGM11);
        CLR_BIT(TCCR1B, WGM12);
        CLR_BIT(TCCR1B, WGM13);

    #elif (TIMER1_MODE == TIMER1_MODE_CTC_OCR1A) || (TIMER1_MODE == TIMER1_MODE_CTC_ICR1)
        #if TIMER1_MODE == TIMER1_MODE_CTC_OCR1A
            CLR_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
        #elif TIMER1_MODE == TIMER1_MODE_CTC_ICR1
            CLR_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
            // Set input capture edge selection
            #if TIMER1_ICU_EDGE_SELECT == TIMER1_ICU_FALLING_EDGE
                CLR_BIT(TCCR1B, ICES1);
            #elif TIMER1_ICU_EDGE_SELECT == TIMER1_ICU_RISING_EDGE
                SET_BIT(TCCR1B, ICES1);
            #else
                #error "INVALID TIMER1 INPUT CAPTURE EDGE SELECTION!"
            #endif
        #else
        #endif
        // Set OC1A and OC1B pin configuration - CTC mode
        #if OC1A_CONFIGURATION == OC1A_DISCONNECTED
            CLR_BIT(TCCR1A, COM1A0);
            CLR_BIT(TCCR1A, COM1A1);
        #elif OC1A_CONFIGURATION == OC1A_TOGGLE_ON_COMPARE_MATCH
            SET_BIT(TCCR1A, COM1A0);
            CLR_BIT(TCCR1A, COM1A1);
        #elif OC1A_CONFIGURATION == OC1A_CLEAR_ON_COMPARE_MATCH
            CLR_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
        #elif OC1A_CONFIGURATION == OC1A_SET_ON_COMPARE_MATCH
            SET_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
        #else
            #error "INVALID OC1A PIN CONFIGURATION"
        #endif
        // Set OC1B pin configuration - CTC mode
        #if OC1B_CONFIGURATION == OC1B_DISCONNECTED
            CLR_BIT(TCCR1A, COM1B0);
            CLR_BIT(TCCR1A, COM1B1);
        #elif OC1B_CONFIGURATION == OC1B_TOGGLE_ON_COMPARE_MATCH
            SET_BIT(TCCR1A, COM1B0);
            CLR_BIT(TCCR1A, COM1B1);
        #elif OC1B_CONFIGURATION == OC1B_CLEAR_ON_COMPARE_MATCH
            CLR_BIT(TCCR1A, COM1B0);
            SET_BIT(TCCR1A, COM1B1);
        #elif OC1B_CONFIGURATION == OC1B_SET_ON_COMPARE_MATCH
            SET_BIT(TCCR1A, COM1B0);
            SET_BIT(TCCR1A, COM1B1);
        #else
            #error "INVALID OC1B PIN CONFIGURATION"
        #endif

    #elif TIMER1_MODE == TIMER1_MODE_PHASE_CORRECT_PWM_ICR1 || TIMER1_MODE == TIMER1_MODE_PHASE_CORRECT_PWM_OCR1A || TIMER1_MODE == TIMER1_MODE_PHASE_FREQUENCY_CORRECT_PWM_ICR1 || TIMER1_MODE == TIMER1_MODE_PHASE_FREQUENCY_CORRECT_PWM_OCR1A || TIMER1_MODE == TIMER1_MODE_PHASE_CORRECT_PWM_8BIT || TIMER1_MODE == TIMER1_MODE_PHASE_CORRECT_PWM_9BIT || TIMER1_MODE == TIMER1_MODE_PHASE_CORRECT_PWM_10BIT
        #if TIMER1_MODE == TIMER1_MODE_PHASE_FREQUENCY_CORRECT_PWM_ICR1
            CLR_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
        #elif TIMER1_MODE == TIMER1_MODE_PHASE_FREQUENCY_CORRECT_PWM_OCR1A
            SET_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
        #elif TIMER1_MODE == TIMER1_MODE_PHASE_CORRECT_PWM_ICR1
            CLR_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
        #elif TIMER1_MODE == TIMER1_MODE_PHASE_CORRECT_PWM_OCR1A
            SET_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
        #elif TIMER1_MODE == TIMER1_MODE_PHASE_CORRECT_PWM_8BIT
            SET_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
        #elif TIMER1_MODE == TIMER1_MODE_PHASE_CORRECT_PWM_9BIT
            CLR_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
        #elif TIMER1_MODE == TIMER1_MODE_PHASE_CORRECT_PWM_10BIT
            SET_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
        #else
        #endif
        #if TIMER1_MODE == TIMER1_MODE_PHASE_CORRECT_PWM_ICR1 || TIMER1_MODE == TIMER1_MODE_PHASE_FREQUENCY_CORRECT_PWM_ICR1
            // Set input capture edge selection
            #if TIMER1_ICU_EDGE_SELECT == TIMER1_ICU_FALLING_EDGE
                CLR_BIT(TCCR1B, ICES1);
            #elif TIMER1_ICU_EDGE_SELECT == TIMER1_ICU_RISING_EDGE
                SET_BIT(TCCR1B, ICES1);
            #else
                #error "INVALID TIMER1 INPUT CAPTURE EDGE SELECTION!"
            #endif
        #else
        #endif
        // Set OC1A pin configuration
        #if OC1A_CONFIGURATION == OC1A_DISCONNECTED
            CLR_BIT(TCCR1A, COM1A0);
            CLR_BIT(TCCR1A, COM1A1);
        #elif OC1A_CONFIGURATION == OC1A_CLEAR_ON_COMPARE_MATCH
            CLR_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
        #elif OC1A_CONFIGURATION == OC1A_SET_ON_COMPARE_MATCH
            SET_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
        #else
            #error "INVALID OC1A PIN CONFIGURATION"
        #endif
        // Set OC1B pin configuration
        #if OC1B_CONFIGURATION == OC1B_DISCONNECTED
            CLR_BIT(TCCR1A, COM1B0);
            CLR_BIT(TCCR1A, COM1B1);
        #elif OC1B_CONFIGURATION == OC1B_CLEAR_ON_COMPARE_MATCH
            CLR_BIT(TCCR1A, COM1B0);
            SET_BIT(TCCR1A, COM1B1);
        #elif OC1B_CONFIGURATION == OC1B_SET_ON_COMPARE_MATCH
            SET_BIT(TCCR1A, COM1B0);
            SET_BIT(TCCR1A, COM1B1);
        #else
            #error "INVALID OC1B PIN CONFIGURATION"
        #endif

    #elif (TIMER1_MODE == TIMER1_MODE_FAST_PWM_8BIT) || (TIMER1_MODE == TIMER1_MODE_FAST_PWM_9BIT) || (TIMER1_MODE == TIMER1_MODE_FAST_PWM_10BIT) || (TIMER1_MODE == TIMER1_MODE_FAST_PWM_ICR1) || (TIMER1_MODE == TIMER1_MODE_FAST_PWM_OCR1A)
        #if TIMER1_MODE == TIMER1_MODE_FAST_PWM_8BIT
            SET_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
        #elif TIMER1_MODE == TIMER1_MODE_FAST_PWM_9BIT
            CLR_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
        #elif TIMER1_MODE == TIMER1_MODE_FAST_PWM_10BIT
            SET_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
        #elif TIMER1_MODE == TIMER1_MODE_FAST_PWM_ICR1
            CLR_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
            // Set input capture edge selection
            #if TIMER1_ICU_EDGE_SELECT == TIMER1_ICU_FALLING_EDGE
                CLR_BIT(TCCR1B, ICES1);
            #elif TIMER1_ICU_EDGE_SELECT == TIMER1_ICU_RISING_EDGE
                SET_BIT(TCCR1B, ICES1);
            #else
                #error "INVALID TIMER1 INPUT CAPTURE EDGE SELECTION!"
            #endif
        #elif TIMER1_MODE == TIMER1_MODE_FAST_PWM_OCR1A
            SET_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
        #else
        #endif
        // Set OC1A configuration
        #if OC1A_CONFIGURATION == OC1A_DISCONNECTED
            CLR_BIT(TCCR1A, COM1A0);
            CLR_BIT(TCCR1A, COM1A1);
        #elif OC1A_CONFIGURATION == OC1A_CLEAR_ON_COMPARE_MATCH
            CLR_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
        #elif OC1A_CONFIGURATION == OC1A_SET_ON_COMPARE_MATCH
            SET_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
        #else
            #error "INVALID OC1A PIN CONFIGURATION"
        #endif
        // Set OC1B pin configuration - CTC mode
        #if OC1B_CONFIGURATION == OC1B_DISCONNECTED
            CLR_BIT(TCCR1A, COM1B0);
            CLR_BIT(TCCR1A, COM1B1);
        #elif OC1B_CONFIGURATION == OC1B_CLEAR_ON_COMPARE_MATCH
            CLR_BIT(TCCR1A, COM1B0);
            SET_BIT(TCCR1A, COM1B1);
        #elif OC1B_CONFIGURATION == OC1B_SET_ON_COMPARE_MATCH
            SET_BIT(TCCR1A, COM1B0);
            SET_BIT(TCCR1A, COM1B1);
        #else
            #error "INVALID OC1B PIN CONFIGURATION"
        #endif
    #else
        #error "INVALID TIMER1 MODE!"
    #endif

    // Set TIMER1 COMPARE A interrupt
    #if TIMER1_COMPARE_MATCH_A_INTERRUPT == ENABLE
        SET_BIT(TIMSK, OCIE1A); // Enable TIMER1 output compare match A interrupt
    #elif TIMER1_COMPARE_MATCH_A_INTERRUPT == DISABLE
        CLR_BIT(TIMSK, OCIE1A); // Disable TIMER1 output compare match A interrupt
    #else
        #error "INVALID TIMER1 COMPARE MATCH A INTERRUPT CONFIGURATION!"
    #endif

    // Set TIMER1 COMPARE B interrupt
    #if TIMER1_COMPARE_MATCH_B_INTERRUPT == ENABLE
        SET_BIT(TIMSK, OCIE1B); // Enable TIMER1 output compare match B interrupt
    #elif TIMER1_COMPARE_MATCH_B_INTERRUPT == DISABLE
        CLR_BIT(TIMSK, OCIE1B); // Disable TIMER1 output compare match B interrupt
    #else
        #error "INVALID TIMER1 COMPARE MATCH B INTERRUPT CONFIGURATION!"
    #endif

    // Set ICU interrupt
    #if TIMER1_INPUT_CAPTURE_INTERRUPT == ENABLE
        SET_BIT(TIMSK, TICIE1); // Enable TIMER1 input capture interrupt
    #elif TIMER1_INPUT_CAPTURE_INTERRUPT == DISABLE
        CLR_BIT(TIMSK, TICIE1); // Disable TIMER1 input capture interrupt
    #else
        #error "INVALID TIMER1 INPUT CAPTURE INTERRUPT CONFIGURATION!"
    #endif

    // Set TIMER1 OVERFLOW interrupt
    #if TIMER1_OVERFLOW_INTERRUPT == ENABLE
        SET_BIT(TIMSK, TOIE1); // Enable TIMER1 overflow interrupt
    #elif TIMER1_OVERFLOW_INTERRUPT == DISABLE
        CLR_BIT(TIMSK, TOIE1); // Disable TIMER1 overflow interrupt
     #else
        #error "INVALID TIMER1 OVERFLOW INTERRUPT CONFIGURATION!"
    #endif

    // Enable global interrupt
    SET_BIT(SREG, 7);
}

void TIMER1_voidSetPreload(uint16 timer_preload)
{
    TCNT1 = timer_preload;
}

void TIMER1_voidSetCTCA(uint16 value)
{
    OCR1A = value;
}

void TIMER1_voidSetCTCB(uint16 value)
{
    OCR1B = value;
}

void TIMER1_voidSetICR(uint16 value)
{
    ICR1 = value;
}

TIMER_errorStatus TIMER1_enumGetTimerCounterValue(uint16 *timer_preload)
{
    TIMER_errorStatus status = TIMER_OK;

    if (timer_preload != NULL)
        *timer_preload = TCNT1;
    else
        status = TIMER_NULL_POINTER;

    return status;
}

void TIMER1_voidStopTimer(void)
{
    CLR_BIT(TCCR1B, CS10);
    CLR_BIT(TCCR1B, CS11);
    CLR_BIT(TCCR1B, CS12);
}

void TIMER1_voidICUInit(void)
{
    // Set input capture edge selection
    #if TIMER1_ICU_EDGE_SELECT == TIMER1_ICU_FALLING_EDGE
        CLR_BIT(TCCR1B, ICES1);
    #elif TIMER1_ICU_EDGE_SELECT == TIMER1_ICU_RISING_EDGE
        SET_BIT(TCCR1B, ICES1);
    #else
    #error "INVALID TIMER1 INPUT CAPTURE EDGE SELECTION!"
    #endif
    
    // Set ICU noise canceler
    #if TIMER1_ICU_NOISE_CANCELER == ENABLE
        SET_BIT(TCCR1B, ICNC1);
    #elif TIMER1_ICU_NOISE_CANCELER == DISABLE
        CLR_BIT(TCCR1B, ICNC1);
    #else
    #error "INVALID TIMER1 INPUT CAPTURE EDGE SELECTION!"
    #endif

    // Enable input capture unit interrupt 
    #if TIMER1_INPUT_CAPTURE_INTERRUPT == ENABLE
        SET_BIT(TIMSK, TICIE1);
    #elif TIMER1_INPUT_CAPTURE_INTERRUPT == DISABLE
        CLR_BIT(TIMSK, TICIE1);
    #else
        #error "INVALID TIMER1 ICU INTERRUPT CONFIGURATION!"
    #endif
}

TIMER_errorStatus TIMER1_enumSetTriggerEdge(uint8 icu_edge)
{
    TIMER_errorStatus status = TIMER_OK;

    if (icu_edge == TIMER1_ICU_FALLING_EDGE)
        CLR_BIT(TCCR1B, ICES1);
    else if (icu_edge == TIMER1_ICU_RISING_EDGE)
        SET_BIT(TCCR1B, ICES1);
    else
        status = TIMER_INVALID_VALUE;
    
    return status;
}

void TIMER1_voidEnableICUInterrupt(void)
{
    SET_BIT(TIMSK, TICIE1);
}

void TIMER1_voidDisableICUInterrupt(void)
{
    CLR_BIT(TIMSK, TICIE1);
}

TIMER_errorStatus TIMER1_enumGetICRValue(uint16 *icr_value)
{
    TIMER_errorStatus status = TIMER_OK;

    if (icr_value != NULL)
        *icr_value = ICR1;
    else
        status = TIMER_NULL_POINTER;

    return status;
}



void TIMER2_voidInit(void)
{
    uint8 local_TCCR2 = 0;

    // Disable TIMER2 interrupts
    CLR_BIT(TIMSK, TOIE2); // Disable TIMER2 overflow interrupt
    CLR_BIT(TIMSK, OCIE2); // Disable TIMER2 output compare match interrupt

    // Wait for the update of the registers to complete
    while (ASSR & ((1 << TCR2UB) | (1 << OCR2UB) | (1 << TCN2UB)));

    // Stop TIMER2
    TCCR2 = 0;

    while (GET_BIT(ASSR, TCR2UB));

    #if TIMER2_ASYNC_MODE == ENABLE
        SET_BIT(ASSR, AS2); // Enable asynchronous mode
    #elif TIMER2_ASYNC_MODE == DISABLE
        CLR_BIT(ASSR, AS2); // Enable synchronous mode
    #else
        #error "INVALID TIMER2 ASYNC MODE CONFIGURATION!"
    #endif

    // Wait for synchronization of the registers to complete
    while (ASSR & ((1 << TCR2UB) | (1 << OCR2UB) | (1 << TCN2UB)));

    TCNT2 = 0;

    // Set TIMER2 prescaler
    #if TIMER2_PRESCALER == TIMER2_PRESCALER_NO_CLOCK
    #elif TIMER2_PRESCALER == TIMER2_PRESCALER_NO_PRESCALER
        SET_BIT(local_TCCR2, CS20);
    #elif TIMER2_PRESCALER == TIMER2_PRESCALER_8
        SET_BIT(local_TCCR2, CS21);
    #elif TIMER2_PRESCALER == TIMER2_PRESCALER_32
        SET_BIT(local_TCCR2, CS20);
        SET_BIT(local_TCCR2, CS21);
    #elif TIMER2_PRESCALER == TIMER2_PRESCALER_64
        SET_BIT(local_TCCR2, CS22);
    #elif TIMER2_PRESCALER == TIMER2_PRESCALER_128
        SET_BIT(local_TCCR2, CS20);
        SET_BIT(local_TCCR2, CS22);
    #elif TIMER2_PRESCALER == TIMER2_PRESCALER_256
        SET_BIT(local_TCCR2, CS21);
        SET_BIT(local_TCCR2, CS22);
    #elif TIMER2_PRESCALER == TIMER2_PRESCALER_1024
        SET_BIT(local_TCCR2, CS20);
        SET_BIT(local_TCCR2, CS21);
        SET_BIT(local_TCCR2, CS22);
    #else
        #error "INVALID TIMER2 PRESCALER!"
    #endif

    // Set TIMER2 mode
    #if TIMER2_MODE == TIMER2_MODE_NORMAL
        CLR_BIT(local_TCCR2, WGM20);
        CLR_BIT(local_TCCR2, WGM21);
        // Set OC2 pin configuration - NORMAL mode
        #if OC2_CONFIGURATION == OC2_DISCONNECTED
            CLR_BIT(local_TCCR2, COM20);
            CLR_BIT(local_TCCR2, COM21);
        #elif OC2_CONFIGURATION == OC2_TOGGLE_ON_COMPARE_MATCH
            SET_BIT(local_TCCR2, COM20);
            CLR_BIT(local_TCCR2, COM21);
        #elif OC2_CONFIGURATION == OC2_CLEAR_ON_COMPARE_MATCH
            CLR_BIT(local_TCCR2, COM20);
            SET_BIT(local_TCCR2, COM21);
        #elif OC2_CONFIGURATION == OC2_SET_ON_COMPARE_MATCH
            SET_BIT(local_TCCR2, COM20);
            SET_BIT(local_TCCR2, COM21);
        #else
        #error "INVALID OC2 PIN CONFIGURATION"
        #endif

    #elif TIMER2_MODE == TIMER2_MODE_PHASE_CORRECT_PWM
        SET_BIT(local_TCCR2, WGM20);
        CLR_BIT(local_TCCR2, WGM21);
        // Set OC2 pin configuration - PHASE CORRECT PWM Mode
        #if OC2_CONFIGURATION == OC2_DISCONNECTED
            CLR_BIT(local_TCCR2, COM20);
            CLR_BIT(local_TCCR2, COM21);
        #elif OC2_CONFIGURATION == OC2_CLEAR_ON_COMPARE_MATCH
            CLR_BIT(local_TCCR2, COM20);
            SET_BIT(local_TCCR2, COM21);
        #elif OC2_CONFIGURATION == OC2_SET_ON_COMPARE_MATCH
            SET_BIT(local_TCCR2, COM20);
            SET_BIT(local_TCCR2, COM21);
        #else
            #error "INVALID OC2 PIN CONFIGURATION"
        #endif

    #elif TIMER2_MODE == TIMER2_MODE_CTC
        CLR_BIT(local_TCCR2, WGM20);
        SET_BIT(local_TCCR2, WGM21);
        // Set OC2 pin configuration - CTC Mode
        #if OC2_CONFIGURATION == OC2_DISCONNECTED
            CLR_BIT(local_TCCR2, COM20);
            CLR_BIT(local_TCCR2, COM21);
        #elif OC2_CONFIGURATION == OC2_TOGGLE_ON_COMPARE_MATCH
            SET_BIT(local_TCCR2, COM20);
            CLR_BIT(local_TCCR2, COM21);
        #elif OC2_CONFIGURATION == OC2_CLEAR_ON_COMPARE_MATCH
            CLR_BIT(local_TCCR2, COM20);
            SET_BIT(local_TCCR2, COM21);
        #elif OC2_CONFIGURATION == OC2_SET_ON_COMPARE_MATCH
            SET_BIT(local_TCCR2, COM20);
            SET_BIT(local_TCCR2, COM21);
        #else
            #error "INVALID OC2 PIN CONFIGURATION"
        #endif

    #elif TIMER2_MODE == TIMER2_MODE_FAST_PWM
        SET_BIT(local_TCCR2, WGM20);
        SET_BIT(local_TCCR2, WGM21);
        // Set OC2 pin configuration - FAST PWM Mode
        #if OC2_CONFIGURATION == OC2_DISCONNECTED
            CLR_BIT(local_TCCR2, COM20);
            CLR_BIT(local_TCCR2, COM21);
        #elif OC2_CONFIGURATION == OC2_CLEAR_ON_COMPARE_MATCH
            CLR_BIT(local_TCCR2, COM20);
            SET_BIT(local_TCCR2, COM21);
        #elif OC2_CONFIGURATION == OC2_SET_ON_COMPARE_MATCH
            SET_BIT(local_TCCR2, COM20);
            SET_BIT(local_TCCR2, COM21);
        #else
            #error "INVALID OC2 PIN CONFIGURATION"
        #endif
        
    #else
        #error "INVALID TIMER2 MODE!"
    #endif

    TCCR2 = local_TCCR2;

    #if TIMER2_ASYNC_MODE == ENABLE
        while (GET_BIT(ASSR, TCR2UB)); // Wait for TCCR2 to be updated
    #endif

    TIFR |= (1 << TOV2) | (1 << OCF2); // Clear TIMER2 overflow and compare match flags

    // Set TIMER2 overflow interrupt
    #if TIMER2_OVERFLOW_INTERRUPT == ENABLE
        SET_BIT(TIMSK, TOIE2); // Enable TIMER2 overflow interrupt
    #elif TIMER2_OVERFLOW_INTERRUPT == DISABLE
        CLR_BIT(TIMSK, TOIE2); // Disable TIMER2 overflow interrupt
    #else
        #error "INVALID TIMER2 OVERFLOW INTERRUPT CONFIGURATION!"
    #endif

    // Set TIMER2 compare match interrupt
    #if TIMER2_COMPARE_MATCH_INTERRUPT == ENABLE
        SET_BIT(TIMSK, OCIE2); // Enable TIMER2 output compare match interrupt
    #elif TIMER2_COMPARE_MATCH_INTERRUPT == DISABLE
        CLR_BIT(TIMSK, OCIE2); // Disable TIMER2 output compare match interrupt
    #else
        #error "INVALID TIMER2 COMPARE MATCH INTERRUPT CONFIGURATION!"
    #endif
    

    // Enable global interrupt
    SET_BIT(SREG, 7);
}

void TIMER2_voidSetPreload(uint8 timer_preload)
{
    #if TIMER2_ASYNC_MODE == ENABLE
        while (GET_BIT(ASSR, TCN2UB)); // Wait for TCNT2 to be updated
        TCNT2 = timer_preload;
        while (GET_BIT(ASSR, TCN2UB)); // Wait for TCNT2 to be updated
    #else
        TCNT2 = timer_preload;
    #endif
        
}

void TIMER2_voidSetCTC(uint8 value)
{
    #if TIMER2_ASYNC_MODE == ENABLE
        while (GET_BIT(ASSR, OCR2UB)); // Wait for OCR2 to be updated
        OCR2 = value;
        while (GET_BIT(ASSR, OCR2UB)); // Wait for OCR2 to be updated
    #elif TIMER2_ASYNC_MODE == DISABLE
        OCR2 = value;
    #endif
}

TIMER_errorStatus TIMER2_enumGetTimerCounterValue(uint8 *timer_preload)
{
    TIMER_errorStatus status = TIMER_OK;

    if (timer_preload != NULL)
        *timer_preload = TCNT2;
    else
        status = TIMER_NULL_POINTER;

    return status;
}

void TIMER2_voidStopTimer(void)
{
    CLR_BIT(TCCR2, CS20);
    CLR_BIT(TCCR2, CS21);
    CLR_BIT(TCCR2, CS22);
}



TIMER_errorStatus TIMER_enumSetCallBack(void (*ptr)(void), uint8 timer_id)
{
    TIMER_errorStatus status = TIMER_OK;

    if (ptr != NULL)
        if (timer_id >= TIMER2_CTC_ID && timer_id <= TIMER0_OVF_ID)
            callBacks[timer_id] = ptr;
        else
            status = TIMER_INVALID_NUMBER;
    else
        status = TIMER_NULL_POINTER;

    return status;
}



// TIMER2 output compare match ISR
void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
    if (callBacks[TIMER2_CTC_ID] != NULL)
    {
        callBacks[TIMER2_CTC_ID]();
    }
}

// TIMER2 overflow ISR
void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
    if (callBacks[TIMER2_OVF_ID] != NULL)
    {
        callBacks[TIMER2_OVF_ID]();
    }
}

// TIMER1 capture event ISR
void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
    if (callBacks[TIMER1_ICU_ID] != NULL)
    {
        callBacks[TIMER1_ICU_ID]();
    }
}

// TIMER1 output compare match A ISR
void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
    if (callBacks[TIMER1_CTC_A_ID] != NULL)
    {
        callBacks[TIMER1_CTC_A_ID]();
    }
}

// TIMER1 output compare match B ISR
void __vector_8(void) __attribute__((signal));
void __vector_8(void)
{
    if (callBacks[TIMER1_CTC_B_ID] != NULL)
    {
        callBacks[TIMER1_CTC_B_ID]();
    }
}

// TIMER1 overflow ISR
void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
    if (callBacks[TIMER1_OVF_ID] != NULL)
    {
        callBacks[TIMER1_OVF_ID]();
    }
}

// TIMER0 output compare match ISR
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
    if (callBacks[TIMER0_CTC_ID] != NULL)
    {
        callBacks[TIMER0_CTC_ID]();
    }
}

// TIMER0 overflow ISR
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
    if (callBacks[TIMER0_OVF_ID] != NULL)
    {
        callBacks[TIMER0_OVF_ID]();
    }
}
