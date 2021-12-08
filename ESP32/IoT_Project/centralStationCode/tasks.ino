/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/
/* define task for handling the FSM of the central hub*/
void TaskHandleFSM( void *pvParameters )
{
  (void) pvParameters;

  for (;;)
  {
    switch(currentState)
    {
      case initMeshState:
      {
        /* initialize the meshFunction part */
        FunctionInitMesh();
        currentState = meshState;
        break;
      }
      case meshState:
      {
        FunctionSendMessage();
        vTaskDelay(TICKS_DELAY*1000);
        if(true == buttonPressed)
          currentState = deactivateMeshState;
        break;
      }
      case deactivateMeshState:
      {
        FunctionMeshStop();
        currentState = initServerState;
        break;
      }
      case initServerState:
      {
        /* initialize the centralHubFunction part */
        FunctionInitSPIFFS();
        FunctionInitWiFiAP();
        FunctionInitAsyncServer();
        currentState = serverState;
        break;
      }
      case serverState:
      {
        if(true == buttonPressed)
          currentState = deactivateServerState;
        break;
      }
      case deactivateServerState:
      {
        FunctionWebServerStop();
        currentState = initMeshState;
        break;
      }
      default:
      {
        currentState = initMeshState;
        break;
      }
    }
    buttonPressed = false;
    /* TICKS_DELAY (one tick = 15ms) in between reads for stability */
    vTaskDelay(TICKS_DELAY);  
  }
}
