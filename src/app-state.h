#ifndef app_state_h
#define app_state_h

struct InputState
{
    unsigned long inputButtonTime;
    int inputButtonState;
    unsigned long inputKnobTime;
    int inputKnobState;

    InputState()
    {
        inputButtonTime = 0;
        inputButtonState = 0;
        inputKnobTime = 0;
        inputKnobState = 0;
    }
};

struct AppState
{
    float currentTemp;
    float targetTemp;

    InputState input;
    int connectionStatus;
    float knobPercentage;

    AppState()
    {
        currentTemp = 0;
        targetTemp = 0;
        connectionStatus = 0;
        knobPercentage = 0;
    }
};

#endif