#ifndef app_state_h
#define app_state_h

struct AppState {
    float currentTemp;
    float targetTemp;
    unsigned long  targetTempUpdateTime;
    int buttonState;
    int knobState;
    int connectionStatus;
    float knobPercentage;
};



#endif