#include <stdlib.h>
#include "message-reader.h"

MessageReader::MessageReader()
    : _msg(NULL), _currentIndx(0), _numDelim(0)
{
}

bool MessageReader::addByte(int byte)
{
    this->buffer.push(byte);
    return this->_processMessage();
}

Message* MessageReader::getMessage()
{
    return this->_msg;
}

void MessageReader::_clearUntilStart(bool forceInitialShift)
{
    // used to remove start char and clear rest of message;
    if (forceInitialShift && !this->buffer.isEmpty())
    {
        this->buffer.shift();
    }

    // flush buffer until empty or we see a start
    while (!this->buffer.isEmpty() && this->buffer.first() != MSG_START)
    {
        this->buffer.shift();
        this->_currentIndx = 0;
        this->_numDelim = 0;
    }
}

bool MessageReader::_processMessage()
{
    this->_clearUntilStart(false);

    if (this->buffer.first() == MSG_START)
    {
        bool hasMessage = false;
        int i = this->_currentIndx;
        while (i < this->buffer.size() && !hasMessage)
        {
            this->_currentIndx = i;
            if (this->buffer[i] == MSG_START) // we see a start after a start, ignore everthing before
            {
                this->_clearUntilStart(true);
                return false;
            }

            if (this->buffer[i] == MSG_PARAM_DELIM)
            {
                this->_numDelim++;
            }
            if (this->buffer[i] == MSG_END)
            {
                hasMessage = true;
            }
            i++;
        }
        if (hasMessage)
        {
            // message is invalid if not at least one parameter is found
            // min valid message  size is 5 (e.g. '{a:1}' )
            // 3rd char should always be a param delimiter
            if (this->_numDelim <= 0 || this->buffer.size() < 5 || this->buffer[2] != MSG_PARAM_DELIM)
            {
                this->_clearUntilStart(true);
                return false;
            }

            Message *msg = new Message();
            int currentParam = 0;
            msg->numParams = this->_numDelim;
            msg->params = new int[msg->numParams];
            msg->type = this->buffer[1]; // message type is always the first char after the start token

            int j = 3; //the first valid param char is always at index 3
            int paramBufferOffset = j;
            //the value of i is one more than the index value of where end token is
            while (j < (i - 1))
            {
                if (this->buffer[j] == MSG_PARAM_DELIM || this->buffer[j] == MSG_END)
                {
                    this->_paramBuffer[j - paramBufferOffset] = 0;
                    paramBufferOffset = j + 1;
                    msg->params[currentParam] = atoi(this->_paramBuffer);
                    currentParam++;
                }
                else
                {
                    this->_paramBuffer[j - paramBufferOffset] = (char)this->buffer[j];
                }
                j++;
                if (j - paramBufferOffset > 50) //49(+1 for 0 char) is the max param length;
                {
                    this->_clearUntilStart(true);
                    return false;
                }
            }
            this->_clearUntilStart(true);
            if (this->_msg != NULL)
            {
                delete this->_msg;
            }
            this->_msg = msg;

            return true;
        }
    }
    return false;
}
