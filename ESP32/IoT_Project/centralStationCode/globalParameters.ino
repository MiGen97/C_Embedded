/* variables used in the messaging */
boolean bulbToggleMode = BULB_TOGGLE_MODE_LIGHT_INTENSITY;
poleInfo polesInfo[MESH_MAX_POLE_NUMBER];
uint8_t maxPoleID = 0u;

/* internal variable needed in code */
painlessMesh  mesh;
FSMStates currentState = initMeshState;
boolean buttonPressed = false;

/* variables used for the web server */
/* Create AsyncWebServer object on port 80 */
AsyncWebServer server(80);
const char* input_paramter1 = "poleID";
int poleIndex=0;

/* Replace with your network credentials */
const char* ssid     = "Comani_Lights_System_AP";
const char* password = "easy_peasy_LEM0N_SQU1ZY";

/* ISR Response */
void IRAM_ATTR isr() {
  buttonPressed = true;
}
