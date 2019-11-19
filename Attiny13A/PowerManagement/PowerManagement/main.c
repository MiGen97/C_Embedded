/*
 * PowerManagement.c
 *
 * Created: 11/19/2019 9:14:31 PM
 * Author : mihail_eugen.pascu
 * Code Logic:
 *	-use button connected to PIN3 as an input to turn on an LED connected to PIN4 and to put the ATtiny13A to sleep
 *  -use INT0 pin (PIN1) to sense low level interrupt to wake up the ATtiny13A from sleep and to turn off the LED
 *  -When the LED is ON, the ATtiny13A is on Power-Down mode
 *  -When the LED is OFF, the ATtiny13A is in Active mode
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	//Enable pin3 as Input
	DDRB&=~(1<<3);
	PORTB|=1<<3;
	
	//Internal pull-up activated
	MCUCR&=~(1<<6);
	
	//Set the pin4 as Output
	DDRB|=1<<4;

	
	//Set enable the Global Interrupt (I bit)
	SREG|=1<<7;
	//Enable INT0 Interrupt
	GIMSK|=1<<6; //Set INT0 to 1
	//Enable the rising edge of INT0 to generate an interrupt request
	MCUCR&=~(1<<1); //Set ISC01 to 1
	MCUCR&=~1;	 //Set ISC00 to 1
	//MCUCR=0xFC; it work also with hex numbers
	
	
    while (1) 
    {
		if(PINB&=1<<3){
			//going to sleep
			//but first turn the LED from pin4 ON
			
			PORTB|=1<<4;
			
			//Set Sleep Enable bit to "TRUE"
			MCUCR|=1<<5;		//SE
			
			//Set the sleep mode to "Power-Down" with the two Sleep Mode Select Bits
			MCUCR|=1<<4;		//SM1
			MCUCR&=~(1<<3);		//SM2
			
			asm("sleep");
			
		}else{
			//turn off the LED connected to PIN4
			PORTB&=~(1<<4);
		}
    }
}

