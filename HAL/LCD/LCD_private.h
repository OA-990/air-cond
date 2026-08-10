/*
 * LCD_private.h
 * Layer :  HAL
 * SWC	 :  LCD
*/



#ifndef _LCD_PRIVATE_H_
#define _LCD_PRIVATE_H_

/*registers
vss ->  gnd
vdd ->  pwr
v0  ->  pwr for contrast (potentiometer)
E   -> 	enable
rs  ->  (0 cmd/ 1 data)
rw  ->  gnd low/high
8 datapins (7-13)
A : anode pin
K : cathode pin
*/

static void LCD_voidSendFallingEdge	();

#endif
