/*
 * WatchDog.c
 *
 * This script is thinket for testing the Watchdog interrupt mode functionality
 * It turns on a LED and goes to sleep
 * When the Watchdog wakes up the CPU, after 8 seconds
 * The LED is turned off and the CPU waits for 2 seconds before going again at sleep
 *
 * Created: 11/21/2019 11:37:39 PM
 * Author : mihail_eugen.pascu
 */ 

#include <avr/io.h>
#include <util/delay.h>

//#define WDTIE   (1<<6)
#define IBIT	(1<<7)
//#define WDE	  (1<<3)
//#define WDP3    (1<<5)
//#define WDP2    (1<<2)
//#define WDP1    (1<<1)
//#define WDP0    (1<<0)
#define PB4_T		(1<<4)
#define SE_T		(1<<5)
#define SM1_T		(1<<4)
#define SM0_T		(1<<3)
#
int main(void)
{
	int counter=0;	
	//Enable watchdog timer interrupt
	SREG|=IBIT;		//set the IBIT from the Status Registers to 1 to enable the interrupts
	
	//to enable the prescaler on Watchdog you need to follow a specific sequence of steps (see page 39 in datasheet)
	//1. write 1 to the bits WDCE and WDE (one single operation)
	WDTCR|=((1<<WDCE)|(1<<WDE));
	//2. within the next four clocks write to WDE and WDPbits as desired and clear WDCE. (one single operation)
	//set the watchdog timeout at 8 seconds
	WDTCR&=((~(1<<WDCE))&(~(1<<WDP1))&(~(1<<WDP2)));
	WDTCR|=((1<<WDE)|(1<<WDP3)|(1<<WDP0));
	
	//set the pin4 as Output
	DDRB|=PB4_T;
    /* Replace with your application code */
    while (1) 
    {
		if(counter%2){
			
			//turn on the LED connected to pin4
			PORTB|=PB4_T;
			//Set Sleep Enable bit to "TRUE"
			MCUCR|=SE_T;
			
			//Set the sleep mode to "Power-Down" with the two Sleep Mode Select Bits
			MCUCR|=SM1_T;	
			MCUCR&=~SM0_T;
			
			//increment the counter an make it at the next loop to go on the other branch of the IF statement
			counter+=1;
			asm("sleep");
		}else{
			
			//turn off the LED connected to pin4
			PORTB&=~PB4_T;
			counter+=1;
			_delay_ms(2000);
		}
    }
}

