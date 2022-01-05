#ifndef app_system_h
#define app_system_h

#include "app-state.h"
#include "i-logger.h"

class AppSystem
{
protected:
    AppState *_state;
    ILogger *_logger;

public:
    virtual void setup() = 0;
    virtual void update(unsigned long time) = 0; // Time in milliseconds

protected:
    AppSystem(AppState *state, ILogger *logger)
    {
        _state = state;
        _logger = logger;
    };
};

#endif