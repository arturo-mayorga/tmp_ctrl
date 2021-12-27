#ifndef temp_sensor_system_h
#define temp_sensor_system_h

#include "app-system.h"

#include "i-ssd-wrapper.h"

class TempSensorSystem : public AppSystem
{
private:
    ISsdWrapper *_issd;

public:
    TempSensorSystem(AppState *state, ISsdWrapper *issd) : AppSystem(state)
    {
        _issd = issd;
    }
    virtual void setup();
    virtual void update(unsigned long time); // Time in milliseconds
};

#endif