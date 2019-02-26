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
 * 10
 * 11
 * 12
 * 13
 */
#include <Wire.h>
#include "MPU9250.h"
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>  // Used for all Adafruit Sensors

#define PIN_NAME 1
#define OTHER PIN_NAME 2

//Time Estimates
#define ENGINE_CUT_TIME 0
#define APOGEE_TIME 0
#define DESCENT_TIME 0
