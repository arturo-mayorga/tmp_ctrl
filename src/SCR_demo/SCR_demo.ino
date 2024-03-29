#include "ssd-wrapper-ino-impl.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

SsdWrapperInoImpl display(SCREEN_WIDTH, SCREEN_HEIGHT);

void setup()
{

    Serial.begin(38400);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {

        Serial.println(F("SSD1306 Allocation Failed"));

        for (;;)
            ;
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Hello 128×32 OLED");
    display.setTextSize(3);
    display.println("T 70`F");
    display.display();
}

void loop()
{
}
