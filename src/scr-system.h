#ifndef scr_system_h
#define scr_system_h

#include "app-system.h"

#include "i-ssd-wrapper.h"

class ScrSystem : public AppSystem
{
private:
    ISsdWrapper *_scrDevice;
    unsigned long _lastUpdateTime;

public:
    ScrSystem(AppState *state, ISsdWrapper *scrDevice) : AppSystem(state)
    {
        _scrDevice = scrDevice;
        _lastUpdateTime = 0;
    }
    virtual void setup();
    virtual void update(unsigned long time); // Time in milliseconds
};

#endif