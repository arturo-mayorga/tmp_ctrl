#ifndef dallas_temperature_wrapper_ino_impl_h
#define dallas_temperature_wrapper_ino_impl_h

#include "i-dallas-temperature-wrapper.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class DallasTemperatureWrapperInoImpl : public IDallasTemperatureWrapper
{
private:
    DallasTemperature *_dallasTempDelegate;

public:
    DallasTemperatureWrapperInoImpl(int wireBus)
    {
        // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
        OneWire *tempOneWire = new OneWire(wireBus);
        // Pass our oneWire reference to Dallas Temperature.
        _dallasTempDelegate = new DallasTemperature(tempOneWire);
    }

    virtual void begin();
    virtual void requestTemperatures();
    virtual float getTempFByIndex(int i);
};

#endif