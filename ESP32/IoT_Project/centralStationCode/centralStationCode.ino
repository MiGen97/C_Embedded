/*-----------------------------------------------*/
/*------------------ Includes -------------------*/
/*-----------------------------------------------*/
#include "painlessMesh.h"

/*-----------------------------------------------*/
/*------------------ Defines --------------------*/
/*-----------------------------------------------*/
/* FreeRTOS defines */
#define PRO_CORE 0
#define APP_CORE 1

/* central hub configuration parameters */
#define ID ((uint32_t)0u) 

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

typedef struct pInfo
{
  uint16_t poleID;
  uint16_t statusBulb;
  uint16_t bulbIntensity;
  boolean isNight;
  boolean detectsMovements;
} poleInfo;

/*--------------------------------------------------*/
/*-------------- External Variables ----------------*/
/*--------------------------------------------------*/
extern painlessMesh mesh;

/*--------------------------------------------------*/
/*------------------ Prototypes --------------------*/
/*--------------------------------------------------*/
/*********/
/* TASKS */
/*********/
/* define task for mesh tasks */
void TaskMaintainMesh( void *pvParameters );
/* define task for sending message to the mesh*/
void TaskSendMeshMessage( void *pvParameters );

/******************/
/* POLE FUNCTIONS */
/******************/
void FunctionSetModeOfBulbToggle(uint8_t pMode);

/******************/
/* MESH FUNCTIONS */
/******************/
void FunctionSendMessage(void); 
void FunctionReceivedCallback(uint32_t from, String &msg);
void FunctionNewConnectionCallback(uint32_t nodeId);
void FunctionChangedConnectionCallback(void);
void FunctionNodeTimeAdjustedCallback(int32_t offset);

/*--------------------------------------------------*/
/*---------------- Init function -------------------*/
/*--------------------------------------------------*/
/* the setup function runs once when you press reset or power the board */
void setup() {
  /* initialize the meshFunction part */
  FunctionInitMesh();
  
  /* initialize serial communication at 115200 bits per second: */
  Serial.begin(115200);

  xTaskCreatePinnedToCore(
    TaskMaintainMesh
    ,  "TaskMaintainMesh"
    ,  1024   /* Stack size */
    ,  NULL
    ,  1      /* Priority */
    ,  NULL 
    ,  PRO_CORE);
    
  xTaskCreatePinnedToCore(
    TaskSendMeshMessage
    ,  "TaskSendMeshMessage"
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
  mesh.update();
}
