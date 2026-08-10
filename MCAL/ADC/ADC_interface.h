/*
 * ADC_interface.h
 * Layer :  MCAL
 * SWC	 :  ADC
*/



#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

//pins definition
//(in ADMUX)
#define	REFS1 	7
#define REFS0 	6
#define ADLAR	5

//(in ADCSRA)
#define ADEN 	7
#define ADIF 	4
#define ADIE 	3
#define ADATE	5
#define ADPS0   0
#define ADPS1   1
#define ADPS2   2
#define ADSC    6

//voltage reference choices
#define ADC_VREF_EXTERNAL	0  // AREF (Internal turned off)
#define ADC_VREF_AVCC		1  // AVCC
#define ADC_VREF_INTERNAL	3  // Internal 2.56V

//alignment
#define ADC_ALIGN_LEFT	1
#define ADC_ALIGN_RIGHT	0

//channels
//single mode
#define ADC_CH0			0x00
#define ADC_CH1			0x01
#define ADC_CH2			0x02
#define ADC_CH3			0x03
#define ADC_CH4			0x04
#define ADC_CH5			0x05
#define ADC_CH6			0x06
#define ADC_CH7			0x07
//differential (MUX 0-4)
#define ADC_CH0_0_10x	0x08
#define ADC_CH0_0_200x	0x09
#define ADC_CH0_1_1x	0x0A
// ... ...

//prescaler not needed here

//conversion mode (ADATE on ADCSRA)
#define ADC_CONV_MODE_SINGLE		0
#define ADC_CONV_MODE_CONTINUOUS	1

//read mode (value for ADIE pin in ADCSRA reg)
#define ADC_INT		1
#define ADC_POLL	0

//functions prototypes
void ADC_Init();
void ADC_StartConversion();
uint16 ADC_ReadData();
float32 ADC_ConvertData();


#endif
