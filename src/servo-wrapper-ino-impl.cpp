#include "servo-wrapper-ino-impl.h"

void ServoWrapperInoImpl::write(int value)
{
    _servo.write(value);
}

void ServoWrapperInoImpl::attach(int value)
{
    _servo.attach(value);
}
