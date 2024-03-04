/* UART Example, any character received on either the real
   serial port, or USB serial (or emulated serial to the
   Arduino Serial Monitor when using non-serial USB types)
   is printed as a message to both ports.
*/

// set this to the hardware serial port you wish to use
//#define HWSERIAL Serial1

const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data
String message;
float period;
unsigned long startMillis;

boolean newData = false;

void setup() {
	Serial.begin(9600);
  period = 10.0;
//	HWSERIAL.begin(38400);
  startMillis = millis();
}

void loop() {
  recvWithEndMarker();
  showNewData();
//  PrintWave();
  delay(50);
}

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
 
  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();
  
    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void showNewData() {
  if (newData == true) {
    message = String(receivedChars);
    if (message.compareTo("Hello") == 0 ){
      Serial.println("Hello to you too");
    }
    if (message.compareTo("Wave") == 0){
      PrintWave();
    }
    newData = false;
  }
}

void PrintWave(){
  Serial.println(sin((float)(millis()-startMillis)/1000.0 * 6.28 / period ));
}
