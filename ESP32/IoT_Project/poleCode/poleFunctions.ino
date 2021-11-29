/*--------------------------------------------------*/
/*---------------- Pole Functions ------------------*/
/*--------------------------------------------------*/


/**
 * Function to initialize the PWM of LED
 *
 */
void FunctionInitPWMLED(void)
{
  /* configure LED PWM functionalitites */
  ledcSetup(PWM_LED_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  /* attach the channel to the GPIO to be controlled */
  ledcAttachPin(LED_PIN, PWM_LED_CHANNEL);
}

/**
 * Function to set the bulb ON or OFF
 *
 */
void FunctionSetBulb(uint16_t pPWMValue)
{
  /* changing the LED brightness*/
  ledcWrite(PWM_LED_CHANNEL, pPWMValue);
  bulbPWMValue = (bulbStates)pPWMValue;
}

/**
 * Function for reading the analog value from the Photoresistor 
 */
boolean FunctionCheckEnvironmentalLightIntensity(void)
{
  /* static variable to make a hysteresis on the light threshold */
  static boolean answer = false;
  /* read the input on photoresistor */
  uint16_t sensorValue = analogRead(PHOTORESISTOR_PIN);

  /* hysteresis logic */
  if(LIGHT_INTENSITY_LOW > sensorValue)
    answer = true;
  if(LIGHT_INTENSITY_HIGH < sensorValue)
    answer = false;
  return answer;
}


/** 
 * Function for reading the time interval in which the bulb should be ON
 */
boolean FunctionCheckLightTimeInterval(uint32_t pTime)
{
  
}

/**
 * Function for reading the analog value from the Photoresistor 
 */
boolean FunctionCheckMovement(void)
{
  /* read the input on movement sensor pin: */
  boolean answer = digitalRead(MOVEMENT_SENSOR_PIN);
  return answer;
}
