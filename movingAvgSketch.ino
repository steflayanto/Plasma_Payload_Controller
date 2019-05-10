
const int samples = 5; // number of samples for the running avg

int inputs[samples];
int index = 0;
int avg = 0;
int total = 0;
int inputPin = 0; // this 


void setup() {

  Serial.begin(9600);

  // initialize input array to 0
  for (int i = 0; i < samples; i++) {
    inputs[i] = 0;
  }
}

void loop() {
  total = total - inputs[index];
  inputs[index] = analogRead(inputPin); // placeholder
  total += inputs[index];
  index = (index + 1) % samples;

//  // reset when we reach the end of the array
//  if (index >= samples) {
//    index = 0;
//  }

  avg = total / samples; // input for second derivative function
  Serial.println(avg);
  delay(1); // change the delay as needed
 
  }
  
