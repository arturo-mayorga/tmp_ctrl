#include "pid-system.h"

void PidSystem::setup()
{
}

void PidSystem::update(unsigned long time)
{

    if (time - _lastControlerUpdate > 2000)
    {

        _state->knobPercentage = _pidController->calculate(_state->targetTemp,
                                                           _state->currentTemp,
                                                           (float)(time - _lastControlerUpdate));

        _lastControlerUpdate = time;
    }
}