//Example for performing Loop Speed analysis

unsigned long timer;
//  'unsigned long' means two things: 
//  in C, 'long' means a big integer (can store MUCH bigger numbers than 'int'). with Arduino, an 'int' uses 2 bytes. and a long uses 4 bytes.
//  'unsigned' means everything is assumed to be positive, and no negative numbers..
//    ...doing this enables you to have a lot more capacity, because you don't waste a bit to store whether the value is positive or negative.

void setup() {
  Serial.begin(9600);
  //The millis function returns the time that has passed since the program started in milliseconds. millis() returns an unsigned long, so our timer has to be an unsigned long too.
  timer = millis();
  //When starting, set timer equal to millis()
}

void loop() {
  unsigned long loopTime = millis() - timer; //time that has passed since last loop is the current 'millis()' value subtracted by the previous millis() value which we saved in 'timer'
  Serial.println("loop took " + String(loopTime) + " milliseconds."); //Print that value to the monitor
  timer = millis();  //Update the timer to be the current millis value

  //The rest of the code goes here
  
}
