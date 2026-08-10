/*
 * LCD_config.h
 * Layer :  HAL
 * SWC	 :  LCD
*/


#ifndef _LCD_CONFIG_H_
#define _LCD_CONFIG_H_

//bit mode (use 4 or 8 pins)
#define BIT_MODE	8


/*data ports
DIO_PORT(A/B/C/d) */
#define LCD_DATA_PORT	DIO_PORTB


/*control port
rs, rw, en
put in either DIO_PORT(A/B/C/d) */
#define LCD_CONTROL_PORT	DIO_PORTD

//4 bit mode data pins
#define START_PIN	DIO_PIN0
#define END_PIN		DIO_PIN7

//define control regs on specific pins (DIO_PIN0-7)
#define LCD_RS	DIO_PIN0
#define LCD_RW	DIO_PIN1
#define LCD_EN	DIO_PIN2



#endif
