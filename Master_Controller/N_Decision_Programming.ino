// Contains code that goes into comparing sensor values and making decision.
int timerStage = 0;
unsigned long launchTime;
boolean launched = false;
unsigned long MAFTimer = 0;
float wt[] = {0.5, 0.5,0.0}; // imu, baro, timer respectively. Initial Settings!
//Burn phase wt[] = {0.05, 0.7, 0.25} // imu, baro, timer respectively
//Coast Phase wt[] = {0.35, 0.55, 0.1} // imu, baro, timer respectively

boolean decisionAlgorithm() {
  if (round(weightedFlightStage) == 0) {
    //wt[] = {0.5, 0.5,0.0};
    wt[0] = 0.5;
    wt[1] = 0.5;
    wt[2] = 0.0;
  }else if (round(weightedFlightStage) == 1) {
    //wt[] = {0.05, 0.7, 0.25};
    wt[0] = 0.05;
    wt[1] = 0.7;
    wt[2] = 0.25;
  }else if (round(weightedFlightStage) == 2 || round(weightedFlightStage) == 3) {
    //wt[] = {0.35, 0.55, 0.1};
    wt[0] = 0.35;
    wt[1] = 0.55;
    wt[2] = 0.1;
  }else if (round(weightedFlightStage) == 4) {
    //wt[] = {0.5, 0.5,0.0};
    wt[0] = 0.5;
    wt[1] = 0.5;
    wt[2] = 0.0;
  }
  timerStage = timerUpdate();
  weightedFlightStage = combinedSensorWeight();
  if (timerStage == 0) { //Pre-launch
    dangerAngle = 10; //needed for safety while the rocket is being raised
    noiseBuffer = 15;
    return false;
  }else if (timerStage == 4) { //descent: don't trigger if still hasn't
    dangerAngle = 33; //Greater allowance while in flight
    noiseBuffer = 4;
    return false;
  }else{
    noiseBuffer = 4;
    dangerAngle = 33; //Greater allowance while in flight
    return weightedFlightStage >= 3;
  }
}

//replace center if else with a weighted average where timer is one of the contributing factors.
//keep timer as bookends

boolean checkForLaunch() {
  if (round(weightedFlightStage) >= 1) {
    launched = true;
    launchTime = millis();
    return true;
  }
  return false;
}

int timerUpdate() {
  if (timerStage == 0) { //if presently on ground
    return checkForLaunch();
  }
  unsigned long currTime = millis() - launchTime;
  Serial.println(currTime);
  if (currTime > LATE_COAST_TIME * 1000) {
    return 4;
  }else if (currTime > EARLY_COAST_TIME * 1000) {
    return 3;
  }else if (currTime > ENGINE_BURN_TIME * 1000) {
    return 2;
  }else{
    return 1;
  }
}

float combinedSensorWeight() {
  float out = (wt[0] * imuTrigger()) + (wt[1] * baroTrigger()) + (wt[2] * timerStage);
  printDecisionInfo(out);
  //Serial.println(LSMaccelZ());
  return out;
}

void printDecisionInfo(float combined) {
  Serial.print("IMU: ");
  Serial.println(imuTrigger());
  Serial.print("BME: ");
  Serial.println(baroTrigger());
  Serial.print("Timer: ");
  Serial.println(timerStage);
  Serial.print("Combined: ");
  Serial.println(combined);
  if (launched) {
    Serial.println("Launched");
  }
  if (activated) {
    Serial.println("Already Activated");
  }
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
