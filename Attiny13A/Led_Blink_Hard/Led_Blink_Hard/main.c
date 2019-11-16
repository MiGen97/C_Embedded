/*
 * Led_Blink_Hard.c
 *
 * Created: 11/16/2019 3:57:57 PM
 * Author : mihail_eugen.pascu
 */ 

#define PORTB_T (*((unsigned int*)0x38))
#define DDRB_T  (*((unsigned int*)0x37))

#define PB4_T    (1u<<4)

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	// initialize pin 4 (ATtiny leg 3) as an output.
	DDRB_T |= PB4_T;    //configure PB4 as output
	
    /* Replace with your application code */
    while (1) 
    {
		PORTB_T |= PB4_T;   //drive the PB4 to HIGH
		_delay_ms(1000);             // wait for a second
		PORTB_T &= ~(PB4_T);    // turn the LED off by making the voltage LOW
		_delay_ms(1000);             // wait for a second
    }
}