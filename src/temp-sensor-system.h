#ifndef temp_sensor_system_h
#define temp_sensor_system_h

#include "app-system.h"

class TempSensorSystem : public AppSystem
{
public:
    virtual void setup();
    virtual void update(unsigned long time); // Time in milliseconds
};

#endif