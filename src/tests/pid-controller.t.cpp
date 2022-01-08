#include <gtest/gtest.h>

#include "../pid-controller.h"

#define EPS 0.00001f

TEST(PidController, PTerm)
{
    // make sure the output is proportional to the distance between the target value and the actual value
    PidController pid(0, 100, 1, 0, 0);
    EXPECT_NEAR(pid.calculate(1, 3, 1), 0, EPS);
    EXPECT_NEAR(pid.calculate(3, 1, 1), 2, EPS);
    EXPECT_NEAR(pid.calculate(99, 1, 1), 98, EPS);
    EXPECT_NEAR(pid.calculate(300, 1, 1), 100, EPS);

    PidController pid2(0, 100, 3, 0, 0);
    EXPECT_NEAR(pid2.calculate(1, 3, 1), 0, EPS);
    EXPECT_NEAR(pid2.calculate(3, 1, 1), 6, EPS);
    EXPECT_NEAR(pid2.calculate(21, 1, 1), 60, EPS);
    EXPECT_NEAR(pid2.calculate(300, 1, 1), 100, EPS);
}

TEST(PidController, DTerm)
{
    // make sure the output increases over time if the error does not decrease
    PidController pid(0, 100, 0, 1, 0);

    EXPECT_NEAR(pid.calculate(3, 1, 1), 2, EPS);
    EXPECT_NEAR(pid.calculate(3, 1, 1), 4, EPS);
    EXPECT_NEAR(pid.calculate(3, 1, 1), 6, EPS);
    EXPECT_NEAR(pid.calculate(3, 1, 1), 8, EPS);
    EXPECT_NEAR(pid.calculate(3, 1, 1), 10, EPS);
    EXPECT_NEAR(pid.calculate(3, 1, 1), 12, EPS);

    // and levels off as we reach the target value
    EXPECT_NEAR(pid.calculate(3, 3, 1), 12, EPS);
    EXPECT_NEAR(pid.calculate(3, 3, 1), 12, EPS);
    EXPECT_NEAR(pid.calculate(3, 3, 1), 12, EPS);
    EXPECT_NEAR(pid.calculate(3, 3, 1), 12, EPS);
    EXPECT_NEAR(pid.calculate(3, 3, 1), 12, EPS);
    EXPECT_NEAR(pid.calculate(3, 3, 1), 12, EPS);
    EXPECT_NEAR(pid.calculate(3, 3, 1), 12, EPS);

    PidController pid2(0, 1000, 0, 10, 0);

    EXPECT_NEAR(pid2.calculate(3, 1, 1), 20, EPS);
    EXPECT_NEAR(pid2.calculate(3, 1, 1), 40, EPS);
    EXPECT_NEAR(pid2.calculate(3, 1, 1), 60, EPS);
    EXPECT_NEAR(pid2.calculate(3, 1, 1), 80, EPS);
    EXPECT_NEAR(pid2.calculate(3, 1, 1), 100, EPS);
    EXPECT_NEAR(pid2.calculate(3, 1, 1), 120, EPS);
    
    EXPECT_NEAR(pid2.calculate(3, 3, 1), 120, EPS);
    EXPECT_NEAR(pid2.calculate(3, 3, 1), 120, EPS);
    EXPECT_NEAR(pid2.calculate(3, 3, 1), 120, EPS);
    EXPECT_NEAR(pid2.calculate(3, 3, 1), 120, EPS);
    EXPECT_NEAR(pid2.calculate(3, 3, 1), 120, EPS);
    EXPECT_NEAR(pid2.calculate(3, 3, 1), 120, EPS);
    EXPECT_NEAR(pid2.calculate(3, 3, 1), 120, EPS);
}

TEST(PidController, ITerm)
{
    // make the output grow with the change in error over time
    PidController pid(0, 100, 0, 0, 1);
    EXPECT_NEAR(pid.calculate(3, 1, 1), 2, EPS);
    EXPECT_NEAR(pid.calculate(4, 1, 1), 1, EPS);
    EXPECT_NEAR(pid.calculate(5, 1, 1), 1, EPS);
    EXPECT_NEAR(pid.calculate(6, 1, 1), 1, EPS);
    EXPECT_NEAR(pid.calculate(7, 1, 1), 1, EPS);

    PidController pid2(0, 100, 0, 0, 10);
    EXPECT_NEAR(pid2.calculate(3, 1, 1), 20, EPS);
    EXPECT_NEAR(pid2.calculate(4, 1, 1), 10, EPS);
    EXPECT_NEAR(pid2.calculate(5, 1, 1), 10, EPS);
    EXPECT_NEAR(pid2.calculate(6, 1, 1), 10, EPS);
    EXPECT_NEAR(pid2.calculate(7, 1, 1), 10, EPS);
}