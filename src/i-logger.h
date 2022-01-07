#ifndef i_logger_h
#define i_logger_h

class ILogger
{
public:
    virtual void print(const char *s) = 0;
    virtual void print(int i) = 0;
    virtual void println(const char *s) = 0;
};

#endif