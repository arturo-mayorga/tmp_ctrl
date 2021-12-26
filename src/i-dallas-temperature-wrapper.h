#ifndef i_dallas_temperature_wrapper_h
#define i_dallas_temperature_wrapper_h

class IDallasTemperatureWrapper
{
public:
    virtual void begin() = 0;
    virtual void requestTemperatures() = 0;
    virtual float getTempFByIndex(int i) = 0;
};

#endif