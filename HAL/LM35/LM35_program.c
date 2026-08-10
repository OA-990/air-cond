/*
 * LM35_program.c
 * Layer :  HAL
 * SWC	 :  LM35
*/

#include "../../LIB/TYPES.h"
#include "LM35_interface.h"
#include "../../MCAL/ADC/ADC_interface.h"

float32 LM35_ReadTemp()
{
	//read volt from : ADC_ConvertData
	//convert volt to temp (according to temp sensor) (LM35 is 10mV per degree Celsius)
	float32 temp = ADC_ConvertData() / 10.0f;
	return temp;
}











