/*
 * GPIO_Input.c
 *
 * Created: 11/16/2019 5:05:39 PM
 * Author : mihail_eugen.pascu
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define PORTB_T (*((unsigned int*)0x38))
#define DDRB_T  (*((unsigned int*)0x37))
#define PINB_T  (*((unsigned int*)0x36))

#define PB3_T	1u<<3
#define PB4_T	1u<<4


int main(void)
{
	//Setting the PB3 pin of ATtiny13A as an INPUT
	PORTB_T |= PB3_T;
	DDRB_T &= ~PB3_T;
	
	//Setting the PB4 pin of ATtiny13A as an OUTPUT
	DDRB_T &= ~PB4_T;
	
    while (1) 
    {
		if(PINB_T>>3 & 1u){
			PORTB_T |= PB4_T;
		}else{
			PORTB_T &= ~PB4_T;
		}
		_delay_ms(1000);
    }
}

