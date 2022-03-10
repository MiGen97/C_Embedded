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
       * sample the PWM signal 10*PeriodOfPWM
       */
      uint16_t sensorValue = 0u;
      for(int i=0;i<ANALOG_IN_PWM_SAMPLE_RATE;i++)
      {
        sensorValue = analogRead(DIAGNOSE_LED_PIN);
        if((ANALOG_IN_MIN + ANALOG_IN_LOW_INTERFERENCE) < sensorValue)
         break;
         vTaskDelay(1u);
      }
      
      /* read the input on analog DIAGNOSE_LED_PIN: */
      if(sensorValue < (ANALOG_IN_MIN + ANALOG_IN_LOW_INTERFERENCE))
      {
        bulbDiagnosticState = bulbShortCircuit;
      }
      else if(sensorValue > (ANALOG_IN_MAX - ANALOG_IN_HIGH_INTERFERENCE))
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
