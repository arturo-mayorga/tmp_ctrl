#include <SoftwareSerial.h>
#define TxD 2
#define RxD 7


SoftwareSerial BTserial(RxD, TxD); // RX, TX for Bluetooth

const long baudRate = 38400; 
char c=' ';
boolean NL = true;
 
void setup() 
{
    Serial.begin(9600);
    Serial.print("Sketch:   ");   Serial.println(__FILE__);
    Serial.print("Uploaded: ");   Serial.println(__DATE__);
    Serial.println(" ");
 
    BTserial.begin(baudRate);  
    Serial.print("BTserial started at "); Serial.println(baudRate);
    Serial.println(" ");
}
 
void loop()
{
 
    // Read from the Bluetooth module and send to the Arduino Serial Monitor
    if (BTserial.available())
    {
        c = BTserial.read();
        Serial.write(c);
    }
 
 
    // Read from the Serial Monitor and send to the Bluetooth module
    if (Serial.available())
    {
        c = Serial.read();
        BTserial.write(c);   
 
        // Echo the user input to the main window. The ">" character indicates the user entered text.
        if (NL) { Serial.print(">");  NL = false; }
        Serial.write(c);
        if (c==10) { NL = true; }
    }
 
}



/*

SoftwareSerial mySerial(RxD, TxD); // RX, TX for Bluetooth
int state = 1;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  mySerial.begin(38400); // Default communication rate of the Bluetooth module
  Serial.begin(38400); 
  Serial.println("START");
  //delay(3000);
  //mySerial.write("AT\r\n");
  //readAndEcho();
  Serial.println("SENT");
}
void readAndEcho(){
  while(mySerial.available() > 0){ // Checks whether data is comming from the serial port
    state = mySerial.read(); // Reads the data from the serial port
    Serial.write(state);
  }
}
void sendAndEcho(char* command){
  mySerial.write(command);
  Serial.print(">");
  Serial.println(command);
}
void loop() {
  sendAndEcho("AT\r\n");
  readAndEcho();
  delay(3000);
  
// if (state == '0') {
//  digitalWrite(LED_BUILTIN, LOW); // Turn LED OFF
//  mySerial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
//  state = 0;
// }
// else if (state == '1') {
//  digitalWrite(LED_BUILTIN, HIGH);
//  mySerial.println("LED: ON");
//  state = 0;
// } 
}
*/
