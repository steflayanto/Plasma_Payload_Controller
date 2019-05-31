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
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>  // Used for all Adafruit Sensors

#define PIN_NAME 1
#define OTHER PIN_NAME 2
#define RELAY_PIN 10                //this means before compiling, find RELAY replace with 10

//Time Estimates (cumulative duration)
#define LATE_COAST_TIME 0
#define EARLY_COAST_TIME 0
#define ENGINE_BURN_TIME 0

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

//BME
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)
