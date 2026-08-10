
#include "../LIB/TYPES.h"
#include "../HAL/KEYPAD/KEYPAD_interface.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/LM35/LM35_interface.h"
#include "../MCAL/DIO/DIO_interface.h"
#include <util/delay.h>
#include <avr/wdt.h>
#include <avr/io.h>
#include <avr/interrupt.h>


#define R_LED_PORT	DIO_PORTA
#define R_LED_PIN	DIO_PIN1
#define B_LED_PORT	DIO_PORTA
#define B_LED_PIN	DIO_PIN2
#define FAN_PORT   	DIO_PORTA
#define FAN_PIN		DIO_PIN3
#define BUZ_PORT	DIO_PORTA
#define BUZ_PIN		DIO_PIN4

//LM35 is not defined only connected in hardware
//but we know it will use A0 because ADC channel is set to (ADC_CH0 -> 0x00)

//uint8 overHeat = 0;
float32 target_temp = 0.0;

void overHeatAlarm()
{
	//turn on buzzer -> turn on red light -> alert txt on screen -> set overHeat to 0
	DIO_voidSetPinDirection(BUZ_PORT, BUZ_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinValue (BUZ_PORT, BUZ_PIN, DIO_PIN_HIGH);

	DIO_voidSetPinDirection (R_LED_PORT, R_LED_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinValue 	(R_LED_PORT, R_LED_PIN, DIO_PIN_HIGH);

	LCD_voidClearScreen ();
	LCD_voidSetCursor (0, 0);
	LCD_voidSendString 	("ALERT! Temp Exceeded Threshold!");
	//overHeat = 0;

	_delay_ms(500);
}

void turnOffOverHeatAlarm()
{
    DIO_voidSetPinDirection(BUZ_PORT, BUZ_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinValue(BUZ_PORT, BUZ_PIN, DIO_PIN_LOW);

    DIO_voidSetPinDirection(R_LED_PORT, R_LED_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinValue(R_LED_PORT, R_LED_PIN, DIO_PIN_LOW);
}


float32 readTargetTempFromKeypad()
{
	 uint8 key;
	 uint8 digits[4] = {0}; //two digits & two decimal points
	 uint8 digit_count = 0;
	 float32 temp;

	//reading digits
	 for(uint8 i = 0; i<=3; i++)
	 {
		 while(1)
		 {//wait for a valid key, don't read garbage if user didn't press
			 key = KEYPAD_GetPressedKey();
			 if(key != NO_KEY) break;
			 _delay_ms(5);
		 }

		 //if user didn't want to enter 3rd/4th digits, just fill with zeros
		 if(key == 'C' || key == '=') {
			 while(digit_count < 4) {
				 digits[digit_count++] = 0;
			 }
			 break;
		 }

		 //store digits
		 digits[i] = key - '0'; //convert char to int
		 LCD_voidSendData(key);
		 _delay_ms(10);

		 if(i == 1)
		 {
			 LCD_voidSendChar('.');
		 }

		 digit_count++;
	 }

	//construct the float number
	temp = (digits[0] * 10.0) + digits[1] + (digits[2] / 10.0) + (digits[3] / 100.0);
	return temp;
}


int main()
{
	wdt_disable();

	float32 current_temp = 0;
	float32 hystersis = 1.0;
	uint8 op_mode = 0;
	//uint8 temp_mode = '*';	//* -> C, # -> F (after each temp read) (not shown in lcd)
	uint8 cool_sys = 0;

	LCD_voidInit ();
	KEYPAD_Init();
	sei();
	ADC_Init();



	//prompt to user: choose target temp 20-28 with keypad
	//in second line show user enter
	//store in var
	LCD_voidClearScreen ();
	LCD_voidSetCursor (0, 0);
	LCD_voidSendString	("Target Temp (20.0 - 28.0): ");
	LCD_voidSetCursor (1, 0);
	//read temp from keypad (using get tmep function because keypad returns a char)
	target_temp = readTargetTempFromKeypad();

	//validation
	if(target_temp < 20.0 || target_temp > 28.0)
	{
		LCD_voidClearScreen ();
		LCD_voidSetCursor (0, 0);
		LCD_voidSendString	("Invalid Temp!!");
		LCD_voidSetCursor(1, 0);
		LCD_voidSendString("Rest Program");
		while(1); // halt for ever
	}

	//show on screen
	LCD_voidSendFloat (target_temp);

	//prompt to user: choose operating mode with keypad
	//show in lcd
	//store in var
	LCD_voidClearScreen ();
	LCD_voidSetCursor (0, 0);
	LCD_voidSendString	("Op Mode: ");
	LCD_voidSetCursor (1, 0);
	LCD_voidSendString	("0:OFF 1:MAN 2:AUT");

	//keep scanning until a key is pressed
	while (KEYPAD_GetPressedKey() != NO_KEY) { _delay_ms(10); }
	op_mode = NO_KEY;
	while (op_mode == NO_KEY)
	{
	    op_mode = KEYPAD_GetPressedKey();
	    _delay_ms(10);
	}

	//convert char read to number
	op_mode = op_mode -  '0';


	while(1)
	{
		current_temp = LM35_ReadTemp();

		if(op_mode == 0)
		{
			//cooling system off - nothing works except for temp reading  & lcd
			//show on lcd target & current -> second line: change target
			LCD_voidClearScreen ();
			LCD_voidSetCursor (0, 0);
			LCD_voidSendString	("Cur: ");
			LCD_voidSendFloat (current_temp);
			LCD_voidSetCursor (1, 0);
			LCD_voidSendString	("Target: ");
			LCD_voidSendFloat (target_temp);
			_delay_ms(500);
			//check over heat
			if(current_temp >= target_temp + 5)
			{
				overHeatAlarm();
			}
			else
			{
				turnOffOverHeatAlarm();
			}
			//check for new target temp (using C)
			uint8 key = KEYPAD_GetPressedKey();
			if(key == 'C')
			{
				LCD_voidClearScreen();
				LCD_voidSetCursor(0, 0);
				LCD_voidSendString("New T.Temp: ");
				LCD_voidSetCursor(1, 0);
				target_temp = readTargetTempFromKeypad();
				_delay_ms(20);
			}
		}

		else if(op_mode == 1)
		{
			//manual: show current temp
			//user can change cooling system on/off
			LCD_voidClearScreen ();
			LCD_voidSetCursor (0, 0);
			LCD_voidSendString	("Current Temp: ");
			LCD_voidSendFloat (current_temp);
			LCD_voidSetCursor (1, 0);
			LCD_voidSendString	("Cool: 0.OFF  1.ON: ");
			uint8 key = KEYPAD_GetPressedKey();
			//wait for user to press
			_delay_ms(350);
			if(key == '0')
			{
				//change char to int
				cool_sys = 0;
			}
			else if(key == '1')
			{
				cool_sys = 1;
			}

			//if on -> blue led -> fan
			if(cool_sys)
			{
				//set blue led & fan pins to high
				DIO_voidSetPinDirection (B_LED_PORT, B_LED_PIN, DIO_PIN_OUTPUT);
				DIO_voidSetPinValue 	(B_LED_PORT, B_LED_PIN, DIO_PIN_HIGH);

				DIO_voidSetPinDirection (FAN_PORT, FAN_PIN, DIO_PIN_OUTPUT);
				DIO_voidSetPinValue 	(FAN_PORT, FAN_PIN, DIO_PIN_HIGH);

			}
			else
			{
				DIO_voidSetPinDirection (B_LED_PORT, B_LED_PIN, DIO_PIN_OUTPUT);
				DIO_voidSetPinValue 	(B_LED_PORT, B_LED_PIN, DIO_PIN_LOW);

				DIO_voidSetPinDirection (FAN_PORT, FAN_PIN, DIO_PIN_OUTPUT);
				DIO_voidSetPinValue 	(FAN_PORT, FAN_PIN, DIO_PIN_LOW);

			}
			//check over heat
			if(current_temp >= target_temp + 5)
			{
				overHeatAlarm();
			}
			else
			{
				turnOffOverHeatAlarm();
			}

		}


		else if(op_mode == 2)
		{
			//auto: user does nothing
			//on & off automatically according to hysteresis
			//show current & target
			LCD_voidClearScreen ();
			LCD_voidSetCursor (0, 0);
			LCD_voidSendString	("Current Temp: ");
			LCD_voidSendFloat (current_temp);
			_delay_ms(250);
			//if > hystersis -> blue led -> fan
			if(current_temp >= target_temp + hystersis)
			{
				//set blue led & fan pins to high
				LCD_voidSetCursor (1, 0);
				LCD_voidSendString	("cooling on");
				_delay_ms(250);

				DIO_voidSetPinDirection (B_LED_PORT, B_LED_PIN, DIO_PIN_OUTPUT);
				DIO_voidSetPinValue 	(B_LED_PORT, B_LED_PIN, DIO_PIN_HIGH);
				DIO_voidSetPinDirection (FAN_PORT, FAN_PIN, DIO_PIN_OUTPUT);
				DIO_voidSetPinValue 	(FAN_PORT, FAN_PIN, DIO_PIN_HIGH);
				_delay_ms(200);
			}
			else if(current_temp <= target_temp - hystersis)
			{
				//turn off
				LCD_voidSetCursor (1, 0);
				LCD_voidSendString	("cooling off");
				_delay_ms(250);

				DIO_voidSetPinDirection (B_LED_PORT, B_LED_PIN, DIO_PIN_OUTPUT);
				DIO_voidSetPinValue 	(B_LED_PORT, B_LED_PIN, DIO_PIN_LOW);
				DIO_voidSetPinDirection (FAN_PORT, FAN_PIN, DIO_PIN_OUTPUT);
				DIO_voidSetPinValue 	(FAN_PORT, FAN_PIN, DIO_PIN_LOW);
				_delay_ms(200);
			}
			//check over heat
			if(current_temp >= target_temp + 5)
			{
				overHeatAlarm();
			}
			else
			{
				turnOffOverHeatAlarm();
			}
		}


		else
		{
			LCD_voidClearScreen ();
			LCD_voidSetCursor (0, 0);
			LCD_voidSendString	("ERROR! Invalid Operation Mode!");
		}

	}

	return 0;
}

