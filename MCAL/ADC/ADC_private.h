/*
 * ADC_private.h
 * Layer :  MCAL
 * SWC	 :  ADC
*/


#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

#include "../../LIB/TYPES.h"

//registers definition
#define ADMUX	*((volatile uint8 *) 0x27)
#define ADCSRA	*((volatile uint8 *) 0x26)
#define ADCL	*((volatile uint8 *) 0x24)
#define ADCH	*((volatile uint8 *) 0x25)


#endif
