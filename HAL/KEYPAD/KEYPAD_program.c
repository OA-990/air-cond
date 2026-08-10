/*
 * KEYPAD_program.c
 * Layer :  HAL
 * SWC	 :  KEYPAD
*/

#include <util/delay.h>
#include "../../LIB/TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "KEYPAD_interface.h"



uint8 keypad[KEYPAD_ROWS][KEYPAD_COLS] =
{
		{'7', '8', '9', '/'},
		{'4', '5', '6', '*'},
		{'1', '2', '3', '-'},
		{'C', '0', '=', '+'}
};



void KEYPAD_Init()
{
	for(uint8 row = KEYPAD_ROW_PIN; row < KEYPAD_ROW_PIN + KEYPAD_ROWS; row++)
	{
		DIO_voidSetPinDirection(KEYPAD_ROW_PORT, row, DIO_PIN_INPUT_PULLUP);
	}
	for(uint8 col = KEYPAD_COL_PIN; col < KEYPAD_COL_PIN + KEYPAD_COLS; col++)
	{
		DIO_voidSetPinDirection(KEYPAD_COL_PORT, col, DIO_PIN_OUTPUT);
		DIO_voidSetPinValue(KEYPAD_COL_PORT, col, DIO_PIN_HIGH);
	}

}


uint8 KEYPAD_GetPressedKey()
{
	uint8 key = NO_KEY;
	for(uint8 col = 0; col < KEYPAD_COLS; col++)
	{
		DIO_voidSetPinValue(KEYPAD_COL_PORT, KEYPAD_COL_PIN + col, DIO_PIN_LOW);
		for(uint8 row = 0; row < KEYPAD_ROWS; row++)
		{
			_delay_ms(20);
			if(DIO_voidGetPinValue(KEYPAD_ROW_PORT, KEYPAD_ROW_PIN + row) == DIO_PIN_LOW)
			{
				key = keypad[row][col];//gets key
				//key = (row << 4) | col;	 //gets binary rep
			}
		}
		DIO_voidSetPinValue(KEYPAD_COL_PORT, KEYPAD_COL_PIN + col, DIO_PIN_HIGH);
	}
	return key;
}






















