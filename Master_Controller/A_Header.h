#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>  // Used for all Adafruit Sensors
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_BME280.h>
#include <SparkFunTMP102.h>
#include <Adafruit_Simple_AHRS.h>

///////////////////////////////////////////////////////////////////////////////////////////////
//Time Estimates (time that has passed since launch) IN SECONDS
#define LATE_COAST_TIME 40  //time that late coast ends (apogee)
#define EARLY_COAST_TIME 20 //time that early coast ends
#define ENGINE_BURN_TIME 15 //time that engine burn ends

//BME (ALTITUDES IN METERS not feet)
#define FACTOR 0.2f
#define LOW_BURN 50 //above this value means we're  in burn
#define LOW_EARLY 4115 //above this means in early coast
#define LOW_LATE 5300  //above means in late coast
#define HIGH_LATE 7620 //apogee
#define ALT_OFFSET -1401 // Based on elevation of spaceport america (1.401 km)

#define BUZZER_INTERVAL 10000

#define RELAY_PIN 11                //this means before compiling, find RELAY replace with 10
////////////////////////////////////////////////////////////////////////////////////////////////////////
// Required for Serial on Zero based boards
#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
#define Serial SERIAL_PORT_USBVIRTUAL
#endif

//This constant and struct are all that is needed for the MAF
#define MAF_SIZE 5 // number of samples for the running avg
struct {
  float total;
  float arr[MAF_SIZE];
  int index;
} BMEfilter;

struct {
  float total;
  float arr[MAF_SIZE];
  int index;
} coneFilter;

//Global Variables
boolean activated = false;  // Stores whether plasma has already been activated
float weightedFlightStage = 0;      // Stores expected flight stage:
/*  Flight stages:
    0: pre-launch
    1: engine-burn
    2: early-coast-phase
    3: late-coast-phase
    4: descent
*/

float alt = 0, altMAF = 0;
boolean inCone = false; //Whether inside the danger cone or not


//Sensor Objects
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(1000);
Adafruit_Simple_AHRS ahrs(&lsm.getAccel(), &lsm.getMag());
Adafruit_BME280 bme; // I2C
TMP102 tempSens(0x48);

//Danger Cone
double dangerAngle = 10;//33.0; // Highly arbitrary value in degrees //updated to 33 later in flight.

//LSM Data Objects
sensors_event_t accel, mag, gyro, temp;
//LSM Noise Buffer
int noiseBuffer = 15; //arbitrary value for now. Updated to +-4 after launched
