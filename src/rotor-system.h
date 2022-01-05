#ifndef rotor_system_h
#define rotor_system_h

#include "app-system.h"
#include "i-digital-pin-wrapper.h"

class RotorSystem : public AppSystem
{
private:
    IDigitalPinWrapper *_pinWrapper;
    int _clkPin;
    int _clkPinMode;
    int _dtPin;
    int _dtPinMode;
    int _swPin;
    int _swPinMode;

    int _clkValue;
    int _swState;

public:
    RotorSystem(AppState *state, ILogger *logger, IDigitalPinWrapper *pinWrapper, int clk_pin, int clk_pin_mode, int dt_pin, int dt_pin_mode, int sw_pin, int sw_pin_mode) : AppSystem(state, logger)
    {
        _clkPin = clk_pin;
        _clkPinMode = clk_pin_mode;
        _dtPin = dt_pin;
        _dtPinMode = dt_pin_mode;
        _swPin = sw_pin;
        _swPinMode = sw_pin_mode;
        _pinWrapper = pinWrapper;
    }

    virtual void setup();
    virtual void update(unsigned long time);
};

#endif