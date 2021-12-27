#ifndef app_state_h
#define app_state_h

struct AppState
{
    float currentTemp;
    float targetTemp;
    unsigned long targetTempUpdateTime;
    int buttonState;
    int knobState;
    int connectionStatus;
    float knobPercentage;

    AppState()
    {
        currentTemp = 0;
        targetTemp = 0;
        targetTempUpdateTime = 0;
        buttonState = 0;
        knobState = 0;
        connectionStatus = 0;
        knobPercentage = 0;
    }
};

#endif