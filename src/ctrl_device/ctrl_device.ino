#include "scr-system.h"
#include "temp-sensor-system.h"
#include "rotor-system.h"

#include "digital-pin-wapper-ino-impl.h"
#include "dallas-temperature-wapper-ino-impl.h"
#include "ssd-wrapper-ino-impl.h"

#include "logger-ino-impl.h"

AppState state;
LoggerInoImpl logger;

#define ROTOR_CLK 7
#define ROTOR_DT 4
#define ROTOR_SW 8

DigitalPinWrapperInoImpl pinWrapper;
RotorSystem rotorS(&state, &logger, &pinWrapper, ROTOR_CLK, INPUT, ROTOR_DT, INPUT, ROTOR_SW, INPUT_PULLUP);

#define TEMP_ONE_WIRE_BUS 2
DallasTemperatureWrapperInoImpl tempSensor(TEMP_ONE_WIRE_BUS);
TempSensorSystem tempS(&state, &logger, &tempSensor);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

SsdWrapperInoImpl display(SCREEN_WIDTH, SCREEN_HEIGHT);
ScrSystem scrS(&state, &logger, &display);

void setup()
{
    Serial.begin(38400);
    rotorS.setup();
    tempS.setup();
    scrS.setup();
    Serial.println("READY ******");
}

void loop()
{
    auto t = millis();
    rotorS.update(t);
    tempS.update(t);
    scrS.update(t);
}