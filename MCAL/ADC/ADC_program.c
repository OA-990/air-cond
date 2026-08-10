/*
 * ADC_program.c
 * Layer :  MCAL
 * SWC	 :  ADC
*/

#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_interface.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/TYPES.h"
#include <avr/interrupt.h>

// Global variables for interrupt mode
#if ADC_READ_MODE == ADC_INT
    volatile uint16 adc_result = 0;
    volatile uint8 adc_complete = 0;
#endif


void ADC_Init()
{	//volt ref set/clear according to choice -> channel
	//-> align -> prescalar -> adc enable -> conv mode -> interrupt

	//voltage
#if ADC_VREF == ADC_VREF_AVCC
	SET_BIT(ADMUX, 6);  //REFS0 = 1
	CLR_BIT(ADMUX, 7);  //REFS1 = 0
#elif ADC_VREF == ADC_VREF_EXTERNAL
	CLR_BIT(ADMUX, 6);  //REFS0 = 0
	CLR_BIT(ADMUX, 7);  //REFS1 = 0
#elif ADC_VREF == ADC_VREF_INTERNAL
	SET_BIT(ADMUX, 6);  //REFS0 = 1
	SET_BIT(ADMUX, 7);  //REFS1 = 1
#endif

	//channel
	//clear MUX bits(0-4)
	ADMUX = ADMUX & ~(0x1F);
	//ADC channels from 0-7, having max five first bits set, 0x1F == 0001 1111
	ADMUX = ADMUX | ADC_CHANNEL_MODE;

	//alignment
#if ADC_ALIGN == ADC_ALIGN_LEFT
	SET_BIT(ADMUX, ADLAR);
	//uint16 adc_value = ADC; //read ADCL & ADCH is read automatically
	//if right ADMUX = CLR_BIT(ADMUX, 5) : no need to use because it's the default
#endif


	//prescaler
	//expand presclaer: (ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))
#if ADC_PRESCALER == 128
	SET_BIT(ADCSRA, ADPS0);
	SET_BIT(ADCSRA, ADPS1);
	SET_BIT(ADCSRA, ADPS2);
#elif ADC_PRESCALER == 64
	CLR_BIT(ADCSRA, ADPS0);
	SET_BIT(ADCSRA, ADPS1);
	SET_BIT(ADCSRA, ADPS2);
// ... other values + error checking in else "Invalid ADC_PRESCALER value!"
#endif

	//adc enable
	SET_BIT(ADCSRA, ADEN);

	//conv mode
#if ADC_CONV_MODE == ADC_CONV_MODE_SINGLE
	CLR_BIT(ADCSRA, ADATE);
#else
	SET_BIT(ADCSRA, ADATE);
#endif

	//interrupt vs polling
#if ADC_READ_MODE == ADC_INT
	SET_BIT(ADCSRA, ADIE);
	//sei(); -> call in main
#else
	//ADIE is 0 by default , or  CLR_BIT(ADCSRA, ADIE);
	//we keep checking adie flag
#endif
}
//------------------------------------------------------------------------------

void ADC_StartConversion()
{
	//adc_complete = 0;
	SET_BIT(ADCSRA, ADSC);
}
//------------------------------------------------------------------------------

uint16 ADC_ReadData()
{
	uint16 adc_value = 0;
#if ADC_READ_MODE == ADC_POLL
	//start conversion
	ADC_StartConversion();
	//wait for conversion: while (!(ADCSRA & (1 << ADIF)));
	while (!GET_BIT(ADCSRA, ADIF));
	//clear flag: ADCSRA |= (1 << ADIF);
	SET_BIT(ADCSRA, ADIF);
	//ADCL+ADCH
	adc_value = ADCL;
	adc_value |= (ADCH << 8);
	//return result: return ADC
	return adc_value;

#elif ADC_READ_MODE == ADC_INT
	//reset global flags
	adc_complete = 0;
	//adc_result = 0;
	//start conversion
	ADC_StartConversion();
	//wait for ISR to finish using flag: while (!adc_complete);
	//Wait for ISR to set the flag (Takes ~100-200 microseconds)
	uint16 timeout = 10000;
	while(!adc_complete && timeout)
	{
		timeout--;
	}
	if(timeout == 0)
	{
		return 0;
	}

	//return adc_result from ISR
	return adc_result;
#else
	return 0;
#endif
}
//------------------------------------------------------------------------------

//EMPTY_INTERRUPT(BADISR_vect);
#if ADC_READ_MODE == ADC_INT
	ISR(ADC_vect)
	{
		adc_result = ADCL;
		adc_result |= (ADCH << 8);
		adc_complete = 1;
	}
#endif
//------------------------------------------------------------------------------

float32 ADC_ConvertData()
{//convert adc value 0-1023 to physical unit (mili-volt)
	//mili voltage = adc value * reference / 1024.0 (ref = 5V = 5000 mV)
	float32 volt = (float32)ADC_ReadData() * 5000.0f / 1024.0f;
	return volt;
}


// Catch any stray/unhandled interrupts and prevent MCU reset

ISR(BADISR_vect)
{
    // Do nothing (or loop) instead of resetting

	// If ADC interrupt was misdirected here, read ADCL/ADCH manually
	    adc_result = ADCL;
	    adc_result |= (ADCH << 8);
	    adc_complete = 1;
}




