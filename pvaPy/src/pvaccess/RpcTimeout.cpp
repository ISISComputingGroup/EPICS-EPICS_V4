// Copyright information and license terms for this software can be
// found in the file LICENSE that is included with the distribution

#include "epicsStdio.h"
#include "RpcTimeout.h"

RpcTimeout::RpcTimeout(const std::string& message) :
    PvaException(message)
{
}

RpcTimeout::RpcTimeout(const char* message, ...) :
    PvaException()
{
    va_list messageArgs;
    va_start(messageArgs, message);
    char messageBuffer[MaxMessageLength];
    epicsVsnprintf(messageBuffer, MaxMessageLength, message, messageArgs);
    setMessage(std::string(messageBuffer));
    va_end(messageArgs);
}

