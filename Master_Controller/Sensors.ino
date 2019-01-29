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

void initMPU() {
  Serial.println("Setting up MPU9250 IMU... ");
  if (mpu.begin() != INV_SUCCESS) {
    Serial.println("ERROR: Unable to intialize MPU.")
    while(1);
  }
  imu.setSensors(INV_XYZ_GYRO | INV_XYZ_ACCEL | INV_XYZ_COMPASS);
  // There are functions for range and sample rate on gyro/accel
  // mpu.setSampleRate(hz); // Controls gyro and accel 4hz-1KHz
  // mpu.setCompassSampleRate(hz); // Magnetometer 1-100hz
  // mpu.setAccelFSR(value); // +/- 2, 4, 8, 16g
  // mpu.setGyroFSR(value); // +/- 250, 500, 1000, 2000 dps
}