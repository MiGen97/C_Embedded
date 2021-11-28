/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

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
