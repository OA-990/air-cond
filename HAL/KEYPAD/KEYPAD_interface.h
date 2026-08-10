/*
 * KEYPAD_interface.h
 * Layer :  HAL
 * SWC	 :  KEYPAD
*/


#ifndef HAL_KEYPAD_KEYPAD_H_
#define HAL_KEYPAD_KEYPAD_H_

#include "../../LIB/TYPES.h"

#define NO_KEY 0xFF
//size
#define KEYPAD_ROWS	4
#define KEYPAD_COLS	4
//port used in mcu
#define KEYPAD_ROW_PORT	DIO_PORTC
#define KEYPAD_COL_PORT	DIO_PORTC
//first pins in mcu
#define KEYPAD_ROW_PIN 0
#define KEYPAD_COL_PIN 4


void KEYPAD_Init();
uint8 KEYPAD_GetPressedKey();

#endif /* HAL_KEYPAD_KEYPAD_H_ */
