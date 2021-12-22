#include <SoftwareSerial.h>
#define TxD 2
#define RxD 7


SoftwareSerial BTserial(RxD, TxD); // RX, TX for Bluetooth

const long baudRate = 9600; 
int r=0;
int fib_0 = 1;
int fib_1 = 0;
int c=0;
void setup() 
{
    Serial.begin(9600);
    Serial.print("Sketch:   ");   Serial.println(__FILE__);
    Serial.println(" ");
 
    BTserial.begin(baudRate);  
    Serial.print("BTserial started at "); Serial.println(baudRate);
    Serial.println(" ");
}
 
void loop()
{
  
    BTserial.write(c);
    Serial.println(c);
    
    // Read from the Bluetooth module and send to the Arduino Serial Monitor
    while (BTserial.available())
    {
        r = BTserial.read();
        Serial.print("READ: ");
        Serial.println(r);
       //fib_0 = fib_1;
        //fib_1 = r;        
    }
    delay(1000);
    c=c+1;
}
