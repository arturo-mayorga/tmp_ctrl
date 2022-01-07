#ifndef logger_ino_impl_h
#define logger_ino_impl_h

#include "i-logger.h"

class LoggerInoImpl : public ILogger
{
public:
    virtual void print(const char *s);
    virtual void print(int i);
    virtual void println(const char *s);
};

#endif