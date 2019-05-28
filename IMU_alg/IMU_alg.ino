#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!


//i2c
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();

void setupSensor()
{
  // 1.) Set the accelerometer range
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_6G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_8G);
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_16G);
  
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



void setup() {

  setupCheck();
  //datalogLegend();

}


void setupCheck(){
  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  
  Serial.begin(9600);
  Serial.println("LSM raw read demo");
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS0. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS0 9DOF");
  Serial.println("");
  Serial.println("");

  }


//printing out legend for values that will be printed for data logging
void datalogLegend(){
  Serial.print("Time");
  Serial.print(", ");
  Serial.print("z-accel");
  Serial.print(", ");
  Serial.print("Flight Stage");
  Serial.print(", ");
  Serial.print("max drag");
  Serial.print(", ");
  Serial.print("x-accel");
  Serial.print(", ");
  Serial.print("y-accel");
  Serial.println();
  }



//variables
int flightStage = 0;
/*  Flight stages:
 *  0: pre-launch
 *  1: engine-burn
 *  2: early-coast-phase
 *  3: late-coast-phase
 *  4: descent
*/
double maxDrag = 0;
boolean isSafe = true;

//constants
const float noiseBuffer = 0.5; //arbitrary value for now


void loop() {
  lsm.read();

  sensors_event_t accel, mag, gyro, temp;

  lsm.getEvent(&accel, &mag, &gyro, &temp); 
  
  int xAccel = accel.acceleration.x;
  int yAccel = accel.acceleration.y;
  int zAccel = accel.acceleration.z;
  
  delay(20); //this delay value can be changed, but might lead to more/less noise
  updateMaxDrag(zAccel);
  flightStage = flightStageDecision(zAccel);
  File imuData = SD.open("imu_data.csv", FILE_WRITE);
  logData(zAccel, flightStage, maxDrag, xAccel, yAccel, imuData);

  
}


//updating the maximum drag value all flight
void updateMaxDrag(float zAccel){

  if(zAccel > maxDrag){
    maxDrag = zAccel;
    }
  
  }


//very cursory attempt at the safety cone algorithm
//dont worry about this
void safetyCone(float xAccel, float yAccel){
  int xMax = 5000; //arbitrary number for now
  int yMax = 5000; 

  if(xAccel >= xMax || yAccel >= yMax){
    isSafe = false;
    } 

  }



//not used in final program so just ignore
void plotReadings(float xAccel, float yAccel, float zAccel){
  //these print values are for testing/troubleshooting
  Serial.print(xAccel); Serial.print(", ");
  Serial.print(yAccel); Serial.print(", ");
  Serial.print(zAccel);
  }



//the main part of the program
//this algorithm determines the rocket's flight stage based on the z-acceleration reading from the IMU
float flightStageDecision(float zAccel){
  
    if(zAccel >= -9.81 - noiseBuffer && zAccel <= -9.81 + noiseBuffer){ //force of gravity //buffer is included due to possibly noise in LSM readings 
      flightStage = 0; //pre-launch, do not activate at all
    } else if(zAccel < -9.81){ // force of gravity plus engine thrust
      flightStage = 1; // burn
    } else if(zAccel >= 0 && zAccel > maxDrag/2){  //force of drag
      flightStage = 2; //early-coast, this is when we want to activate the plasma
    } else if(zAccel <= maxDrag/2 && zAccel != 0){ //force of drag, but less drag than before
      flightStage = 3; //late-coast, if plasma isn't activated yet then activate it now
    } else if(zAccel >= -noiseBuffer && zAccel <= noiseBuffer){ //feels zero Gs in free fall; same noiseBuffer as pre-launch, 
                                                                //maybe the buffer value should be different?
      flightStage = 4; //descent, do not activate at all
    }
    //to differentiate between early and late coast: after burn, save the acceleration value from the IMU
    //that acceleration value is the maximum drag that the rocket will feel during flight

    return flightStage;
 
  }
  

//output for data logging ... CSV format
//time, zAccel, flightStage, maxDrag, xAccel, yAccel
void logData(float zAccel, float flightStage, float maxDrag, float xAccel, float yAccel, File imuData){

  if(imuData){ 
    imuData.print(millis());
    imuData.print(", ");
    imuData.print(zAccel);
    imuData.print(", ");
    imuData.print(flightStage);
    imuData.print(", ");
    imuData.print(maxDrag);
    imuData.print(", ");
    imuData.print(xAccel);
    imuData.print(", ");
    imuData.print(yAccel);
    imuData.println();
    imuData.close();
  } else{
      Serial.println("error opening file");
    }
}
