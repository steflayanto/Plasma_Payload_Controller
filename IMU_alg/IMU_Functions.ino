//Setup
void setupLSM() { //Blocks execution if fails
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS0. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS0 9DOF");
  setupSensor();
}

void setupSensor()
{
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

// Logging/Plotting
//printing out legend for values that will be printed for data logging
void printLegend() {
  File dataFile = SD.open(file_name, FILE_WRITE);
  if (dataFile) {
    dataFile.println();
    dataFile.print("Time");
    dataFile.print(",");
    dataFile.print("z-accel");
    dataFile.print(",");
    dataFile.print("Flight Stage");
    dataFile.print(",");
    dataFile.print("max drag");
    dataFile.print(",");
    dataFile.print("x-accel");
    dataFile.print(",");
    dataFile.print("y-accel");
    dataFile.println();
    dataFile.close();
    Serial.println("Time, z-accel, Flight Stage, max drag, x-accel, y-accel");
  } else { // if the file isn't open, pop up an error:
    Serial.println("error opening file.csv for legend");
  }
}

//output for data logging ... CSV format
//time, zAccel, flightStage, maxDrag, xAccel, yAccel
void logData(float zAccel, float flightStage, float maxDrag, float xAccel, float yAccel) {
  File dataFile = SD.open(file_name, FILE_WRITE);
  if (dataFile) {
    dataFile.print(millis() - startTime);
    dataFile.print(",");
    dataFile.print(zAccel);
    dataFile.print(",");
    dataFile.print(flightStage);
    dataFile.print(",");
    dataFile.print(maxDrag);
    dataFile.print(",");
    dataFile.print(xAccel);
    dataFile.print(",");
    dataFile.print(yAccel);
    dataFile.println();
    dataFile.close();
  } else {
    Serial.println("Error opening file for logging");
  }
}

//not used in final program so just ignore
void plotReadings(float xAccel, float yAccel, float zAccel) {
  //these print values are for testing/troubleshooting
  Serial.print(xAccel); Serial.print(", ");
  Serial.print(yAccel); Serial.print(", ");
  Serial.print(zAccel); Serial.println();
}

//Everything else

//updating the maximum drag value all flight
void updateMaxDrag(float zAccel) {
  if (zAccel > maxDrag) {
    maxDrag = zAccel;
  }
}

//very cursory attempt at the safety cone algorithm
//dont worry about this
void safetyCone(float xAccel, float yAccel) {
  int xMax = 5000; //arbitrary number for now
  int yMax = 5000;

  if (xAccel >= xMax || yAccel >= yMax) {
    isSafe = false;
  }
}


//the main part of the program
//this algorithm determines the rocket's flight stage based on the z-acceleration reading from the IMU
float flightStageDecision(float zAccel) {

  if (zAccel >= -9.81 - noiseBuffer && zAccel <= -9.81 + noiseBuffer) { //force of gravity //buffer is included due to possibly noise in LSM readings
    flightStage = 0; //pre-launch, do not activate at all
  } else if (zAccel < -9.81) { // force of gravity plus engine thrust
    flightStage = 1; // burn
  } else if (zAccel >= 0 && zAccel > maxDrag / 2) { //force of drag
    flightStage = 2; //early-coast, this is when we want to activate the plasma
  } else if (zAccel <= maxDrag / 2 && zAccel != 0) { //force of drag, but less drag than before
    flightStage = 3; //late-coast, if plasma isn't activated yet then activate it now
  } else if (zAccel >= -noiseBuffer && zAccel <= noiseBuffer) { //feels zero Gs in free fall; same noiseBuffer as pre-launch,
    //maybe the buffer value should be different?
    flightStage = 4; //descent, do not activate at all
  }
  //to differentiate between early and late coast: after burn, save the acceleration value from the IMU
  //that acceleration value is the maximum drag that the rocket will feel during flight

  return flightStage;
}
