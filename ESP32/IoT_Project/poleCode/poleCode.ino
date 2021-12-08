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

/* pins definition */
#define LED_PIN                 2
#define PHOTORESISTOR_PIN       36
#define MOVEMENT_SENSOR_PIN     13
#define DIAGNOSE_LED_PIN        34
/* pole node configuration parameters */
#define POLE_ID ((uint32_t)1u)   /* 2 */     /* 3 */
#define CENTRAL_HUB_ID ((uint32_t)2988694845u) 
/* magic numbers replacement */
#define TICKS_DELAY                       5
#define BULB_TOGGLE_MODE_LIGHT_INTENSITY  false
#define BULB_TOGGLE_MODE_TIME_INTERVAL    true
/* analog values ranges from 0=0V to 4095=3.3V */
#define LIGHT_INTENSITY_LOW   ((uint16_t) 1000u)
#define LIGHT_INTENSITY_HIGH  ((uint16_t) 2000u)
/* setting PWM properties */
#define PWM_SECONDS_TO_MILLS(x) ((uint16_t)(x*1000u))
#define PWM_FREQ        ((uint16_t) 100u)
#define PWM_PERIOD      ((uint16_t)(PWM_SECONDS_TO_MILLS((float)1u/PWM_FREQ)))
#define PWM_LED_CHANNEL ((uint16_t) 0u)
#define PWM_RESOLUTION  ((uint16_t) 12u)
/* analog values for MIN=0=0V and MAX=4095=3.3V */
#define ANALOG_IN_MIN   ((uint16_t) 0u)
#define ANALOG_IN_MAX   ((uint16_t) 4095u)
#define ANALOG_IN_LOW_INTERFERENCE   ((uint16_t) 1000u) /* In ESP32 ADC is not linear 0V=0.1V, 3.2V=3.3V */
                                                         /* 3.3V/4095 = 0.0008V per unit  */
                                                         /* 0.0008V*1000 =  0.8V interference tolerance  */
#define ANALOG_IN_HIGH_INTERFERENCE   ((uint16_t) 100u)
#define ANALOG_IN_PWD_DIVIDE_PERIOD   ((uint16_t) 10u)
#define ANALOG_IN_PWM_SAMPLE_RATE     (PWM_PERIOD*ANALOG_IN_PWD_DIVIDE_PERIOD)
/* Mesh settings */
#define   MESH_PREFIX     "Comani_Lights_System"
#define   MESH_PASSWORD   "Sneaky_Peaky_Like*2021*"
#define   MESH_PORT       5555

/* states in which the bulb can be
 * max value is 2^16 - 1 = 65535
 */
typedef enum
{
  bulbMaximumIntensity = ((uint16_t)ANALOG_IN_MAX),
  bulbMinimumIntensity = ((uint16_t)(bulbMaximumIntensity/5u)),
  bulbTurnedOff = ((uint16_t)0u),
  bulbOperatesNormal = (uint16_t)1u,
  bulbOpenCircuit = (uint16_t)2u,
  bulbShortCircuit = (uint16_t)3u,
} bulbStates;

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
/* define task for bulb diagnose check */
void TaskDiagnoseBulb(void);
/* define task for sending message to the mesh*/
void TaskSendMeshMessage( void *pvParameters );

/******************/
/* POLE FUNCTIONS */
/******************/
void FunctionInitPWMLED(void);
void FunctionSetBulb(uint16_t pPWMValue);
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
  /* initialize serial communication at 115200 bits per second: */
  Serial.begin(115200);
  
  /* initialize the poleFunction part */
  FunctionInitPWMLED();
  pinMode(PHOTORESISTOR_PIN, INPUT);
  pinMode(MOVEMENT_SENSOR_PIN, INPUT);

  /* initialize the meshFunction part */
  FunctionInitMesh();
  
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
    ,  NULL /* Task handler */ 
    ,  APP_CORE);

  xTaskCreatePinnedToCore(
    TaskDiagnoseBulb
    ,  "TaskDiagnoseBulb"   /* A name just for humans */
    ,  1024   /* This stack size can be checked & adjusted by reading the Stack Highwater */
    ,  NULL
    ,  1      /* Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest. */
    ,  NULL 
    ,  APP_CORE);
    
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
