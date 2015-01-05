#include "epicsStdio.h"
#include "InvalidRequest.h"

InvalidRequest::InvalidRequest(const std::string& message) :
    PvaException(message)
{
}

InvalidRequest::InvalidRequest(const char* message, ...) :
    PvaException()
{
    va_list messageArgs;
    va_start(messageArgs, message);
    char messageBuffer[MaxMessageLength];
    epicsVsnprintf(messageBuffer, MaxMessageLength, message, messageArgs);
    setMessage(std::string(messageBuffer));
    va_end(messageArgs);
}

