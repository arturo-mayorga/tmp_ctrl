#ifndef message_reader_h
#define message_reader_h



#include "CircularBuffer.h"
#include "message.h"
#include "i-logger.h"

class MessageReader
{
private:
    CircularBuffer<int, 100> buffer;
    Message *_msg;
    ILogger *_logger;
    char _paramBuffer[50];
    int _currentIndx;
    int _numDelim;
    bool _processMessage();
    void _clearUntilStart(bool forceInitialShift);
    void _printBuffer();

public:
    MessageReader(ILogger *logger);
    bool addByte(int byte);
    Message *getMessage();
    static void messageToString(Message *msg, char *buffer);
};

#endif
