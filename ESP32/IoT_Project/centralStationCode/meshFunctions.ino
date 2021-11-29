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
#if ARDUINOJSON_VERSION_MAJOR==6
  DynamicJsonDocument jsonBuffer(1024);
  JsonObject msg = jsonBuffer.to<JsonObject>();
#else
  DynamicJsonBuffer jsonBuffer;
  JsonObject& msg = jsonBuffer.createObject();
#endif
  msg["SenderID"]=ID;
  msg["ToogleMode"] = bulbToggleMode;

  String str;
#if ARDUINOJSON_VERSION_MAJOR==6
  serializeJson(msg, str);
#else
  msg.printTo(str);
#endif
  mesh.sendBroadcast(str);
}

/* Function for event message received */
void FunctionReceivedCallback(uint32_t from, String &msg)
{
#if ARDUINOJSON_VERSION_MAJOR==6
  DynamicJsonDocument jsonBuffer(1024 + msg.length());
  DeserializationError error = deserializeJson(jsonBuffer, msg);
  if (error) {
    Serial.printf("DeserializationError\n");
    return;
  }
  JsonObject root = jsonBuffer.as<JsonObject>();
#else
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(msg);
#endif

  /* the programmer must be sure that the PoleID is unique,
   * otherwise, the data of poles will be overwritten
   * Note:  subtract 1u to use also the position 0 in the polesInfo array,
   *        ID 0 is reserved to the central hub
   */
  int poleIndex =(root["PoleID"].as<String>()).toInt()-1u;
  polesInfo[poleIndex].poleID = (root["PoleID"].as<String>()).toInt();
  polesInfo[poleIndex].statusBulb = (bulbStates)((root["StatusBulb"].as<String>()).toInt());
  polesInfo[poleIndex].bulbIntensity = (root["BulbLightIntensity"].as<String>()).toInt();
  polesInfo[poleIndex].isNight = root["IsNight"].as<String>() == "true" ? true : false;
  polesInfo[poleIndex].detectsMovements = root["DetectedMovement"].as<String>() == "true" ? true : false;

//  Serial.printf("Message is \"%s\".\nLocal bulbState is %d.\n", msg.c_str(),bulbDiagnosticState);
//  Serial.printf("Pole info is: poleID=%d, statusBulb=%d, bulbIntensity=%d, isNight=%d, detectsMovements=%d\n",
//                polesInfo[poleIndex].poleID,polesInfo[poleIndex].statusBulb,polesInfo[poleIndex].bulbIntensity,
//                polesInfo[poleIndex].isNight,polesInfo[poleIndex].detectsMovements);
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
