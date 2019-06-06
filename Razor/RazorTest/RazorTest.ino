/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>
// <>

// unsigned long time;
// float ax, ay, az, gyrox, gyroy, gyroz, magx, magy, magz, criw, crix, criy, criz, eulerpitch, eulerr, eulery, compassh;
float dataset[18];

SoftwareSerial imuSerial(10, 11); // RX, TX
String readLine = "";
#define LENGTH = 160;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  imuSerial.begin(9600);
  //mySerial.write(' ');
}

char dataInput[160];
void parse() {
    Serial.println("Entered the parse");
    dataset[0] = atof(strtok(dataInput, ","));
    for(int i = 1; i < 18; i ++) {
      dataset[i] = atof(strtok(NULL, ","));
    }
}

int index = 0;
char incoming;
void updateData() {
  Serial.print("Enter UpdateData");
  if(imuSerial.available()) {
    incoming = imuSerial.read();
    if(incoming == '>') {
      Serial.print("Into Parse");
      index = 0;
      parse();
    } else {
      //Serial.print("Enter update");
      Serial.print(incoming);
      dataInput[index] = incoming;
      index ++;
      updateData();
    }
  }
}
void loop() { // run over and over
  // if (imuSerial.available()) {
  //   char inByte = imuSerial.read();
  //   if (inByte == '>') {
  //     if(true){//l < readLine.length()) {
  //       l = readLine.length();
  //     }
  //     Serial.println(l);
      
  //     readLine = "";
  //   }else{
  //     readLine += inByte;
  //   }
  // }
  // if (Serial.available()) {
  //   imuSerial.write(Serial.read());
  // }
  if(imuSerial.available()) {
    if(imuSerial.read() == '<') {
      updateData();
      printData();
    }
  }
  // communications();
}

void printData() {
  for(int i = 0; i < 18; i ++) {
    Serial.print(dataset[i]);
    Serial.print(",");
  }
  Serial.print("\n");
  return;
}


