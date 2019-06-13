/* Header file for SARP Master Controller
 * Pinouts
 * 0
 * 1
 * 2
 * 3
 * 4
 * 5
 * 6
 * 7
 * 8
 * 9
 * 10 FOR THE RELAY
 * 11
 * 12
 * 13
 */
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>  // Used for all Adafruit Sensors
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_BME280.h>
#include <SparkFunTMP102.h>

// Required for Serial on Zero based boards
#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
#define Serial SERIAL_PORT_USBVIRTUAL
#endif

#define PIN_NAME 1
#define OTHER PIN_NAME 2
#define RELAY_PIN 10                //this means before compiling, find RELAY replace with 10

//Time Estimates (cumulative duration)
#define LATE_COAST_TIME 0
#define EARLY_COAST_TIME 0
#define ENGINE_BURN_TIME 0

//This constant and struct are all that is needed for the MAF
#define MAF_SIZE 5 // number of samples for the running avg
struct {
  float total;
  float arr[MAF_SIZE];
  int index;
} filter;

//Global Variables
boolean activated = false;  // Stores whether plasma has already been activated
float weightedFlightStage = 0;      // Stores expected flight stage:
                          /*  Flight stages:
                           *  0: pre-launch
                           *  1: engine-burn
                           *  2: early-coast-phase
                           *  3: late-coast-phase
                           *  4: descent
                           */
//Sensor Objects
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();
Adafruit_BME280 bme; // I2C
TMP102 tempSens(0x48);

//BME
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define ALT_OFFSET -1401 // Based on elevation of spaceport america (1.401 km)
