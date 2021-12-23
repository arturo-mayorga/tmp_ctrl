
int CLK = 7; 
int DT = 4; 
int SW = 8;

int RotPosition = 0;
int swState = 1;
int rotation;
int value;
boolean LeftRight;
void setup()
{
    Serial.begin(38400);
    pinMode(CLK, INPUT);
    pinMode(DT, INPUT);
    pinMode(SW, INPUT_PULLUP);

    rotation = digitalRead(CLK);

    Serial.println("READY ******");
}
void loop()
{
    value = digitalRead(CLK);
    if (value != rotation)
    { // we use the DT pin to find out which way we turning.
        if (digitalRead(DT) != value)
        { // Clockwise
            RotPosition++;
            LeftRight = true;
        }
        else
        { //Counterclockwise
            LeftRight = false;
            RotPosition--;
        }
        if (LeftRight)
        { // turning right will turn on red led.
            Serial.println("clockwise");
        }
        else
        { // turning left will turn on green led.
            Serial.println("counterclockwise");
        }
        Serial.print("Encoder RotPosition: ");
        Serial.println(RotPosition);
        // this will print in the serial monitor.
    }
    rotation = value;

    int swIn = digitalRead(SW);
    if (swIn != swState) {
        swState = swIn;
        if (swIn) {
            Serial.println("SW Up");
        } else {
            Serial.println("SW Down");
        }
    }
}
