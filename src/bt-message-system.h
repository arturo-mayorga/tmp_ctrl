#ifndef bt_message_system_h
#define bt_message_system_h

#include "app-system.h"
#include "app-state.h"
#include "message-reader.h"
#include "i-software-serial-wrapper.h"

enum BtMode { controller, servo };
const 

class BtMessageSystem : public AppSystem
{
private:
    MessageReader *_messageReader;
    ISoftwareSerialWrapper *_softwareSerial;
    long _baudRate;
    long _lastUpdateTime;
    float _lastKnobPercentage;
    BtMode _mode;
    Message _msg;
    char _strBuffer[100];
public:
    BtMessageSystem(AppState *state, ILogger *logger, ISoftwareSerialWrapper *softwareSerial, BtMode mode, long baudRate)
        :AppSystem(state, logger), _msg(1, MSG_TYPE_SET_KNOB)
        // messages currently only have one parameter so we can hardcode that
        // right now we also only ever send set knob type messages
    {
        _messageReader = new MessageReader(logger);
        _softwareSerial = softwareSerial;
        _baudRate = baudRate;
        _lastUpdateTime = 0;
        _mode = mode;
    }
    virtual void setup();
    virtual void update(unsigned long time);
};

#endif
