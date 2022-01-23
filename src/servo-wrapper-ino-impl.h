#ifndef servo_wrapper_ino_impl_h
#define servo_wrapper_ino_impl_h

#include "i-servo-wrapper.h"
#include <Servo.h>

class ServoWrapperInoImpl : public IServoWrapper
{
private:
    Servo _servo;

public:
    virtual void write(int value);
    virtual void attach(int value);
};

#endif