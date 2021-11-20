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

/* define task for mesh tasks */
void TaskMaintainMesh( void *pvParameters )
{
  (void) pvParameters;

  for (;;)
  {
    /* TICKS_DELAY (one tick = 15ms) in between reads for stability */
    vTaskDelay(TICKS_DELAY);  
  } 
}
