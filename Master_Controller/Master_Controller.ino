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
  updateSensors();
  transmitToLogger();
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
}

//Performs all sensor updates
void updateSensors() {
  updateLSM();
  updateBME();  
}

//Interacts with slave logger device
void transmitToLogger() {
  
}

//Decides whether to activate plasma (Stefan, Lexie, & Usman)
boolean checkTriggerConditions() {
  //Code will consider sensor data and flight stage and make a decision
  return true;
}
