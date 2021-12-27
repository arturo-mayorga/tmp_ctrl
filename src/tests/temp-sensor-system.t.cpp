#include <gtest/gtest.h>
#include "../temp-sensor-system.h"
#include "../i-dallas-temperature-wrapper.h"

// Demonstrate some basic assertions.
TEST(TempSensorSystem, GeneralTests) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}