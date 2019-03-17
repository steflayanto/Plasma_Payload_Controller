//Global variables 
float btemp, pressure, alt, hum; //BME
float accelX, accelY, accelZ, magX, magY, magZ, gyroX, gyroY, gyroZ, ltemp; //LSM

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
  btemp = bme.readTemperature();
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

float LSMaccelX() {
  accelX = lsm.accelData.x;
}

float LSMaccelY() {
  accelY = lsm.accelData.y;
}

float LSMaccelZ() {
  accelZ = lsm.accelData.z;
}

float LSMmagX() {
  magX = lsm.magData.x;
}

float LSMmagY() {
  magY = lsm.magData.y;
}

float LSMmagZ() {
  magZ = lsm.magData.z;
}

float LSMgyroX() {
  gyroX = lsm.gyroData.x;
}

float LSMgyroY() {
  gyroY = lsm.gyroData.Y;
}

float LSMgyroZ() {
  gyroZ = lsm.gyroData.Z;
}

float LSMtemp(){
  ltemp = lsm.temperature;
}
