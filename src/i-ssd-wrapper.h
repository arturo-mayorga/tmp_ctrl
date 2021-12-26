#ifndef i_ssd_wrapper_h
#define i_ssd_wrapper_h

#include <stdint.h>

class ISsdWrapper
{
    virtual bool begin(uint8_t switchvcc, uint8_t i2caddr) = 0;
    virtual void clearDisplay() = 0;
    virtual void setTextSize(uint8_t s) = 0;
    virtual void setTextColor(uint16_t c) = 0;
    virtual void setCursor(int16_t x, int16_t y) = 0;
    virtual void println(const char * str) = 0;
    virtual void print(const char * str) = 0;
    virtual void print(uint16_t v) = 0;
    virtual void display() = 0;
};

#endif