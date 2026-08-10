/*
 * LCD_program.c
 * Layer :  HAL
 * SWC	 :  LCD
*/



//libraries
#include "../../LIB/TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include <util/delay.h>
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"
#include "../../MCAL/DIO/DIO_interface.h"



void LCD_voidInit	()
{
#if BIT_MODE == 4
		/*old code format
		// Wait more than 30ms
		_delay_ms(50);
		
		// Set control pins as output
		DIO_SetPinDirection(LCD_CONTROL_PORT, LCD_RS, OUTPUT);
		DIO_SetPinDirection(LCD_CONTROL_PORT, LCD_RW, OUTPUT);
		DIO_SetPinDirection(LCD_CONTROL_PORT, LCD_EN, OUTPUT);
		
		// Set data pins (D4-D7) as output
		for(uint8 pin = START_PIN; pin <= END_PIN; pin++)
		{
		    DIO_SetPinDirection(LCD_DATA_PORT, pin, OUTPUT);
		}
		
		//wait for more than 39us
		_delay_us(50);

		//display control
		LCD_voidSendCommand(LCD_SET_MODE_4_BIT);		//set bit mode, line, and font size
		LCD_voidSendCommand(LCD_DisplayOn_CursorOn_BlinkOn);	//set display/cursor/blink to on/off
		//LCD_voidSendCommand(LCD_ReturnHome);			//put cursor on the first position on the first line
		
		//wait for more than 39us
		_delay_us(50);
		
		//display clear
		LCD_voidClearScreen();
		
		//wait for more than 1.53ms
		_delay_ms(2);
		
		//entry mode
		LCD_voidSendCommand(LCD_EntryMode); */
	

#else

		//wait more than 30ms
		_delay_ms(50);
		
		//function set: set all pins to output (because we present on the screen)
		DIO_voidSetPortDirection	(LCD_DATA_PORT, DIO_PIN_OUTPUT);
		DIO_voidSetPinDirection		(LCD_CONTROL_PORT, LCD_RS, DIO_PIN_OUTPUT);
		DIO_voidSetPinDirection		(LCD_CONTROL_PORT, LCD_RW, DIO_PIN_OUTPUT);
		DIO_voidSetPinDirection		(LCD_CONTROL_PORT, LCD_EN, DIO_PIN_OUTPUT);
		
		//wait for more than 39us
		_delay_us(50);

		//display control
		LCD_voidSendCommand(LCD_SET_MODE_8_BIT);		//set bit mode, line, and font size
		LCD_voidSendCommand(LCD_DisplayOn_CursorOn_BlinkOn);	//set display/cursor/blink to on/off
		//LCD_voidSendCommand(LCD_ReturnHome);			//put cursor on the first position on the first line
		
		//wait for more than 39us
		_delay_us(50);
		
		//display clear
		LCD_voidClearScreen();
		
		//wait for more than 1.53ms
		_delay_ms(2);
		
		//entry mode
		LCD_voidSendCommand(LCD_EntryMode);
		
		
		
		/*
		// 1- must wait more than 30 ms before any action (VDD rises to 4.5 v)
		_delay_ms(50);
		// All Pins as OutPut pins
		DIO_enumSetPortDirection ( CLCD_DATA_PORT    , DIO_PORT_OUTPUT           );
		DIO_enumSetPinDirection  ( CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_OUTPUT  );
		DIO_enumSetPinDirection  ( CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_OUTPUT  );
		DIO_enumSetPinDirection  ( CLCD_CONTROL_PORT , CLCD_EN , DIO_PIN_OUTPUT  );
		//Return cursor to the first position on the first line
		CLCD_voidSendCommand(lcd_Home);
		_delay_ms(1);
		//FUNCTION SET Command : 2 lines , 5*8 font size
		CLCD_voidSendCommand( EIGHT_BITS ); // 8 Bit Mode ==> 0x38
		_delay_ms(1); // wait more than 39 Ms
		//DISPLAY & Cursor (ON / OFF) Control
		CLCD_voidSendCommand( lcd_DisplayOn_CursorOff );
		_delay_ms(1);
		//DISPLAY CLEAR
		CLCD_voidClearScreen();
		//ENTRY MODE  SET
		CLCD_voidSendCommand( lcd_EntryMode );
		_delay_ms(1);
		*/
#endif
}
//---------------------------------------------------------------------------------------------------------------------------


void LCD_voidSendData	(uint8 data)
{
	#if BIT_MODE == 4
	{
	}
	
	#else
	{
	//send value/data in the specified port, the whole port (8 bits) - no specific registers or pins
	//we put data then send it (make sense)
	//DIO_setPortValue(LCD_DATA_PORT, Copy_u8Data);
	DIO_voidSetPortValue	(LCD_DATA_PORT, data);
	
	//prp for sending data: rs = 1, rw = 0, enable falling endge
	//DIO_SetPinValue()
	DIO_voidSetPinValue	(LCD_CONTROL_PORT, LCD_RS, DIO_PIN_HIGH);
	DIO_voidSetPinValue	(LCD_CONTROL_PORT, LCD_RW, DIO_PIN_LOW);
	LCD_voidSendFallingEdge();
	}
	
	#endif
	_delay_ms(1);
}
//---------------------------------------------------------------------------------------------------------------------------



