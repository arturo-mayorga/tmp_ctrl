#ifndef ssd_wrapper_ino_impl_h
#define ssd_wrapper_ino_impl_h

#include "i-ssd-wrapper.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class SsdWrapperInoImpl : public ISsdWrapper
{
private:
    Adafruit_SSD1306 *_display;

public:
    SsdWrapperInoImpl(uint16_t w, uint16_t h)
    {
        _display = new Adafruit_SSD1306(w, h, &Wire);
    }

    virtual bool begin(uint8_t switchvcc, uint8_t i2caddr);
    virtual void clearDisplay();
    virtual void setTextSize(uint8_t s);
    virtual void setTextColor(uint16_t c);
    virtual void setCursor(int16_t x, int16_t y);
    virtual void println(const char *str);
    virtual void print(const char *str);
    virtual void print(uint16_t v);
    virtual void display();
};

#endif