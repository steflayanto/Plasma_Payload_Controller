void initTempSens() {
  tempSens.begin();
  Serial.print("TempSensor Initialized");
}

// SETUP Code
void initLSM() {
  Serial.print("Setting up LSM9DS0 IMU... ");
  if (!lsm.begin()) {
    Serial.println("ERROR: Unable to initialize sensor. Check wiring.");
    while (1);
  }
  Serial.println("Success.");

  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_6G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_16G);

  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_12GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_2000DPS);
}



float tempSensTemp() {
  return tempSens.readTempF();
}

float LSMaccelX() {
  return lsm.accelData.x;
}

float LSMaccelY() {
  return  lsm.accelData.y;
}

float LSMaccelZ() {
  return lsm.accelData.z;
}

float LSMmagX() {
  return lsm.magData.x;
}

float LSMmagY() {
  return lsm.magData.y;
}

float LSMmagZ() {
  return lsm.magData.z;
}

float LSMgyroX() {
  return lsm.gyroData.x;
}

float LSMgyroY() {
  return lsm.gyroData.y;
}

float LSMgyroZ() {
  return lsm.gyroData.z;
}

float LSMtemp(){
  return lsm.temperature;
}

int readCircuit() {
  return analogRead(A0);
}