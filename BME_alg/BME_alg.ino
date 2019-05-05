#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

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
  //variables
//  float factor = 0.2;
//  int lowBurn = 100;
//  int highBurn = 15000;
//  int lowEarly = 15000;
//  int highEarly = 21350;
//  int lowLate = 21350;
//  int highLate = 27067; 

//test alt from my bed
  float factor = 0;
  int lowBurn = 22;
  int highBurn = 22.5;
  int lowEarly = 22.5;
  int highEarly = 23;
  int lowLate = 23;
  int highLate = 23.5; 
  
  //map to flight stages, mapping
  if (alt < lowBurn){
    return 0;
  } else{
    //w/o throttle, burn = 10 sec = 10000 ft
    //1 burn
    if (alt < highBurn){
      return map(constrain(alt, lowBurn, highBurn), lowBurn, highBurn, 1 - factor, 1 + factor);
    }else if(alt < highEarly) {
    //2 early coast
      return map(constrain(alt, lowEarly, highEarly), lowEarly, highEarly, 2 - factor, 2 + factor);
    } else if(alt < highLate) {
    //3 late coast
      return map(constrain(alt, lowLate, highLate), lowLate, highLate, 3 - factor, 3 + factor);
    } else{
    //4 decent = 26067 and down
      return map(alt, 100, 1000, 3, 4);
    }  
}
}
