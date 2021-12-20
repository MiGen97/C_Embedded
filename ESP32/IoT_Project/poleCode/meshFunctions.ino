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

  /* This node and all other nodes should ideally know the mesh contains a root, so call this on all nodes */
  mesh.setContainsRoot(true);
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
  msg["PoleID"]=POLE_ID;
  msg["StatusBulb"] = bulbDiagnosticState;
  msg["BulbLightIntensity"] = bulbPWMValue;
  msg["IsNight"] = bulbTurnOnCondition;
  msg["DetectedMovement"] = bulbMovementCondition;
  
  String str;
#if ARDUINOJSON_VERSION_MAJOR==6
  serializeJson(msg, str);
#else
  msg.printTo(str);
#endif
  Serial.printf("Pole send string:%s.\n",str);
  mesh.sendSingle(CENTRAL_HUB_ID, str);
}

/* Function for event message received */
void FunctionReceivedCallback(uint32_t from, String &msg)
{
#if ARDUINOJSON_VERSION_MAJOR==6
  DynamicJsonDocument jsonBuffer(1024 + msg.length());
  DeserializationError error = deserializeJson(jsonBuffer, msg);
  if (error) {
    Serial.printf("DeserializationError %s\n",error.c_str());
    return;
  }
  JsonObject root = jsonBuffer.as<JsonObject>();
#else
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(msg);
#endif

  if (root.containsKey("ToogleMode")) {
      bulbToggleMode = (root["ToogleMode"].as<String>() == "true") ? BULB_TOGGLE_MODE_TIME_INTERVAL : BULB_TOGGLE_MODE_LIGHT_INTENSITY;
      /* Serial.printf("Handled from %s. Toggle mode is %s. Message is \"%s\"\n", root["SenderID"].as<String>(), root["ToogleMode"].as<String>() == "true" ? "BULB_TOGGLE_MODE_TIME_INTERVAL" : "BULB_TOGGLE_MODE_LIGHT_INTENSITY", msg.c_str());
       */
  }
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
