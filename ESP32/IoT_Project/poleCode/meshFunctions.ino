/*--------------------------------------------------*/
/*--------------- Mesh Functions -------------------*/
/*--------------------------------------------------*/

/* Function used to initialize the mesh */
void FunctionInitMesh(void)
{
  /* all types of debug messages */
  /* ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ) */
  mesh.setDebugMsgTypes( ERROR | STARTUP );  
  
  mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT );
  mesh.onReceive(&FunctionReceivedCallback);
  mesh.onNewConnection(&FunctionNewConnectionCallback);
  mesh.onChangedConnections(&FunctionChangedConnectionCallback);
  mesh.onNodeTimeAdjusted(&FunctionNodeTimeAdjustedCallback);
}

/* Function for sending the message through the mesh */
void FunctionSendMessage(void)
{
  String msg = MESH_GENERIC_RESPONSE_MESSAGE;
  msg += mesh.getNodeId();
  mesh.sendBroadcast( msg );
}

/* Function for event message received */
void FunctionReceivedCallback(uint32_t from, String &msg)
{
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
}

/* Function for event new node in mesh*/
void FunctionNewConnectionCallback(uint32_t nodeId)
{
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

/* Function for event changed connection in mesh */
void FunctionChangedConnectionCallback(void)
{
  Serial.printf("Changed connections\n");
}

/* Function for event local time synchronized with the mesh time */
void FunctionNodeTimeAdjustedCallback(int32_t offset)
{
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}
