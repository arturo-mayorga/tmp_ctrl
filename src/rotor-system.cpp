#include "rotor-system.h"

void RotorSystem::setup()
{
    _pinWrapper->pinMode(_clkPin, _clkPinMode);
    _pinWrapper->pinMode(_dtPin, _dtPinMode);
    _pinWrapper->pinMode(_swPin, _swPinMode);
}

void RotorSystem::update(unsigned long time)
{
    int value = _pinWrapper->digitalRead(_clkPin);
    if (value != _clkValue)
    {
        // we use the DT pin to find out which way we turning.
        if ((int)_pinWrapper->digitalRead(_dtPin) != value)
        {
            // Clockwise
            _state->targetTemp += 0.5f;
        }
        else
        {
            //Counterclockwise
            _state->targetTemp -= 0.5f;
        }

        _state->input.inputKnobTime = time;
    }
    _clkValue = value;

    int swIn = _pinWrapper->digitalRead(_swPin);
    if (swIn != _swState)
    {
        _swState = swIn;
        if (swIn)
        {
            // SW Up
        }
        else
        {
            // SW Down
        }
        _state->input.inputButtonTime = time;
    }
}
