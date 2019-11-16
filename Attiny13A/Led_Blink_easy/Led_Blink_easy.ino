void setup() {
 // initialize pin 4 (ATtiny leg 3) as an output.
 pinMode(4, OUTPUT);
}
void loop() {
 digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
 delay(1000);             // wait for a second
 digitalWrite(4, LOW);    // turn the LED off by making the voltage LOW
 delay(1000);             // wait for a second
} 
