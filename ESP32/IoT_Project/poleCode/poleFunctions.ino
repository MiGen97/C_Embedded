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
//  Serial.print("Led set to:");
//  Serial.println(pPWMValue);
  ledcWrite(PWM_LED_CHANNEL, pPWMValue);
}

/** 
 *  Function for selecting how to turn on the bulb 
 *  with a fixed time interval or by light intensity
 */
void FunctionSetModeOfBulbToggle(uint8_t pMode)
{

}


/**
 * Function for reading the analog value from the Photoresistor 
 */
boolean FunctionCheckEnvironmentalLightIntensity(void)
{
  boolean answer = false;
  /* read the input on photoresistor */
  uint16_t sensorValue = analogRead(PHOTORESISTOR_PIN);
  /* print out the value you read: */
//  Serial.print("Photoresistor value is ");
//  Serial.println(sensorValue);
  if(LIGHT_INTENSITY_LOW > sensorValue)
    answer = true;
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
