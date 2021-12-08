/*---------------------------------------------------------*/
/*---------------- Central Hub Functions ------------------*/
/*---------------------------------------------------------*/
/* Replaces placeholders */
String processor(const String& var)
{
  Serial.println(var);
  if(var == "bulbControlMode")
  {
    return bulbToggleMode ? "Time" : "Light";
  }
  else if(var == "poles")
  {
    String polesConnected = "<option value=\"none\" selected disabled hidden> Choose pole to display info </option>\n";
    for(int i=0;i<maxPoleID;i++)
    {
      polesConnected += "<option value=\""+String(polesInfo[i].poleID)+"\"> Pole"+String(i)+" </option>\n";
    }
    return polesConnected;
  }
  else if(var == "poleID")  return String(polesInfo[poleIndex-1u].poleID);
  else if(var == "statusBulb")  return String(polesInfo[poleIndex-1u].statusBulb);
  else if(var == "bulbIntensity")  return String(polesInfo[poleIndex-1u].bulbIntensity);
  else if(var == "isNight")  return String(polesInfo[poleIndex-1u].isNight);
  else if(var == "detectsMovement")  return String(polesInfo[poleIndex-1u].detectsMovement);
  
  return String();
}

void FunctionInitSPIFFS(void)
{
  /* Initialize SPIFFS */
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    Serial.println("Restarting in 15 seconds");
    /* TICKS_DELAY (one tick = 15ms) in between reads for stability */
    vTaskDelay(TICKS_DELAY*2000);  
    ESP.restart();
  }
}

void FunctionInitWiFiAP(void)
{
  // Set up the AP Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);
  /* Print ESP32 Local IP Address */
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}

void FunctionInitAsyncServer(void)
{
  /* Route for root / web page */
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/startPage.html", String(), false, processor);
  });
  
  /* Route to load style.css file */
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  /* Route to set the bulb control mode to light intensity */
  server.on("/lightMode", HTTP_GET, [](AsyncWebServerRequest *request){
    bulbToggleMode = BULB_TOGGLE_MODE_LIGHT_INTENSITY; 
    request->send(SPIFFS, "/startPage.html", String(), false, processor);
  });

  /* Route to set the bulb control mode to time interval */
  server.on("/timeMode", HTTP_GET, [](AsyncWebServerRequest *request){
    bulbToggleMode=BULB_TOGGLE_MODE_TIME_INTERVAL;   
    request->send(SPIFFS, "/startPage.html", String(), false, processor);
  });
  
  /* Route to go to poles list */
  server.on("/display_poles", HTTP_GET, [](AsyncWebServerRequest *request){  
    request->send(SPIFFS, "/poleList.html", String(), false, processor);
  });

  /* Route to display the info of the selected pole */
  server.on("/display_info", HTTP_GET, [](AsyncWebServerRequest *request){  
    request->send(SPIFFS, "/displayInfo.html", String(), false, processor);
  });

  /* Send a GET request to <ESP_IP>/display_info?poleID=<inputMessage1> */
  server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request){  
    /* GET input1 value on <ESP_IP>/display_info?poleID=<inputMessage1> */
    if (request->hasParam(input_paramter1)) {
      poleIndex = (request->getParam(input_paramter1)->value()).toInt();
    }
    else {
      poleIndex = -1;
    }
    Serial.print("poleIndex is: ");
    Serial.println(poleIndex);
    request->send(200, "text/plain", "OK");
  });
  
  /* Start server */
  server.begin();
}

/* Function used to deactivate the host server */
void FunctionWebServerStop(void)
{
  WiFi.softAPdisconnect (true);
  server.end();
}
