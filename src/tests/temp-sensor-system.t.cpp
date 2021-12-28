#include <gtest/gtest.h>
#include "../app-state.h"
#include "../temp-sensor-system.h"
#include "../i-dallas-temperature-wrapper.h"

#include <vector>
#include <string>

class DallasTemperatureWrapperTestImpl : public IDallasTemperatureWrapper
{
private:
    std::vector<std::string> _log;

public:
    DallasTemperatureWrapperTestImpl(int wireBus)
    {
        _log.push_back("create 3");
    }

    virtual void begin();
    virtual void requestTemperatures();
    virtual float getTempFByIndex(int i);

    void assertLogContents(std::vector<std::string> &inLog)
    {
        EXPECT_EQ(_log.size(), inLog.size());

        for (int i = 0; i < _log.size(); ++i)
        {
            EXPECT_STREQ(inLog[i].c_str(), _log[i].c_str());
        }
    }
};

void DallasTemperatureWrapperTestImpl::begin()
{
    _log.push_back("begin");
}

void DallasTemperatureWrapperTestImpl::requestTemperatures()
{
    _log.push_back("requestTemperatures");
}

float DallasTemperatureWrapperTestImpl::getTempFByIndex(int i)
{
    _log.push_back("getTempFByIndex");
    return 1.234f;
}

// Demonstrate some basic assertions.
TEST(TempSensorSystem, Constructor)
{
    std::vector<std::string> tempWLog;
    DallasTemperatureWrapperTestImpl tempW(3);
    tempWLog.push_back("create 3");

    AppState state;
    TempSensorSystem tSys(&state, &tempW);

    tempW.assertLogContents(tempWLog);
}

TEST(TempSensorSystem, Setup)
{
    std::vector<std::string> tempWLog;
    DallasTemperatureWrapperTestImpl tempW(3);
    tempWLog.push_back("create 3");

    AppState state;
    TempSensorSystem tSys(&state, &tempW);

    tSys.setup();
    tempWLog.push_back("begin");
    tempW.assertLogContents(tempWLog);
}

TEST(TempSensorSystem, InitialUpdates)
{
    std::vector<std::string> tempWLog;
    DallasTemperatureWrapperTestImpl tempW(3);
    tempWLog.push_back("create 3");

    AppState state;
    TempSensorSystem tSys(&state, &tempW);

    tSys.setup();
    tempWLog.push_back("begin");

    tSys.update(0);

    tSys.update(10);

    tSys.update(100);

    tSys.update(999);

    tSys.update(1000);

    tSys.update(1999);

    tempW.assertLogContents(tempWLog);

    EXPECT_EQ(state.currentTemp, 0.0f); // make sure the state hasn't been touched
}

TEST(TempSensorSystem, UpdateAfter2Sec)
{
    std::vector<std::string> tempWLog;
    DallasTemperatureWrapperTestImpl tempW(3);
    tempWLog.push_back("create 3");

    AppState state;
    TempSensorSystem tSys(&state, &tempW);

    tSys.setup();
    tempWLog.push_back("begin");

    tSys.update(0);

    tSys.update(10);

    tSys.update(100);

    tSys.update(999);

    tSys.update(1000);

    tSys.update(1999);

    tSys.update(2000);
    tempWLog.push_back("requestTemperatures");
    tempWLog.push_back("getTempFByIndex");

    tempW.assertLogContents(tempWLog);

    EXPECT_EQ(state.currentTemp, 1.234f);
}

TEST(TempSensorSystem, UpdateEvery2Sec)
{
    std::vector<std::string> tempWLog;
    DallasTemperatureWrapperTestImpl tempW(3);
    tempWLog.push_back("create 3");

    AppState state;
    TempSensorSystem tSys(&state, &tempW);

    tSys.setup();
    tempWLog.push_back("begin");

    tSys.update(0);
    tSys.update(1000);
    tSys.update(2000);
    tempWLog.push_back("requestTemperatures");
    tempWLog.push_back("getTempFByIndex");

    tSys.update(3000);
    tSys.update(4000);
    tempWLog.push_back("requestTemperatures");
    tempWLog.push_back("getTempFByIndex");

    tSys.update(5000);
    tSys.update(6000);
    tempWLog.push_back("requestTemperatures");
    tempWLog.push_back("getTempFByIndex");

    tSys.update(7000);
    tSys.update(8000);
    tempWLog.push_back("requestTemperatures");
    tempWLog.push_back("getTempFByIndex");

    tempW.assertLogContents(tempWLog);

    EXPECT_EQ(state.currentTemp, 1.234f);
}


TEST(TempSensorSystem, UpdateEvery2SecStaggered)
{
    std::vector<std::string> tempWLog;
    DallasTemperatureWrapperTestImpl tempW(3);
    tempWLog.push_back("create 3");

    AppState state;
    TempSensorSystem tSys(&state, &tempW);

    tSys.setup();
    tempWLog.push_back("begin");

    tSys.update(0);
    tSys.update(1999);
    tSys.update(3999);
    tempWLog.push_back("requestTemperatures");
    tempWLog.push_back("getTempFByIndex");

    tSys.update(4111);
    tempWLog.push_back("requestTemperatures");
    tempWLog.push_back("getTempFByIndex");

    tSys.update(5000);
    tSys.update(6000);
    tempWLog.push_back("requestTemperatures");
    tempWLog.push_back("getTempFByIndex");

    tSys.update(7999);
    tSys.update(8000);
    tempWLog.push_back("requestTemperatures");
    tempWLog.push_back("getTempFByIndex");

    tempW.assertLogContents(tempWLog);

    EXPECT_EQ(state.currentTemp, 1.234f);
}