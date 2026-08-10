/*
 * DIO_interface.h
 * Layer :  MCAL
 * SWC	 :  DIO
*/


#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H


//PORTs (assigned value, actual ports are accessed using the addresses
//named PORTA, PORTB,...etc
#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

//Port direction
#define DIO_PORT_OUTPUT	0xFF
#define DIO_PORT_INPUT	0

//Port value
#define DIO_PORT_HIGH	0xFF
#define DIO_PORT_LOW	0


//PINs
#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7

//PIN direction
#define DIO_PIN_INPUT			0
#define DIO_PIN_OUTPUT			1
#define DIO_PIN_INPUT_PULLUP	2

//PIN value
#define DIO_PIN_LOW  0
#define DIO_PIN_HIGH 1


//function prototypes
void DIO_voidSetPinDirection	(uint8 port, uint8 pin, uint8 direction);
void DIO_voidSetPinValue		(uint8 port, uint8 pin, uint8 value);
uint8 DIO_voidGetPinValue		(uint8 port, uint8 pin);
void DIO_voidTogglePinValue		(uint8 port, uint8 pin);

void DIO_voidSetPortDirection	(uint8 port, uint8 direction);
void DIO_voidSetPortValue		(uint8 port, uint8 value);
uint8 DIO_voidGetPortValue		(uint8 port);
void DIO_voidTogglePortValue	(uint8 port);


#endif
