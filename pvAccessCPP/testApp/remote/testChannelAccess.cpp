/*
 * testChannelAccess.cpp
 */

#ifdef _WIN32
#define NOMINMAX
#endif

// TODO not nice
// disable buggy boost enable_shared_from_this assert code
#define BOOST_DISABLE_ASSERTS

#define TESTSERVERNOMAIN

#include <envDefs.h>
#include <epicsExit.h>
#include <epicsUnitTest.h>
#include <testMain.h>

#include <pv/serverContext.h>
#include <pv/clientFactory.h>

#include "channelAccessIFTest.h"

#include "testServer.cpp"


class ServerContextAction : public Runnable {

  public:

    ServerContextAction(): 
      m_serverThread(){}


    virtual void run()
    {
      testServer(0);
    }


    void stop() {
      testServerShutdown();
    }


    void start() {
      m_serverThread.reset(new epics::pvData::Thread("pvAccess", highPriority, this));
    }


  private:
    auto_ptr<epics::pvData::Thread> m_serverThread;
};


class ChannelAccessIFRemoteTest: public ChannelAccessIFTest  {

  public:
    
    ChannelAccessIFRemoteTest(): m_serverContextAction() 
    {
      m_serverContextAction.start();
      ClientFactory::start();
    }


    virtual ChannelProvider::shared_pointer getChannelProvider() {
      return getChannelProviderRegistry()->getProvider(
          "pva");
    }


    virtual long getTimeoutSec() {
      return 3;
    }


    virtual bool isLocal() { return false;}


    ~ChannelAccessIFRemoteTest() {
      m_serverContextAction.stop();   
      ClientFactory::stop();

      // shutdown SIGSEG problems
      epicsThreadSleep(2.0);
    }

  private:
    ServerContextAction m_serverContextAction;
};


MAIN(testChannelAccess)
{
  // note: this leaks memory (uses putenv)
  epicsEnvSet("EPICS_PVA_ADDR_LIST", "127.0.0.1");
  epicsEnvSet("EPICS_PVA_AUTO_ADDR_LIST", "0");

  SET_LOG_LEVEL(logLevelError);
  ChannelAccessIFRemoteTest caRemoteTest;
  return caRemoteTest.runAllTest();
}
