#ifndef pid_controller_h
#define pid_controller_h


class PidController
{
private:
    float _max;
    float _min;
    float _Kp;
    float _Kd;
    float _Ki;
    float _pre_error;
    float _integral;

public:
    PidController(float min, float max, float p, float i, float d);

    virtual float calculate(float targetValue, float currentValue, float dt);
};

#endif