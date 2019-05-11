#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

//variables
//  float FACTOR = 0.2;
//  int LOW_BURN = 100;
//  int HIGH_BURN = 15000;
//  int LOW_EARLY = 15000;
//  int HIGH_EARLY = 21350;
//  int LOW_LATE = 21350;
//  int HIGH_LATE = 27067; 

//  test alt from my bed
//  float FACTOR = 0;
//  int LOW_BURN = 22;
//  int HIGH_BURN = 22.5;
//  int LOW_EARLY = 22.5;
//  int HIGH_EARLY = 23;
//  int LOW_LATE = 23;
//  int HIGH_LATE = 23.5;

#define FACTOR 0
#define LOW_BURN 22
#define HIGH_BURN 22.5
#define LOW_EARLY 22.5
#define HIGH_EARLY 23
#define LOW_LATE 23
#define HIGH_LATE 23.5

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

float alt;

void setup() {
    Serial.begin(9600);
    Serial.println(F("BME280 test"));
    bool status;
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    status = bme.begin();  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
    Serial.println();
}

void loop() {
  alt = bme.readAltitude(SEALEVELPRESSURE_HPA);
  //Serial.println(alt); 
  Serial.println(bmeDecision()); 
}

int bmeDecision(){
  //map to flight stages, mapping
  if (alt < LOW_BURN){
    return 0;
  } else{
    //w/o throttle, burn = 10 sec = 10000 ft
    //1 burn
    if (alt < HIGH_BURN){
      return map(constrain(alt, LOW_BURN, HIGH_BURN), LOW_BURN, HIGH_BURN, 1 - FACTOR, 1 + FACTOR);
    }else if(alt < HIGH_EARLY) {
    //2 early coast
      return map(constrain(alt, LOW_EARLY, HIGH_EARLY), LOW_EARLY, HIGH_EARLY, 2 - FACTOR, 2 + FACTOR);
    } else if(alt < HIGH_LATE) {
    //3 late coast
      return map(constrain(alt, LOW_LATE, HIGH_LATE), LOW_LATE, HIGH_LATE, 3 - FACTOR, 3 + FACTOR);
    } else{
    //4 decent = 26067 and down
      return map(alt, 100, 1000, 3, 4);
    }  
}
}
