/*
 * CLCD_config.h
 *
 *  Created on: Oct 28, 2026
 *      Author: Hamdi
 */

#ifndef HAL_CLCD_CLCD_CONFIG_H_
#define HAL_CLCD_CLCD_CONFIG_H_

#define CLCD_ROWS 2
#define CLCD_COLUMNS 16

#define CURSOR_OFF 0
#define CURSOR_ON 1

#define CURSOR_NO_BLINK 0
#define CUSRSOR_BLINK 1

#define DISPLAY_OFF 0
#define DISPLAY_ON 1

#define CLCD_MODE 4

#define CLCD_DATA_PORT DIO_PORTA

#define CLCD_RS_PORT DIO_PORTB
#define CLCD_RS_PIN DIO_PIN0

#define CLCD_RW_PORT DIO_PORTB
#define CLCD_RW_PIN DIO_PIN1

#define CLCD_EN_PORT DIO_PORTB
#define CLCD_EN_PIN DIO_PIN2

#endif /* HAL_CLCD_CLCD_CONFIG_H_ */
