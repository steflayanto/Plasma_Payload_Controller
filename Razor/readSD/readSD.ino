#define FACTOR 0.2f
#define LOW_BURN 10
#define LOW_EARLY 20 // equiv HIGH_BURN
#define LOW_LATE 30  // equiv HIGH_EARLY
#define HIGH_LATE 50

// Function to read a text file one field at a time.
//
#include <SPI.h>
#include <SD.h>
#define CS_PIN 4

File file;

/*
 * Read a file one field at a time.
 *
 * file - File to read.
 *
 * str - Character array for the field.
 *
 * size - Size of str array.
 *
 * delim - String containing field delimiters.
 *
 * return - length of field including terminating delimiter.
 *
 * Note, the last character of str will not be a delimiter if
 * a read error occurs, the field is too long, or the file
 * does not end with a delimiter.  Consider this an error
 * if not at end-of-file.
 *
 */
size_t readField(File* file, char* str, size_t size, char* delim) {
  char ch;
  size_t n = 0;
  while ((n + 1) < size && file->read(&ch, 1) == 1) {
    // Delete CR.
    if (ch == '\r') {
      continue;
    }
    str[n++] = ch;
    if (strchr(delim, ch)) {
        break;
    }
  }
  str[n] = '\0';
  return n;
}
//------------------------------------------------------------------------------
#define errorHalt(msg) {Serial.println(F(msg)); while(1);}
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);

  // Initialize the SD.
  if (!SD.begin(CS_PIN)) errorHalt("begin failed");

  // Create or open the file.
  file = SD.open("BME2.csv", FILE_WRITE);
  if (!file) errorHalt("open failed");

  // Rewind file so test data is not appended.
  file.seek(0);


  size_t n;      // Length of returned field with delimiter.
  char str[20];  // Must hold longest field with delimiter and zero byte.
  
  // Read the file and print fields.
  int count = 0;
  while (true) {
    n = readField(&file, str, sizeof(str), ",\n");
    if (n == 0) break;
    // Print the type of delimiter.
    char end = ',';
    if (str[n-1] == ',' || str[n-1] == '\n') {
      if (str[n-1] != ',') {
        end = '\n';
        count = 0;
      }
      str[n-1] = end;
    } else {
      // At eof, too long, or read error.  Too long is error.
      Serial.print(file.available() ? F("error: ") : F("eof:   "));
    }
    // Print the field.
    if (count == 4) {
      str[n-1] = 0;
      float value = String(str).toFloat();
      Serial.print(value);
      Serial.print(", ");
      Serial.println(bmeDecision(value));
    }
    count++;
  }
  file.close();
}
//------------------------------------------------------------------------------
void loop() {
}
float bmeDecision(float alt) {
  //map to flight stages, mapping
  if (alt < LOW_BURN) {
    return 0;
  } else {
    //w/o throttle, burn = 10 sec = 10000 ft
    //1 burn
    if (alt < LOW_EARLY) {
      return mapFloat(constrain(alt, LOW_BURN, LOW_EARLY), LOW_BURN, LOW_EARLY, 1 - FACTOR, 1 + FACTOR);
    } else if (alt < LOW_LATE) {
      //2 early coast
      return mapFloat(constrain(alt, LOW_EARLY, LOW_LATE), LOW_EARLY, LOW_LATE, 2 - FACTOR, 2 + FACTOR);
    } else if (alt < HIGH_LATE) {
      //3 late coast
      return mapFloat(constrain(alt, LOW_LATE, HIGH_LATE), LOW_LATE, HIGH_LATE, 3 - FACTOR, 3 + FACTOR);
    } else {
      //4 decent = 26067 and down
      return 4.0;//map(alt, 100, 1000, 3, 4);
    }
  }
}
