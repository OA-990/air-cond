/*
 * LCD_interface.h
 * Layer :  HAL
 * SWC	 :  LCD
*/


#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#include "../../LIB/TYPES.h"
/* command functions
8 bit mode can't set individual bits */
//#define LCD_DISPLAY_ON            0x0C  // Display ON, cursor OFF
//#define LCD_DISPLAY_ON_CURSOR     0x0E  // Display ON, cursor ON

#define LCD_SET_MODE_8_BIT				0x38  	// 8-bit, 2 lines, 5x8 font
#define LCD_SET_MODE_4_BIT				0x28  	// 4-bit, 2 lines, 5x8 font
#define LCD_DisplayOn_CursorOn_BlinkOn	0x0F
#define LCD_ClearScreen					0x01
#define LCD_EntryMode					0x06	//shift cursor from left to right
#define LCD_SetCursor                 	0x80	//must have for multi-line 0x80+address
#define LCD_ReturnHome                  0x02    //return cursor to first position on first line (faster than SetCursor)

/*
#define lcd_DisplayOn_CursorOff       0x0c          // display on, cursor off, don't blink character 
#define lcd_DisplayOn_CursorOn        0x0e          // display on, cursor on, don't blink character 
#define lcd_DisplayOff_CursorOff      0x08          // turn display off
#define lcd_CGRAM                     0x40          // the first Place/Address at CGRAM
#define lcd_FunctionReset             0x30          // reset the LCD
*/


//functions prototypes
void LCD_voidInit			();
void LCD_voidSendCommand	(uint8 command);
void LCD_voidSendData		(uint8 data);
void LCD_voidSendString		(const uint8 *ptrString);
void LCD_voidSendChar		(const uint8 character);
void LCD_voidClearScreen	();
void LCD_voidSetCursor		(uint8 row, uint8 col);
void LCD_voidSendNumber		(uint16 number);
void LCD_voidSendFloat		(float32 value);


#endif
