#include "logger-ino-impl.h"
#include <Arduino.h>

void LoggerInoImpl::print(const char *s)
{
    Serial.print(s);
}
void LoggerInoImpl::print(int i)
{
    Serial.print(i);
}
void LoggerInoImpl::print(char c)
{
    Serial.print(c);
}
void LoggerInoImpl::println(const char *s)
{
    Serial.println(s);
}