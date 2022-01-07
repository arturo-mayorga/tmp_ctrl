#include "temp-sensor-system.h"

#define CYCLE_LEN 200000

#define SCREEN_HIDE_DELAY 4000

void TempSensorSystem::setup()
{
    _dallasTempW->begin();
    _logger->println("temp-sensor-system: Ready");
}
void TempSensorSystem::update(unsigned long time)
{
    int lastNumCycles = _lastUpdateTime / 2000;
    int numCycles = time / 2000;
    if (numCycles - lastNumCycles >= 1 &&
        time - _state->input.inputButtonTime > SCREEN_HIDE_DELAY &&
        time - _state->input.inputKnobTime > SCREEN_HIDE_DELAY)
    {
        _lastUpdateTime = time;
        _dallasTempW->requestTemperatures();
        _state->currentTemp = _dallasTempW->getTempFByIndex(0);
    }
}