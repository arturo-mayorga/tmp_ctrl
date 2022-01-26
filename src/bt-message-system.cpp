#include <stdlib.h>
#include "bt-message-system.h"

void BtMessageSystem::setup()
{
    //begin software serial
    _softwareSerial->begin(_baudRate);
    _lastKnobPercentage = _state->knobPercentage;
}

void BtMessageSystem::update(unsigned long time)
{
    //check time, return if not needed
    if (time - _lastUpdateTime < 2000)
    {
        return;
    }
    _lastUpdateTime = time;

    //#PID controller mode - at knob state value
    // if different from last sent, send message
    if (_mode == BtMode::controller && _lastKnobPercentage != _state->knobPercentage)
    {
        //build message and get string
        _msg.params[0] = (int)(_state->knobPercentage * 1000);
        MessageReader::messageToString(&_msg, _strBuffer);
        _softwareSerial->write(_strBuffer);
        _lastKnobPercentage = _state->knobPercentage;
    }

    //#servo mode - look for set knob message
    //read serial -> pass bytes to reader
    //if message is found, update app state
    if (_mode == BtMode::servo)
    {
        while (_softwareSerial->available() > 0)
        {
            if (_messageReader->addByte(_softwareSerial->read()))
            {
                Message *msg = _messageReader->getMessage();
                if (msg->type == MSG_TYPE_SET_KNOB && msg->numParams > 0)
                {
                    _state->knobPercentage = ((float)msg->params[0]) / 1000.0f;
                }
            }
        }
    }
}
