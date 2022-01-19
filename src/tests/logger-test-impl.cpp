#include "logger-test-impl.h"
#include <stdio.h>

void LoggerTestImpl::print(const char *s)
{
    printf(s);
}
void LoggerTestImpl::print(int i)
{
    printf("%d", i);
}
void LoggerTestImpl::print(char c)
{
    printf("%c", c);
}
void LoggerTestImpl::println(const char *s)
{
    printf("%s\n", s);
}