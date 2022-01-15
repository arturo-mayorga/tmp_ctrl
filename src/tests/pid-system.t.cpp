#include <gtest/gtest.h>
#include "../pid-system.h"
#include "logger-test-impl.h"

class TestPidController : public PidController
{
private:
    int _calcCounter;

public:
    TestPidController() : PidController(0.0f, 0.0f, 0.0f, 0.0f, 0.0f)
    {
        _calcCounter = 0;
    }

    virtual float calculate(float targetValue, float currentValue, float dt)
    {
        return (float)(_calcCounter++);
    }
};

TEST(PidSystem, Update)
{
    // make sure pidController::calculate() is only called every 2000 ms
    // and that the calculate() output is stored in the state

    AppState state;
    TestPidController pidController;
    LoggerTestImpl logger;

    PidSystem pidS(&state, &logger, &pidController);

    for (unsigned long i = 0; i < 10010; ++i)
    {
        pidS.update(i);
    }

    EXPECT_EQ(state.knobPercentage, 4.0f);
}
