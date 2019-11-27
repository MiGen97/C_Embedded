/*
 * InterruptVector.c
 *
 *	This script is used to understand how to use the InteruptVector
 *	so, when an interrupt appear, run a specific sequence of code
 *
 *	The used interrupt it TimerOverflow (TIM0_OVF) from address at 0x0003 with prescaler of the clkI/O at 1024
 *	When the timer gets an overflow it toggle an LED placed on PB4 pin
 * 
 *	Application description:
 *		The LED placed on PB4 pin will be toggle only when a TimerOverflow interrupt is ocuring.
 *
 * Created: 11/27/2019 2:40:29 PM
 * Author : MihailPascu
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>


//ISR(TIM0_OVF_vect) {
	//PORTB ^=1u<<4; //toggle the LED
//}


void __vector_3 (void) __attribute__ ((signal, used));

void __vector_3 (void)  {
	PORTB ^= (1u<<4u);
}

int main(void)
{
	//cli(); //set bit 7(I) in SREG to 0 (disable global interrupts)
	SREG &= ~(1u<<7u);
	
	//Configure pin PB4 and PB3 as output
	DDRB |= (1u<<4u);		//set the PB4 pin as output
	PORTB &= ~(1u<<4u);	//set the PB4 pin to LOW
	
	

	//Enable the Timer/Counter with prescaler
	//Prescaler
		//keep the prescaler in reset until the needed modifications are made
		GTCCR |= (1u<<7u);
	
		//Select the clock source at clkI/O divided by 1024 from prescaler
		TCCR0B |= (1u<<2u)|(1u);			//set CS0 bits to one
		
		//stop the prescaler reset
		GTCCR &= ~(1u<<7u);
		
	//Enable the timer overflow interrupt
	//Timer
		TIMSK0 |= (1u<<1u);			//set TOIE0 to one
	
	
	//sei(); //set bit 7(I) in SREG to 1 (enable global interrupts)
	SREG |= 1u<<7u;
	
	while(1){
	} 
}

