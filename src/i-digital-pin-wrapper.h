#ifndef i_digital_pin_wrapper_h
#define i_digital_pin_wrapper_h

class IDigitalPinWrapper
{
public:
    virtual void pinMode(int pin, int mode) = 0;
    virtual bool digitalRead(int port) = 0;
};

#endif