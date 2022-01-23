#include <gtest/gtest.h>

/**
 * The implementation for this system is very particular to the specifics of 
 * the knob we are trying to control and the servo we are using to control with.  
 * 
 * ## Knob
 * 
 * There are 3 key positions; OFF, MAX, and MIN.
 * 
 * OFF: Full counter clockwise deflection 
 * MAX: A click away from the OFF position in the clockwise direction (about 15 degrees away)
 * MIN: Full clockwise deflection
 * 
 * The distance between full deflections is about 350 degrees.
 * 
 * Setting the knob to the MAK possition when starting from the OFF possition 
 * is needed to move about 90 degrees clockwise to turn it on and then back to 
 * the MAX position.
 * 
 * ## Servo
 * 
 * The max deflection of the servo is ~160 degrees.  Some gearing will be 
 * needed to reach the deflection needed by the knob.
 * 
 * ## Interpreting the Percentage Output from the Application State
 * 
 * The application state contains knobPercentage which is a value from 0 to 100. These are the mappings to translate from knobPercentage to actual knob positions:
 * 
 * knobPercentage        actual knob position
 * [0 - 49]         =>   OFF
 * [50 - 100]       =>   [MIN - MAX]
 * 
 */

TEST(ServoSystem, Update)
{
    EXPECT_EQ(1, 1);
}