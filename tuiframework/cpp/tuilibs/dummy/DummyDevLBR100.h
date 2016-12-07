#ifndef _tuidevices_DummyDevLBR100_h_
#define _tuidevices_DummyDevLBR100_h_

#include <tuiframework/core/EventQueue.h>
#include <tuiframework/core/IDevice.h>
#include <tuiframework/core/IEventSink.h>
#include <tuiframework/server/DeviceDescriptor.h>
#include <tuitypes/common/CommonTypeReg.h>

#include <pthread.h>

#include <map>
#include <cstdio>

#define AVALUE_SIZE 9

namespace tuiframework {
    class ITUIServer;
}

namespace tuidevices {


class DummyDevLBR100 : public tuiframework::IDevice, public tuiframework::IEventSink {
public:
    static IDevice * createFunction(void * arg);
    static std::string getDeviceName();

    DummyDevLBR100(const tuiframework::DeviceConfig & deviceConfig);
    virtual ~DummyDevLBR100();

        // IDevice
    virtual void deviceConnect(tuiframework::ITUIServer & tuiServer);
    virtual void deviceDisconnect();
    virtual bool deviceExecute();
    virtual void deviceStop();
    virtual void deviceSetEventSink(tuiframework::IEventSink * eventSink);
    virtual const tuiframework::DeviceDescriptor & getDeviceDescriptor() const;

        // IEventSink
    virtual void push(tuiframework::IEvent * event);

    void sendValueEvent(const std::string & str, int index);

    void sendInfoEvents2();

protected:
    static void * inputLoopThread_run(void * arg);
    void executeInputLoop();

    static void * outputLoopThread_run(void * arg);
    void executeOutputLoop();

protected:
    tuiframework::DeviceDescriptor deviceDescriptor;

    int entityID;
    tuiframework::ITUIServer * tuiServer;
    tuiframework::IEventSink * eventSink;

    volatile bool outputLoopRunning;
    pthread_t outputLoopThread;
    volatile bool inputLoopRunning;
    pthread_t inputLoopThread;

    tuiframework::EventQueue outputEventQueue;

protected:
  class AState {
  public:
      AState(int threshold = 100);
      ~AState();

      bool isOn() const;
      void setOn(bool on);
      void tick();

  protected:
      int value;
      int threshold;
      int increment;
  };


  class AValue {
  public:
      AValue(float increment = 1, float minValue = -170, float maxValue = 170);
      ~AValue();

      void setOverride(bool on);

      void setTargetValue(float value);
      void setOverrideValue(float value);
      float getCurrentValue() const;

      void tick();

  protected:
      bool override;

      float increment;
      float minValue;
      float maxValue;

      float currentValue;
      float targetValue;

      float overrideValue;
  };

protected:
    bool engineOn;

    AState engine;

      // 0 - 6: Achsenwinkel, 7 - 8: Greifer
    AValue aValue[AVALUE_SIZE];

    bool stateTrigger;

    std::map<int, AValue> channelNrAValueMap;
    std::map<int, int> channelNrInternalAValueNrMap;

    int enginePortNr;
    int greiferAufPortNr;
    int stateTriggerPortNr;

    int engineIsOnPortNr;
    int greiferIstAufPortNr;
    int greiferIstZuPortNr;

    bool engineIsOn;
    bool greiferIstAuf;
    bool greiferIstZu;
};

}

#endif

