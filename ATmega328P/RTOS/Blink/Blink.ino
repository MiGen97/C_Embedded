/*Functionality
* This code blink the internal LED at every second 
* And turns on and off an external LED at interrupt appear
* On PIN2 (interrupt from a Button)
*/
//include the core for FreeRTOS on ArduinoUno
#include <Arduino_FreeRTOS.h>

// define the task functions
void TaskBlinkInternal( void *pvParameters );
void TaskBlinkExternal( void *pvParameters );

TaskHandle_t xHandle;

void Pressed(){
  vTaskResume( xHandle );
}
// the setup function runs once when you press reset or power the board
void setup() {
  // Now set up two tasks to run independently.
  xTaskCreate(
    TaskBlinkInternal
    ,  (const char *)"BlinkInternal" 
    ,  128 
    ,  NULL
    ,  2 
    ,  NULL );

  xTaskCreate(
    TaskBlinkExternal
    ,  (const char *) "BlinkExternal"
    ,  128
    ,  NULL
    ,  1
    ,  &xHandle );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlinkInternal(void *pvParameters)  // This is a task.
{
  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
  }
}

void TaskBlinkExternal(void *pvParameters)  // This is a task.
{
  // initialize pin 6 as an output.
  pinMode(6, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2),Pressed,RISING);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(6, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskSuspend( NULL );
    digitalWrite(6, LOW);    // turn the LED off by making the voltage LOW
    vTaskSuspend( NULL );
  }
}
