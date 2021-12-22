#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

// Data wire is plugged into pin 2 on the Arduino
#define TEMP_ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire tempOneWire(TEMP_ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature tempSensor(&tempOneWire);

int tempReading = 0;

void setup()
{

    tempSensor.begin();

    Serial.begin(9600);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {

        Serial.println(F("SSD1306 Allocation Failed"));

        for (;;)
            ;
    }

    drawTemp();
}

void drawTemp()
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Hello 128×32 OLED");
    display.setTextSize(3);
    display.print("T ");
    if (tempReading < 100)
    {
        display.print(" ");
    }
    if (tempReading < 10)
    {
        display.print(" ");
    }
    display.print(tempReading);
    display.println("`F");
    display.display();
}

void loop()
{
    tempSensor.requestTemperatures();
    Serial.print("Temperature is: ");

    tempReading = tempSensor.getTempFByIndex(0);
    Serial.println(tempReading);
    drawTemp();
}
