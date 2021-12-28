#include "temp-sensor-system.h"

#define CYCLE_LEN 2000

void TempSensorSystem::setup()
{
    _dallasTempW->begin();
}
void TempSensorSystem::update(unsigned long time)
{
    int lastNumCycles = _lastUpdateTime / 2000;
    int numCycles = time / 2000;
    if (numCycles - lastNumCycles >= 1)
    {
        _lastUpdateTime = time;
        _dallasTempW->requestTemperatures();
        _state->currentTemp = _dallasTempW->getTempFByIndex(0);
    }
}