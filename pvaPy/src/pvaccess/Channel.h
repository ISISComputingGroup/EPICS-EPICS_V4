#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include <vector>

#include "boost/python/list.hpp"

#include "ChannelGetRequesterImpl.h"
#include "ChannelMonitorRequesterImpl.h"
#include "ChannelRequesterImpl.h"
#include "SynchronizedQueue.h"
#include "PvaClient.h"
#include "CaClient.h"
#include "PvObject.h"
#include "PvProvider.h"
#include "PvaPyLogger.h"

class Channel
{
public:

    static const char* DefaultRequestDescriptor;
    static const double DefaultTimeout;
        
    Channel(const std::string& channelName, PvProvider::ProviderType providerType=PvProvider::PvaProviderType);
    Channel(const Channel& channel);
    virtual ~Channel();

    std::string getName() const;
    virtual PvObject* get(const std::string& requestDescriptor);
    virtual PvObject* get();
    virtual void put(const PvObject& pvObject, const std::string& requestDescriptor);
    virtual void put(const PvObject& pvObject);
    virtual void put(const std::vector<std::string>& values, const std::string& requestDescriptor);
    virtual void put(const std::vector<std::string>& values);
    virtual void put(const std::string& value, const std::string& requestDescriptor);
    virtual void put(const std::string& value);
    virtual void put(const boost::python::list& pyList, const std::string& requestDescriptor);
    virtual void put(const boost::python::list& pyList);

    virtual void put(bool value, const std::string& requestDescriptor);
    virtual void put(bool value);
    virtual void put(char value, const std::string& requestDescriptor);
    virtual void put(char value);
    virtual void put(unsigned char value, const std::string& requestDescriptor);
    virtual void put(unsigned char value);
    virtual void put(short value, const std::string& requestDescriptor);
    virtual void put(short value);
    virtual void put(unsigned short value, const std::string& requestDescriptor);
    virtual void put(unsigned short value);
    virtual void put(int value, const std::string& requestDescriptor);
    virtual void put(int value);
    virtual void put(unsigned int value, const std::string& requestDescriptor);
    virtual void put(unsigned int value);
    virtual void put(long long value, const std::string& requestDescriptor);
    virtual void put(long long value);
    virtual void put(unsigned long long value, const std::string& requestDescriptor);
    virtual void put(unsigned long long value);
    virtual void put(float value, const std::string& requestDescriptor);
    virtual void put(float value);
    virtual void put(double value, const std::string& requestDescriptor);
    virtual void put(double value);

    virtual void subscribe(const std::string& subscriberName, const boost::python::object& pySubscriber);
    virtual void unsubscribe(const std::string& subscriberName);
    virtual void callSubscribers(PvObject& pvObject);
    virtual void startMonitor(const std::string& requestDescriptor);
    virtual void startMonitor();
    virtual void stopMonitor();
    virtual bool isMonitorThreadDone() const;
    virtual void setTimeout(double timeout);
    virtual double getTimeout() const;

private:
    static const double ShutdownWaitTime;

    static PvaPyLogger logger;
    static PvaClient pvaClient;
    static CaClient caClient;
    static void monitorThread(Channel* channel);

    ChannelMonitorRequesterImpl* getMonitorRequester(); 

    epics::pvData::Requester::shared_pointer requester;
    std::tr1::shared_ptr<ChannelRequesterImpl> requesterImpl;
    ChannelGetRequesterImpl channelGetRequester;
    epics::pvAccess::ChannelProvider::shared_pointer provider;
    epics::pvAccess::Channel::shared_pointer channel;
    epics::pvData::MonitorRequester::shared_pointer monitorRequester;
    bool monitorThreadDone;
    SynchronizedQueue<PvObject> pvObjectMonitorQueue;
    std::map<std::string, boost::python::object> subscriberMap;
    epics::pvData::Mutex subscriberMutex;
    double timeout;
};

inline std::string Channel::getName() const
{
    return channelGetRequester.getChannelName();
}

inline void Channel::setTimeout(double timeout) 
{
    this->timeout = timeout;
}

inline double Channel::getTimeout() const
{
    return timeout;
}

#endif
