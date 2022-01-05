#include <gtest/gtest.h>
#include "../rotor-system.h"
#include "logger-test-impl.h"

class DigitalPinWrapperTestImpl : public IDigitalPinWrapper
{
private:
    std::vector<std::string> _log;

public:
    int pinVals[3];

    virtual void pinMode(int pin, int mode)
    {
        _log.push_back("pinMode");
    }
    virtual bool digitalRead(int port)
    {
        return pinVals[port] != 0;
    }

    void assertLogContents(std::vector<std::string> &inLog)
    {
        EXPECT_EQ(_log.size(), inLog.size());

        for (int i = 0; i < _log.size(); ++i)
        {
            EXPECT_STREQ(inLog[i].c_str(), _log[i].c_str());
        }
    }
};

TEST(RotorSystem, Setup)
{
    std::vector<std::string> log;
    DigitalPinWrapperTestImpl pinWrapper;

    AppState state;
    LoggerTestImpl logger;
    RotorSystem system(&state, &logger, &pinWrapper, 0, 0, 1, 1, 2, 2);

    pinWrapper.assertLogContents(log);

    system.setup();
    log.push_back("pinMode");
    log.push_back("pinMode");
    log.push_back("pinMode");

    pinWrapper.assertLogContents(log);
}

TEST(RotorSystem, Forward)
{
    DigitalPinWrapperTestImpl pinWrapper;

    AppState state;
    LoggerTestImpl logger;
    RotorSystem system(&state, &logger, &pinWrapper, 0, 0, 1, 1, 2, 2);

    pinWrapper.pinVals[0] = 0;
    pinWrapper.pinVals[1] = 0;
    pinWrapper.pinVals[2] = 0;
    system.update(1);

    state.targetTemp = 10;

    pinWrapper.pinVals[0] = 1;
    pinWrapper.pinVals[1] = 0;
    pinWrapper.pinVals[2] = 0;
    system.update(2);

    EXPECT_EQ(state.targetTemp, 10.5);

    pinWrapper.pinVals[0] = 0;
    pinWrapper.pinVals[1] = 1;
    pinWrapper.pinVals[2] = 0;
    system.update(3);

    EXPECT_EQ(state.targetTemp, 11);
    EXPECT_EQ(state.input.inputKnobTime, 3);
}

TEST(RotorSystem, Backward)
{
    DigitalPinWrapperTestImpl pinWrapper;

    AppState state;
    LoggerTestImpl logger;
    RotorSystem system(&state, &logger, &pinWrapper, 0, 0, 1, 1, 2, 2);

    pinWrapper.pinVals[0] = 0;
    pinWrapper.pinVals[1] = 0;
    pinWrapper.pinVals[2] = 0;
    system.update(1);

    state.targetTemp = 10;

    pinWrapper.pinVals[0] = 1;
    pinWrapper.pinVals[1] = 1;
    pinWrapper.pinVals[2] = 0;
    system.update(20);

    EXPECT_EQ(state.targetTemp, 9.5);

    pinWrapper.pinVals[0] = 0;
    pinWrapper.pinVals[1] = 0;
    pinWrapper.pinVals[2] = 0;
    system.update(30);

    EXPECT_EQ(state.targetTemp, 9);
    EXPECT_EQ(state.input.inputKnobTime, 30);
}

TEST(RotorSystem, DownUp)
{
    DigitalPinWrapperTestImpl pinWrapper;

    AppState state;
    LoggerTestImpl logger;
    RotorSystem system(&state, &logger, &pinWrapper, 0, 0, 1, 1, 2, 2);

    pinWrapper.pinVals[0] = 0;
    pinWrapper.pinVals[1] = 0;
    pinWrapper.pinVals[2] = 0;
    system.update(1);

    state.targetTemp = 10;

    pinWrapper.pinVals[0] = 0;
    pinWrapper.pinVals[1] = 0;
    pinWrapper.pinVals[2] = 1;
    system.update(200);

    pinWrapper.pinVals[0] = 0;
    pinWrapper.pinVals[1] = 0;
    pinWrapper.pinVals[2] = 0;
    system.update(300);

    EXPECT_EQ(state.targetTemp, 10);
    EXPECT_EQ(state.input.inputButtonTime, 300);
}
