#ifndef i_servo_wrapper_h
#define i_servo_wrapper_h

class IServoWrapper
{
public:
    virtual void write(int value) = 0;
    virtual void attach(int value) = 0;
};

#endif