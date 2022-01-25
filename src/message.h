#ifndef message_h
#define message_h

class Message
{
public:
    char type;
    int numParams;
    int *params;

    Message(int numP, char t){
        numParams = numP;
        type = t;
        params = new int[numParams];
    }

    ~Message(){ delete this->params; }
};

const char MSG_START = '{';
const char MSG_END = '}';
const char MSG_PARAM_DELIM = ':';

const char MSG_TYPE_SET_KNOB = 'K';
const char MSG_TYPE_STATUS = 'S';


#endif
