#ifndef app_system_h
#define app_system_h

#include "app-state.h"

class AppSystem
{
protected:
    AppState *_state;

public:
    AppSystem(AppState *state)
    {
        _state = state;
    };

    virtual void setup() = 0;
    virtual void update(unsigned long time) = 0; // Time in milliseconds
};

#endif