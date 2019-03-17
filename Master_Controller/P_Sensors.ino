//Global var
float temp, pressure, alt, hum;

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

void initBME() {
  //in setup
  Serial.begin(9600);
  Serial.println(F("BME280 test"));

  bool status;

  status = bme.begin();
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

}

float BMEtemp() {
  temp = bme.readTemperature();
}

float BMEpressure() {
  pressure = bme.readPressure() / 100.0F; //hPa
}

float BMEalt() {
  alt = bme.readAltitude(SEALEVELPRESSURE_HPA);
}

float BMEhum() {
  hum = bme.readHumidity();
}
