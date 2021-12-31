#ifndef digital_pin_wrapper_ino_impl_h
#define digital_pin_wrapper_ino_impl_h

#include "i-digital-pin-wrapper.h"


class DigitalPinWrapperInoImpl : public IDigitalPinWrapper
{

public:
    virtual void pinMode(int pin, int mode);
    virtual bool digitalRead(int port);
};

#endif