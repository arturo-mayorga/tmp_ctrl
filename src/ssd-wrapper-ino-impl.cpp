#include "ssd-wrapper-ino-impl.h"
#include <Arduino.h>


bool SsdWrapperInoImpl::begin(uint8_t switchvcc, uint8_t i2caddr)
{
    Serial.println("begin ssdwrapper");
    Serial.print(switchvcc);
    Serial.print("  ");
    Serial.print(i2caddr);
    Serial.println("");
    return _display->begin(SSD1306_SWITCHCAPVCC, i2caddr);
}
void SsdWrapperInoImpl::clearDisplay()
{
    _display->clearDisplay();
}
void SsdWrapperInoImpl::setTextSize(uint8_t s)
{
    _display->setTextSize(s);
}
void SsdWrapperInoImpl::setTextColor(uint16_t c)
{
    _display->setTextColor(c);
}
void SsdWrapperInoImpl::setCursor(int16_t x, int16_t y)
{
    _display->setCursor(x, y);
}
void SsdWrapperInoImpl::println(const char *str)
{
    _display->println(str);
}
void SsdWrapperInoImpl::print(const char * str)
{
    _display->print(str);
}
void  SsdWrapperInoImpl::print(uint16_t v)
{
    _display->print(v);
}
void SsdWrapperInoImpl::display()
{
    _display->display();
}