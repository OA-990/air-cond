/*
 * ADC_config.h
 * Layer :  MCAL
 * SWC	 :  ADC
*/


#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

//voltage reference : +{EXTERNAL, AVCC, INTERNAL}
#define ADC_VREF ADC_VREF_AVCC

//alignment +(LEFT / RIGHT)
#define ADC_ALIGN	ADC_ALIGN_RIGHT

//adc channel choice (single or differential)
#define ADC_CHANNEL_MODE	ADC_CH0

//adc prescaler values (2, 2, 4, 8, 16, 32, 64, 128)
#define ADC_PRESCALER 128

//conversion mode (single/continuous)
#define ADC_CONV_MODE	ADC_CONV_MODE_SINGLE

//read mode (interrupt/ polling)
#define ADC_READ_MODE	ADC_INT


#endif
