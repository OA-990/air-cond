/*
 * DIO_program.c
 * Layer :  MCAL
 * SWC	 :  DIO
*/


//libraries
#include "../../LIB/TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"


void DIO_voidSetPinDirection	(uint8 port, uint8 pin, uint8 direction)
{
	if(direction == DIO_PIN_OUTPUT)
	{
		//check port & set specific pin to 1
		switch(port)
		{
		case DIO_PORTA : SET_BIT(DDRA, pin); break;
		case DIO_PORTB : SET_BIT(DDRB, pin); break;
		case DIO_PORTC : SET_BIT(DDRC, pin); break;
		case DIO_PORTD : SET_BIT(DDRD, pin); break;
		}
	}
	
	else if(direction == DIO_PIN_INPUT)
	{
		switch(port)
		{
		case DIO_PORTA : CLR_BIT(DDRA, pin); break;
		case DIO_PORTB : CLR_BIT(DDRB, pin); break;
		case DIO_PORTC : CLR_BIT(DDRC, pin); break;
		case DIO_PORTD : CLR_BIT(DDRD, pin); break;
		}
	}

	else if(direction == DIO_PIN_INPUT_PULLUP)
	{
		switch(port)
		{
		case DIO_PORTA : CLR_BIT(DDRA, pin); SET_BIT(PORTA, pin); break;
		case DIO_PORTB : CLR_BIT(DDRB, pin); SET_BIT(PORTB, pin); break;
		case DIO_PORTC : CLR_BIT(DDRC, pin); SET_BIT(PORTC, pin); break;
		case DIO_PORTD : CLR_BIT(DDRD, pin); SET_BIT(PORTD, pin); break;
		}
	}
}
//------------------------------------------------------------------------------


void DIO_voidSetPinValue	(uint8 port, uint8 pin, uint8 value)
{
	if(value == DIO_PIN_HIGH)
	{
		switch(port)
		{
		case DIO_PORTA : SET_BIT(PORTA, pin); break;
		case DIO_PORTB : SET_BIT(PORTB, pin); break;
		case DIO_PORTC : SET_BIT(PORTC, pin); break;
		case DIO_PORTD : SET_BIT(PORTD, pin); break;
		}
	}
	
	else if(value == DIO_PIN_LOW)
	{
		switch(port)
		{
		case DIO_PORTA : CLR_BIT(PORTA, pin); break;
		case DIO_PORTB : CLR_BIT(PORTB, pin); break;
		case DIO_PORTC : CLR_BIT(PORTC, pin); break;
		case DIO_PORTD : CLR_BIT(PORTD, pin); break;
		}
	}
}
//------------------------------------------------------------------------------


uint8 DIO_voidGetPinValue		(uint8 port, uint8 pin)
{
	uint8 data = 0;
	switch(port)
	{//can return here or use local variable
		case DIO_PORTA : data = GET_BIT(PINA, pin); break;
		case DIO_PORTB : data = GET_BIT(PINB, pin); break;
		case DIO_PORTC : data = GET_BIT(PINC, pin); break;
		case DIO_PORTD : data = GET_BIT(PIND, pin); break;
	}
	return data;
}
//------------------------------------------------------------------------------


void DIO_voidTogglePinValue	(uint8 port, uint8 pin)
{
	switch(port)
		{
		case DIO_PORTA : TOG_BIT(PORTA, pin); break;
		case DIO_PORTB : TOG_BIT(PORTB, pin); break;
		case DIO_PORTC : TOG_BIT(PORTC, pin); break;
		case DIO_PORTD : TOG_BIT(PORTD, pin); break;
		}
}
//------------------------------------------------------------------------------


void DIO_voidSetPortDirection	(uint8 port, uint8 direction)
{
	switch(port)
	{
		case DIO_PORTA : DDRA = direction; break;
		case DIO_PORTB : DDRB = direction; break;
		case DIO_PORTC : DDRC = direction; break;
		case DIO_PORTD : DDRD = direction; break;
	}
}
//------------------------------------------------------------------------------


void DIO_voidSetPortValue		(uint8 port, uint8 value)
{
	switch(port)
	{
		case DIO_PORTA : PORTA = value; break;
		case DIO_PORTB : PORTB = value; break;
		case DIO_PORTC : PORTC = value; break;
		case DIO_PORTD : PORTD = value; break;
	}
}
//------------------------------------------------------------------------------


uint8 DIO_voidGetPortValue		(uint8 port)
{
//port reg value = whole pin reg value
//(because we can only get a value that is not from us, in case of an INPUT
	uint8 data = 0;
	switch(port)
	{
		case DIO_PORTA : data = PINA; break;
		case DIO_PORTB : data = PINB; break;
		case DIO_PORTC : data = PINC; break;
		case DIO_PORTD : data = PIND; break;
	}
	return data;
}
//------------------------------------------------------------------------------


void DIO_voidTogglePortValue	(uint8 port)
{
	switch(port)
	{
		case DIO_PORTA : PORTA = ~PORTA; break;
		case DIO_PORTB : PORTB = ~PORTB; break;
		case DIO_PORTC : PORTC = ~PORTC; break;
		case DIO_PORTD : PORTD = ~PORTD; break;
	}
}



