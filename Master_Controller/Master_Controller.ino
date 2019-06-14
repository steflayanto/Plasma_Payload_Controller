#include "A_Header.h"

void setup() {
#ifndef ESP8266
  while (!Serial);     // For running on ESP boards. Will pause until serial console opens
#endif
  Serial.begin(116200);
  initSensors();
  relayInit();
}

void loop() {
  updateTrackedValues(); //Updates the values that are relevant to the decision algorithm
  //transmitToLogger();    //Directly reads and sends all sensor data to serial monitor. Some unnecessary reads.
  weightedFlightStage = decisionAlgorithm();
  if (activated) {
    return; //if already running, don't do anything below
  }
  if (checkTriggerConditions()) {
    trigger(10000, RELAY_PIN); //Run for 10 seconds
    activated = true;
  }
}


//Performs all initialization of sensors
void initSensors() {
  initLSM();
  initBME();
  initTempSens();
}

//Interacts with slave logger device
void transmitToLogger() {
  printLSMData();
  printBMEData();
  printTempSensData();
  Serial.println("Transmitting to logger");
}

//Decides whether to activate plasma (Stefan, Lexie, & Usman)
boolean checkTriggerConditions() {
  //Code will consider sensor data and flight stage and make a decision
  return true;
}

// Utility float map function with 3 digits precision. includes constrain
float mapFloat(float val, float inLo, float inHi, float outLo, float outHi) { 
  return map(constrain(val, inLo, inHi) * 1000, inLo * 1000, inHi * 1000, outLo * 1000, outHi * 1000) / 1000.0;
}

void updateTrackedValues() {
  //BME
  alt = BMEalt();
  updateBMEMAF(alt);
  altMAF = getBMEMAFAve();

  //LSM
  lsm.getEvent(&accel, &mag, &gyro, &temp); 
}
