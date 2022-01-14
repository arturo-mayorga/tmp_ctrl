#include "pid-controller.h"

/**
 * based on the implementation described under:
 * https://en.wikipedia.org/wiki/PID_controller#Pseudocode
 * 
 * previous_error := 0
 * integral := 0
 * loop:
 *   error := setpoint − measured_value
 *   proportional := error;
 *   integral := integral + error × dt
 *   derivative := (error − previous_error) / dt
 *   output := Kp × proportional + Ki × integral + Kd × derivative
 *   previous_error := error
 *   wait(dt)
 *   goto loop
 * 
 */

PidController::PidController(float min, float max, float p, float i, float d)
{
    _max = max;
    _min = min;
    _Kp = p;
    _Kd = d;
    _Ki = i;
    _pre_error = 0;
    _integral = 0;
}

float PidController::calculate(float targetValue, float currentValue, float dt)
{
    // Calculate error
    float error = targetValue - currentValue;

    // Proportional term
    float Pout = _Kp * error;

    // Integral term
    _integral += error * dt;
    float Iout = _Ki * _integral;

    // Derivative term
    float derivative = (error - _pre_error) / dt;
    float Dout = _Kd * derivative;

    // Calculate total output
    float output = Pout + Iout + Dout;

    // Restrict to max/min
    if (output > _max)
        output = _max;
    else if (output < _min)
        output = _min;

    // Save error to previous error
    _pre_error = error;

    return output;
}