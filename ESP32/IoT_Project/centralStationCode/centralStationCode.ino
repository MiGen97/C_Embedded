/*-----------------------------------------------*/
/*------------------ Includes -------------------*/
/*-----------------------------------------------*/
#include "WiFi.h"
#include "SPIFFS.h"
#include "painlessMesh.h"
#include "ESPAsyncWebServer.h"

/*-----------------------------------------------*/
/*------------------ Defines --------------------*/
/*-----------------------------------------------*/
/* FreeRTOS defines */
#define PRO_CORE 0
#define APP_CORE 1

/* central hub configuration parameters */
#define ID ((uint32_t)0u) 
/* State button select */
#define SERVER_BUTTON ((uint8_t) 0u)
/* magic numbers replacement */
#define TICKS_DELAY                       5
#define BULB_TOGGLE_MODE_LIGHT_INTENSITY  false
#define BULB_TOGGLE_MODE_TIME_INTERVAL    true
/* analog values for MIN=0=0V and MAX=4095=3.3V */
#define ANALOG_IN_MAX   ((uint16_t) 4095u)
/* Mesh settings */
#define   MESH_PREFIX     "Comani_Lights_System"
#define   MESH_PASSWORD   "Sneaky_Peaky_Like*2021*"
#define   MESH_PORT       5555
#define   MESH_MAX_POLE_NUMBER ((uint16_t)100u)

typedef enum
{
  bulbMaximumIntensity = ((uint16_t)ANALOG_IN_MAX),
  bulbMinimumIntensity = ((uint16_t)(bulbMaximumIntensity/5u)),
  bulbTurnedOff = ((uint16_t)0u),
  bulbOperatesNormal = (uint16_t)1u,
  bulbOpenCircuit = (uint16_t)2u,
  bulbShortCircuit = (uint16_t)3u,
} bulbStates;

typedef enum 
{
  initMeshState = (uint8_t)0u, /* state to init the mesh */
  meshState = (uint8_t)1u,   /* state when central hub is connected to the mesh, this is the default state */
  deactivateMeshState = (uint8_t)2u, /* state to deactivate the mesh */
  initServerState = (uint8_t)3u, /* state to init the server */
  serverState = (uint8_t)4u,  /* state when the central hub hosts the server for config and info display */
  deactivateServerState = (uint8_t)5u, /* state to init the server */
}FSMStates;

typedef struct pInfo
{
  uint16_t poleID;
  uint16_t statusBulb;
  uint16_t bulbIntensity;
  boolean isNight;
  boolean detectsMovement;
} poleInfo;


/*--------------------------------------------------*/
/*-------------- External Variables ----------------*/
/*--------------------------------------------------*/
extern painlessMesh mesh;
extern FSMStates currentState;
extern boolean bulbToggleMode;
/*--------------------------------------------------*/
/*------------------ Prototypes --------------------*/
/*--------------------------------------------------*/
/*********/
/* TASKS */
/*********/
/* define task for handling the FSM of the central hub*/
void TaskHandleFSM( void *pvParameters );

/******************/
/* ISR FUNCTIONS */
/******************/
void IRAM_ATTR isr(void);

/******************/
/* POLE FUNCTIONS */
/******************/
String FunctionProcessor(const String& var);
void FunctionInitSPIFFS(void);
void FunctionInitWiFiAP(void);
void FunctionInitAsyncServer(void);
void FunctionSetModeOfBulbToggle(uint8_t pMode);
void FunctionWebServerStop(void);
/******************/
/* MESH FUNCTIONS */
/******************/
void FunctionInitMesh(void);
void FunctionSendMessage(void); 
void FunctionReceivedCallback(uint32_t from, String &msg);
void FunctionNewConnectionCallback(uint32_t nodeId);
void FunctionOnDroppedConnection(uint32_t nodeId);
void FunctionChangedConnectionCallback(void);
void FunctionNodeTimeAdjustedCallback(int32_t offset);
void FunctionMeshStop(void);
/*--------------------------------------------------*/
/*---------------- Init function -------------------*/
/*--------------------------------------------------*/
/* the setup function runs once when you press reset or power the board */
void setup() {
 /* initialize Serial communication at 115200 bits per second: */
  Serial.begin(115200);

  pinMode(SERVER_BUTTON, INPUT_PULLUP);
  attachInterrupt(SERVER_BUTTON, isr, FALLING);
  
  xTaskCreatePinnedToCore(
    TaskHandleFSM
    ,  "TaskHandleFSM"
    ,  4096  /* Stack size */
    ,  NULL
    ,  1      /* Priority */
    ,  NULL 
    ,  PRO_CORE);
    
  /* Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started. */
}

void loop()
{
  /* Empty. Things are done in Tasks. */
  if(meshState == currentState)
    mesh.update();
}
