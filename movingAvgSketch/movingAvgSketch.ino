//This constant and struct are all that is needed for the MAF
#define MAF_SIZE 5 // number of samples for the running avg
struct {
  float total;
  float arr[MAF_SIZE];
  int index;
} filter;

void setup() {
  Serial.begin(9600);
  initMAF();
}

void loop() {
  updateMAF(sin(millis()/1000));
  Serial.println(getMAFAve());
  delay(1); // change the delay as needed
}
