#include "digital-pin-wapper-ino-impl.h"

// these functions are to avoid scope confusion
// when calling the standard arduino pin functions

void wPinMode(int pin, int mode)
{
    pinMode(pin, mode);
}

bool wDigitalRead(int port)
{
    return digitalRead(port);
}

void DigitalPinWrapperInoImpl::pinMode(int pin, int mode)
{
    wPinMode(pin, mode);
}
bool DigitalPinWrapperInoImpl::digitalRead(int port)
{
    return wDigitalRead(port);
}
