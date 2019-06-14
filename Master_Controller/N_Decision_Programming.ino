// Contains code that goes into comparing sensor values and making decision.
int timerStage = 0;
unsigned long launchTime;
boolean launched = false;

unsigned long MAFTimer = 0;

boolean decisionAlgorithm() {
  timerStage = timerUpdate();
  weightedFlightStage = combinedSensorWeight();
  if (timerStage == 0) { //Pre-launch
    return false;
  }else if (timerStage == 4) { //descent: don't trigger if still hasn't
    return false;
  }else{
    return weightedFlightStage >= 2;
  }
}

//replace center if else with a weighted average where timer is one of the contributing factors.
//keep timer as bookends

boolean checkForLaunch() {
  if (round(weightedFlightStage) >= 1) {
    launched = true;
    return true;
  }
  return false;
}

int timerUpdate() {
  if (timerStage == 0) {
    checkForLaunch();
    return 0;
  }
  unsigned long currTime = millis() - launchTime;
  if (currTime > LATE_COAST_TIME) {
    return 4;
  }else if (currTime > EARLY_COAST_TIME) {
    return 3;
  }else if (currTime > ENGINE_BURN_TIME) {
    return 2;
  }else{
    return 1;
  }
}

float combinedSensorWeight() {
  float wt[] = {0.0, 0.5, 0.4,0.1}; // Primary, imu, baro, accel, timer respectively
  float out = (wt[0] * primaryTrigger()) + (wt[1] * imuTrigger()) + (wt[2] * baroTrigger()) + (wt[3] * timerStage);
//  Serial.print("Combined val: ");
//  Serial.println(out);
  return out;
}

//Rename to be actual parameters detected (constant acceleration)
float primaryTrigger() {
  return 1;
}

float imuTrigger() {
  if (launched) {
    updateMaxDrag(LSMaccelZ());
  }
  float out = imuDecision(LSMaccelZ());
//  Serial.print("IMU Out: ");
//  Serial.println(out);
  return out;
}

float baroTrigger() {
  float out = bmeDecision();
//  Serial.print(getBMEMAFAve());
//  Serial.print("Baro Out: ");
//  Serial.println(out);
  return out;
}
