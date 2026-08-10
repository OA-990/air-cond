/*
 * DIO_private.h
 * Layer :  MCAL
 * SWC	 :  DIO
*/


#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H

//register definition

//Group/Port A
#define DDRA  *((volatile uint8 *) 0x3A)
#define PORTA *((volatile uint8 *) 0x3B)
#define PINA  *((volatile uint8 *) 0x39)

//Group/Port B
#define DDRB  *((volatile uint8 *) 0x37)
#define PORTB *((volatile uint8 *) 0x38)
#define PINB  *((volatile uint8 *) 0x36)

//Group/Port C
#define DDRC  *((volatile uint8 *) 0x34)
#define PORTC *((volatile uint8 *) 0x35)
#define PINC  *((volatile uint8 *) 0x33)

//Group/Port D
#define DDRD  *((volatile uint8 *) 0x31)
#define PORTD *((volatile uint8 *) 0x32)
#define PIND  *((volatile uint8 *) 0x30)

#endif
