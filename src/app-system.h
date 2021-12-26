#ifndef app_system_h
#define app_system_h

#include "app-state.h"

class AppSystem
{
protected:
    AppState *_state;

public:
    virtual void setup() = 0;
    virtual void update(unsigned long time) = 0; // Time in milliseconds

protected:
    AppSystem(AppState *state)
    {
        _state = state;
    };
};

#endif