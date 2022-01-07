#ifndef message_reader_h
#define message_reader_h



#include "CircularBuffer.h"

#include "message.h"

class MessageReader
{
private:
    CircularBuffer<int, 100> buffer;
    Message *_msg;
    char _paramBuffer[50];
    int _currentIndx;
    int _numDelim;
    bool _processMessage();
    void _clearUntilStart(bool forceInitialShift);

public:
    MessageReader();
    bool addByte(int byte);
    Message *getMessage();
};

#endif
