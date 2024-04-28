#define ADCSRA (*(volatile unsigned char*) 0x06)
#define ACSR (*(volatile unsigned char*) 0x08)
#define PINB (*(volatile unsigned char*) (0x20 + 0x16)) 
#define DDRB (*(volatile unsigned char*) (0x20 + 0x17))
#define PORTB (*(volatile unsigned char*) (0x20 + 0x18)) 
#define WDTCR (*(volatile unsigned char*) 0x21)  
#define PRR (*(volatile unsigned char*) 0x25)
#define BODCR (*(volatile unsigned char*) 0x30)
#define MCUSR (*(volatile unsigned char*) 0x34)
#define MCUCR (*(volatile unsigned char*) 0x35)
#define SREG (*(volatile unsigned char*) 0x3F)

// the setup function runs once when you press reset or power the board
void setup() {
  //Keep button pressed (HIGH) for 5 seconds than release (LOW)
  DDRB |= 1<<4; // set PIN4 as output
  PORTB |= 1<<4; // set PIN 4 to HIGH (press button)
  delay(50000); 
  PORTB ^= 1<<4; // toggle PIN4 (set PIN 4 to LOW - release button)

  //Power reduction register
  PRR |= 1<<1;//PowerReduction Timer/Counter0
  ADCSRA &= ~(1<<7); //Before PRR set, Disable ADC
  PRR |= 1; //PowerReduction ADC
  //Disable Analog Comparator
  ACSR |= 1<<7;
  //Disable watchdog
  MCUSR &= ~(1<<3); //clear WDRF 
  WDTCR |= 1<<4; //set WDCE to 1
  WDTCR &= ~(1<<3); //clear WDE 
  //Disable BOD
  BODCR = 0x3; //set BODS and BODSE to 1
  BODCR = 0x2; //set BODS to 1 and BODSE to 0
  //sleep to disable BOD
  asm volatile
  ("\
    SLEEP\
  ");

  //Select Sleep mode and enter sleep
  MCUCR |= 1<<5; // set SE bit to 1 for ECU to be able to enter in SLEEP mode
  MCUCR |= 1<<4; // set SM1 and SM0 bits to 1, select sleep mode POWER_DOWN when SLEEP command is sent
  //Sleep until reset
  asm volatile
  ("\
    CLI ;Disable global interrupt \
    SLEEP\
  ");
}

// the loop function runs over and over again forever
void loop() {

  /* should never get here, but as a safery measure put MCU again to sleep */
  asm volatile
  ("\
    SLEEP\
  ");
}
