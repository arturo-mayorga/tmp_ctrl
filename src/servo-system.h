#ifndef servo_system_h
#define servo_system_h

#include "app-system.h"
#include "app-state.h"
#include "i-servo-wrapper.h"

class ServoSystem : public AppSystem
{
private:
    IServoWrapper *_servoWrapper;
    int _servoPin;

public:
    ServoSystem(AppState *state, ILogger *logger, IServoWrapper *pidController, int servoPin) : AppSystem(state, logger)
    {
        _servoWrapper = pidController;
        _servoPin = servoPin;
    }

    virtual void setup();
    virtual void update(unsigned long time); // Time in milliseconds
};

#endif
