#include <SoftwareSerial.h>
#define TxD 2
#define RxD 7

SoftwareSerial mySerial(RxD, TxD); // RX, TX for Bluetooth


int state = 1;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  mySerial.begin(9600); // Default communication rate of the Bluetooth module
  Serial.begin(9600); 
  Serial.println("START");
}
void loop() {
  if(mySerial.available() > 0){ // Checks whether data is comming from the serial port
    Serial.println("READ");
    state = mySerial.read(); // Reads the data from the serial port
    Serial.println((char)state);
 }
 if (state == '0') {
  digitalWrite(LED_BUILTIN, LOW); // Turn LED OFF
  mySerial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
  state = 0;
 }
 else if (state == '1') {
  digitalWrite(LED_BUILTIN, HIGH);
  mySerial.println("LED: ON");
  state = 0;
 } 
}
