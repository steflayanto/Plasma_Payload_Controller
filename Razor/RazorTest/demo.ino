// // simple parse demo
// char receivedChars[] = "This is a test, 1234, 45.3" ;

// char messageFromPC[32] = {0};
// int integerFromPC = 0;
// float floatFromPC = 0.0;

// char recvChar;
// char endMarker = '>';
// boolean newData = false;
// void setup() {
//  Serial.begin(9600);
//  Serial.println("<Arduino is ready>");
 
//  parseData();
//  showParsedData();
// }


// void loop() {

// }

 
// void parseData() {

//     // split the data into its parts
    
//   char * strtokIndx; // this is used by strtok() as an index
  
//   strtokIndx = strtok(receivedChars,",");      // get the first part - the string
//   strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC
  
//   strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
//   integerFromPC = atoi(strtokIndx);     // convert this part to an integer
  
//   strtokIndx = strtok(NULL, ",");
//   floatFromPC = atof(strtokIndx);     // convert this part to a float

// }


// void showParsedData() {
//  Serial.print("Message ");
//  Serial.println(messageFromPC);
//  Serial.print("Integer ");
//  Serial.println(integerFromPC);
//  Serial.print("Float ");
//  Serial.println(floatFromPC);
// }