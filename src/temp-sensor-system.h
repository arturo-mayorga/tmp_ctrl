#ifndef temp_sensor_system_h
#define temp_sensor_system_h

#include "app-system.h"

#include "i-dallas-temperature-wrapper.h"

class TempSensorSystem : public AppSystem
{
private:
    IDallasTemperatureWrapper *_dallasTempW;
    unsigned long _lastUpdateTime;

public:
    TempSensorSystem(AppState *state, IDallasTemperatureWrapper *dallasTempW) : AppSystem(state)
    {
        _dallasTempW = dallasTempW;
        _lastUpdateTime = 0;
    }
    virtual void setup();
    virtual void update(unsigned long time); // Time in milliseconds
};

#endif