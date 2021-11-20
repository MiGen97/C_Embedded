/*-----------------------------------------------*/
/*------------------ Includes -------------------*/
/*-----------------------------------------------*/
#include "painlessMesh.h"

/*-----------------------------------------------*/
/*------------------ Defines --------------------*/
/*-----------------------------------------------*/
#define PRO_CORE 0
#define APP_CORE 1

/* pins definition */
#define LED_PIN 2
#define PHOTORESISTOR_PIN 36
#define MOVEMENT_SENSOR_PIN 13

/* pole node configuration parameters */
#define ID "002"

/* magic numbers replacement */
#define TICKS_DELAY 5
#define BULB_TOGGLE_MODE_LIGHT_INTENSITY false
#define BULB_TOGGLE_MODE_TIME_INTERVAL   true
/* analog values ranges from 0=0V to 4096=3.3V */
#define LIGHT_INTENSITY_LOW   ((uint16_t) 1000u)
#define LIGHT_INTENSITY_HIGH  ((uint16_t) 3000u)
/* setting PWM properties */
#define PWM_FREQ        ((uint16_t)1000u)
#define PWM_LED_CHANNEL ((uint16_t) 0u)
#define PWM_RESOLUTION  ((uint16_t) 16u)
/* Mesh settings */
#define   MESH_PREFIX     "Comani_Lights_System"
#define   MESH_PASSWORD   "Sneaky_Peaky_Like*2021*"
#define   MESH_PORT       5555
#define   MESH_GENERIC_RESPONSE_MESSAGE  "Major Tom here, I can hear you low and clear Ground control." //"Ground Control to major Tom. Can you hear me?"

/* values for the intesity of the bulb
 * max value is 2^16 - 1 = 65535
 */
typedef enum
{
  bulbMaximumIntensity = ((uint16_t)65535u),
  bulbMinimumIntensity = ((uint16_t)(bulbMaximumIntensity/5u)),
  bulbTurnedOff = ((uint16_t)0u)
}bulbStates;



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
/* define task for reading the value returned by the movement sensor */
void TaskCheckMovement( void *pvParameters ); 
/* define task for checking the conditions to toggle the bulb */
void TaskCheckToggleBulbConditions( void *pvParameters );
/* define task for controlling the bulb */
void TaskControlBulb( void *pvParameters );
/* define task for mesh tasks */
void TaskMaintainMesh( void *pvParameters );
/* define task for sending message to the mesh*/
void TaskSendMeshMessage( void *pvParameters );

/******************/
/* POLE FUNCTIONS */
/******************/
void FunctionInitPWMLED(void);
void FunctionSetBulb(uint16_t pPWMValue);
void FunctionSetModeOfBulbToggle(uint8_t pMode);
boolean FunctionCheckEnvironmentalLightIntensity(void);
boolean FunctionCheckLightTimeInterval(uint32_t pTime);

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
  
  /* initialize the poleFunction part */
  FunctionInitPWMLED();
  pinMode(PHOTORESISTOR_PIN, INPUT);
  pinMode(MOVEMENT_SENSOR_PIN, INPUT);

  /* initialize the meshFunction part */
  FunctionInitMesh();
  
  /* initialize serial communication at 115200 bits per second: */
  Serial.begin(115200);

  /* Set up the tasks to run independently. */
  xTaskCreatePinnedToCore(
    TaskCheckMovement
    ,  "TaskCheckMovement"   /* A name just for humans */
    ,  1024   /* This stack size can be checked & adjusted by reading the Stack Highwater */
    ,  NULL
    ,  1      /* Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest. */
    ,  NULL 
    ,  APP_CORE);

  xTaskCreatePinnedToCore(
    TaskCheckToggleBulbConditions
    ,  "TaskCheckToggleBulbConditions"
    ,  1024   /* Stack size */
    ,  NULL
    ,  1      /* Priority */
    ,  NULL 
    ,  APP_CORE);

  xTaskCreatePinnedToCore(
    TaskControlBulb
    ,  "TaskControlBulb"
    ,  1024   /* Stack size */
    ,  NULL
    ,  1      /* Priority */
    ,  NULL 
    ,  APP_CORE);

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
