/* variables used in the messaging */
boolean bulbToggleMode = BULB_TOGGLE_MODE_LIGHT_INTENSITY;
bulbStates bulbDiagnosticState = bulbOperatesNormal;

/* internal variable needed in code */
boolean bulbTurnOnCondition = false;
boolean bulbMovementCondition = false;
TaskHandle_t xHandle = NULL;
painlessMesh  mesh;