void LCD_voidSendCommand	(uint8 command)
{
	#if BIT_MODE == 4
	{
	}
	
	#else
	{
	DIO_voidSetPortValue(LCD_DATA_PORT, command);
	DIO_voidSetPinValue	(LCD_CONTROL_PORT, LCD_RS, DIO_PIN_LOW);
	DIO_voidSetPinValue	(LCD_CONTROL_PORT, LCD_RW, DIO_PIN_LOW);
	LCD_voidSendFallingEdge	();
	}
	
	#endif
	_delay_ms(1);
}
//---------------------------------------------------------------------------------------------------------------------------


void LCD_voidSendString		(const uint8 *ptrString)
{
	uint8 iterator = 0;
	while(ptrString[iterator] != '\0')
	{
		LCD_voidSendData(ptrString[iterator]);
		iterator++;
	}
}
//---------------------------------------------------------------------------------------------------------------------------


void LCD_voidSendChar		(const uint8 character) //just a Wrapper function
{
	LCD_voidSendData(character);
}
//---------------------------------------------------------------------------------------------------------------------------



static void LCD_voidSendFallingEdge()
{
	DIO_voidSetPinValue	(LCD_CONTROL_PORT, LCD_EN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue	(LCD_CONTROL_PORT, LCD_EN, DIO_PIN_LOW);
	_delay_ms(1);
}
//---------------------------------------------------------------------------------------------------------------------------


void LCD_voidSetCursor		(uint8 row, uint8 col)
{
	uint8 address;
	if(row == 0)		address = LCD_SetCursor + col;		// 0x80 + col (cols 0-15)
	else if(row == 1)	address = LCD_SetCursor + 0x40 + col;	// 0xC0 + col (cols 0-15)
 	else return;							// Invalid row (only 2 rows available)
 	
   	 LCD_voidSendCommand(address);
   	 
   	/* switch(row)
    	{
        case 0: 
            // address = 0x80 + 0x00 + col
            address = LCD_SetCursor + LCD_LINE1_OFFSET + col; 
            break;
        case 1: 
            // address = 0x80 + 0x40 + col
            address = LCD_SetCursor + LCD_LINE2_OFFSET + col; 
            break;
        default: 
            return;
   	 }*/
}
/*
┌──────────────────────────────────────────────────────────┐
│                    16x2 LCD Memory Map                   │
├──────────────────────────────────────────────────────────┤
│                                                          │
│  Row 0 (Line 1):  0x80  0x81  0x82 ... 0x8F              │
│                   Col 0  Col 1  Col 2 ... Col 15         │
│                                                          │
│  Row 1 (Line 2):  0xC0  0xC1  0xC2 ... 0xCF              │
│                   Col 0  Col 1  Col 2 ... Col 15         │
│                                                          │
└──────────────────────────────────────────────────────────┘
DDRAM Address:     0x00   0x01   0x02  ...  0x0F     ← Line 1 (Row 0)
                    ↓      ↓      ↓          ↓
LCD Position:     Col 0  Col 1  Col 2 ...  Col 15

DDRAM Address:     0x40   0x41   0x42  ...  0x4F     ← Line 2 (Row 1)
                    ↓      ↓      ↓          ↓
LCD Position:     Col 0  Col 1  Col 2 ...  Col 15

// address = 0x80 + 0x00 + col
*///---------------------------------------------------------------------------------------------------------------------------


void LCD_voidClearScreen	()
{
	LCD_voidSendCommand(LCD_ClearScreen);
	_delay_ms(5);
}
//---------------------------------------------------------------------------------------------------------------------------


void LCD_voidSendNumber(uint16 number)
{
	uint16 reversed = 1; //flag for end/mask

	if(number == 0)
	{
		LCD_voidSendData('0');
	}

	while(number != 0)
	{
		reversed = (reversed * 10) + (number % 10);
		number /= 10;
	}

	while(reversed != 1)
	{
		LCD_voidSendData((reversed % 10) + 48); //48 convert char to int, same as + '0'
		reversed /= 10;
	}
}
//---------------------------------------------------------------------------------------------------------------------------


void LCD_voidSendFloat	(float32 value)
{
    if (value < 0.0f) {
        LCD_voidSendData('-');
        value = -value;
    }

    uint16 int_part = (uint16)value;
    uint16 frac_part = (uint16)((value - (float32)int_part) * 10.0f);

    LCD_voidSendNumber(int_part);
    LCD_voidSendData('.');
    LCD_voidSendNumber(frac_part);
}







