#ifndef pid_system_h
#define pid_system_h

#include "app-system.h"
#include "app-state.h"
#include "pid-controller.h"

class PidSystem : public AppSystem
{
    private:
    PidController *_pidController;
    unsigned long _lastControlerUpdate;
public:
    PidSystem(AppState *state, ILogger *logger, PidController *pidController) : AppSystem(state, logger)
    {
        _pidController = pidController;
        _lastControlerUpdate = 0;
    }

    virtual void setup();
    virtual void update(unsigned long time); // Time in milliseconds
};

#endif
