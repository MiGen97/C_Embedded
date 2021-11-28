/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

/* define task for checking the conditions to toggle the bulb */
void TaskCheckToggleBulbConditions( void *pvParameters )
{
  (void) pvParameters;

  for (;;)
  {
    if(BULB_TOGGLE_MODE_LIGHT_INTENSITY == bulbToggleMode)
      bulbTurnOnCondition = FunctionCheckEnvironmentalLightIntensity();
    else
      bulbTurnOnCondition = FunctionCheckLightTimeInterval(1u);

    /* TICKS_DELAY (one tick = 15ms) in between reads for stability */
    vTaskDelay(TICKS_DELAY);  
  }
}

/* define task for reading the value returned by the movement sensor */
void TaskCheckMovement( void *pvParameters )
{
  (void) pvParameters;

  for (;;)
  {
    if(true == FunctionCheckMovement())
    {
      /* set bulb intensity to maximum */
      bulbMovementCondition = true;
    }
    else
    {
      /* set bulb intensity to minimum */
      bulbMovementCondition = false;
    }
    
    /* TICKS_DELAY (one tick = 15ms) in between reads for stability */
    vTaskDelay(TICKS_DELAY);  
  }
}

/* define task for controlling the bulb */
void TaskControlBulb( void *pvParameters )
{
  (void) pvParameters;

  for (;;)
  {
    if(true == bulbTurnOnCondition)
    {
      if(true == bulbMovementCondition)
      {
       /* print out the value of bulb set*/
       FunctionSetBulb(bulbMaximumIntensity);
      }
      else
      {
        /* print out the value of bulb set*/
        FunctionSetBulb(bulbMinimumIntensity);
      }
    }
    else
    {
      FunctionSetBulb(bulbTurnedOff);
    }
    /* TICKS_DELAY (one tick = 15ms) in between reads for stability */
    vTaskDelay(TICKS_DELAY);  
  } 
}

/**
 * Task to check if there is a short or an open circuit on the bulb
 */
void TaskDiagnoseBulb( void *pvParameters )
{
  (void) pvParameters;

  for (;;)
  { 
    /* diagnostic the LED only if is ON */
    if(true == bulbTurnOnCondition)
    {
      /* To read corretly the state of the LED, not interfered by PWM
       * set PWM value at max (so that we can read the voltage that is on the LED)
       */

      /* FIX: wrong analogRead value 
       *  1.Disable task that controlls the LED 
       *  2.Set the LED to Full Duty Cycle (100% 3.3V)
       *  3.Put 1 tick delay so that the PWM command will take effect
       *  4.Read the analog value of the LED in order to diagnose it
       *  5.Enable task that controlls the LED 
       */
      vTaskSuspend(xHandle); 
      FunctionSetBulb(bulbMaximumIntensity);
      vTaskDelay(1u);
      uint16_t sensorValue = analogRead(DIAGNOSE_LED_PIN);
      vTaskResume(xHandle);
      
      /* read the input on analog DIAGNOSE_LED_PIN: */
      if(sensorValue < (ANALOG_IN_MIN + ANALOG_IN_INTERFERENCE))
      {
        bulbDiagnosticState = bulbShortCircuit;
      }
      else if(sensorValue > (ANALOG_IN_MAX - ANALOG_IN_INTERFERENCE))
      {
        bulbDiagnosticState = bulbOpenCircuit;
      }
      else
      {
        bulbDiagnosticState = bulbOperatesNormal;
      }
//      Serial.print("Led diagnostic is:");
//      Serial.println(bulbDiagnosticState);
//      Serial.print("Sensor Value is:");
//      Serial.println(sensorValue);
    }
    /* TICKS_DELAY (one tick = 15ms) in between reads for stability */
    vTaskDelay(100*TICKS_DELAY);  
  } 
}

/* define task for mesh maintain */
void TaskMaintainMesh( void *pvParameters )
{
  (void) pvParameters;

  for (;;)
  {
    
    /* TICKS_DELAY (one tick = 15ms) in between reads for stability */
    vTaskDelay(TICKS_DELAY);  
  } 
}

/* define task to send messages through mesh*/
void TaskSendMeshMessage( void *pvParameters )
{
  (void) pvParameters;

  for (;;)
  {
    FunctionSendMessage();
    /* TICKS_DELAY (one tick = 15ms) in between reads for stability */
    vTaskDelay(TICKS_DELAY*1000);  
  } 
}
