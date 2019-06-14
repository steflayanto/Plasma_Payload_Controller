//Adam Norgaard
double maxDrag = 0;
const float noiseBuffer = 1.0; //arbitrary value for now

//updating the maximum drag value all flight
void updateMaxDrag(float zAccel) {
  if (zAccel > maxDrag) {
    maxDrag = zAccel;
  }
}

//the main part of the program
//this algorithm determines the rocket's flight stage based on the z-acceleration reading from the IMU
float imuDecision(float zAccel) {
  float flightStage = 2;
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
  //Serial.print(zAccel); Serial.print("\t"); Serial.println(flightStage);
  return flightStage;
}

float LSMaccelX() {  return accel.acceleration.x;}

float LSMaccelY() {  return accel.acceleration.y;}

float LSMaccelZ() {  return accel.acceleration.z;}

float LSMmagX() {  return mag.magnetic.x;}

float LSMmagY() {  return mag.magnetic.y;}

float LSMmagZ() {  return mag.magnetic.z;}

float LSMgyroX() {  return gyro.gyro.x;}

float LSMgyroY() {  return gyro.gyro.y;}

float LSMgyroZ() {  return gyro.gyro.z;}

float LSMtemp(){  return temp.temperature;}
