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

    void setStartState();

    void sendChangedValueEvents1();
    void sendChangedValueEvents2();
    void sendChangedValueEvents3();
    void sendSteadyValueEvents1();
    void sendControlEvents1();
    void sendControlEvents2();
    void sendControlEvents3();
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
      void setOn();
      void setOff();
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

      void setTargetValue(float value);
      float getCurrentValue() const;
      void tick();
      void setEngineOn(bool on);

  protected:
      float increment;
      float minValue;
      float maxValue;

      float currentValue;
      float targetValue;

      bool engineOn;
  };


protected:
    int curTick;

    AState engine;
    bool lastTickEngineState;

      // 0 - 6: Achsenwinkel, 7 - 8: Greifer
    AValue $a[8];

    /*
      portMap["LBR100.CTR.AntriebeAn"] =      Port("LBR100.CTR.AntriebeAn", "DigitalChannel", Port::Sink);
      portMap["LBR100.CTR.AntriebeSindAn"] =  Port("LBR100.CTR.AntriebeSindAn", "DigitalChannel", Port::Source);
      portMap["LBR100.CTR.ExternStart"] =     Port("LBR100.CTR.ExternStart", "DigitalChannel", Port::SourceAndSink);
      portMap["LBR100.CTR.GreiferIstAuf"] =   Port("LBR100.CTR.GreiferIstAuf", "DigitalChannel", Port::Source);
      portMap["LBR100.CTR.GreiferIstZu"] =    Port("LBR100.CTR.GreiferIstZu", "DigitalChannel", Port::Source);
      portMap["LBR100.CTR.GreiferAuf"] =      Port("LBR100.CTR.GreiferAuf", "DigitalChannel", Port::SourceAndSink);

      portMap["LBR100.M01.$A1"] = Port("LBR100.M01.$A1", "AnalogChannel", Port::SourceAndSink);
      portMap["LBR100.M02.$A2"] = Port("LBR100.M02.$A2", "AnalogChannel", Port::SourceAndSink);
      portMap["LBR100.M03.$A3"] = Port("LBR100.M03.$A3", "AnalogChannel", Port::SourceAndSink);
      portMap["LBR100.M04.$A4"] = Port("LBR100.M04.$A4", "AnalogChannel", Port::SourceAndSink);
      portMap["LBR100.M05.$A5"] = Port("LBR100.M05.$A5", "AnalogChannel", Port::SourceAndSink);
      portMap["LBR100.M06.$A6"] = Port("LBR100.M06.$A6", "AnalogChannel", Port::SourceAndSink);
      portMap["LBR100.M07.$A7"] = Port("LBR100.M07.$A7", "AnalogChannel", Port::SourceAndSink);

      portMap["LBR100.GR.$pos_l"] = Port("LBR100.GR.$pos_l", "TextChannel", Port::SourceAndSink);
      portMap["LBR100.GR.$pos_r"] = Port("LBR100.GR.$pos_r", "TextChannel", Port::SourceAndSink);


      portMap["LBR100.CTR.Soll_A1"] = Port("LBR100.CTR.Soll_A1", "AnalogChannel", Port::Sink);
      portMap["LBR100.CTR.Soll_A2"] = Port("LBR100.CTR.Soll_A2", "AnalogChannel", Port::Sink);
      portMap["LBR100.CTR.Soll_A3"] = Port("LBR100.CTR.Soll_A3", "AnalogChannel", Port::Sink);
      portMap["LBR100.CTR.Soll_A4"] = Port("LBR100.CTR.Soll_A4", "AnalogChannel", Port::Sink);
      portMap["LBR100.CTR.Soll_A5"] = Port("LBR100.CTR.Soll_A5", "AnalogChannel", Port::Sink);
      portMap["LBR100.CTR.Soll_A6"] = Port("LBR100.CTR.Soll_A6", "AnalogChannel", Port::Sink);
      portMap["LBR100.CTR.Soll_A7"] = Port("LBR100.CTR.Soll_A7", "AnalogChannel", Port::Sink);

      portMap["LBR100.INF.Scripts"] = Port("LBR100.INF.Scripts", "TextVectorChannel", Port::Source, "WinMod Scripts");
      portMap["LBR100.INF.Additional"] = Port("LBR100.INF.Additional", "TextChannel", Port::Source, "Zusatzinformationen");

      portMap["LBR100.CMD.StateTrigger"] = Port("LBR100.CMD.StateTrigger", "DigitalChannel", Port::Sink);
    */


    bool switchState[4];

    float transX;
    float transZ;
    Vector4<double> pos;

    bool highlight[3];
    bool infopanel[3];
};

}

#endif

