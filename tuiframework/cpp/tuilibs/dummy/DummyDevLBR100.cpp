#include "DummyDevLBR100.h"

#include <tuiframework/core/ITUIServer.h>
#include <tuiframework/core/IEvent.h>
#include <tuiframework/server/DeviceConfig.h>


#include <cstdlib> // GCC 4.3 related build problem

#include <ctime>

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#endif

#include <cmath>

using namespace tuiframework;
using namespace std;

namespace tuidevices {


static std::string $A1 = "LBR100.M01.$A1";
static std::string $A2 = "LBR100.M02.$A2";
static std::string $A3 = "LBR100.M03.$A3";
static std::string $A4 = "LBR100.M04.$A4";
static std::string $A5 = "LBR100.M05.$A5";
static std::string $A6 = "LBR100.M06.$A6";
static std::string $A7 = "LBR100.M07.$A7";

static std::string $POS_L = "LBR100.GR.$pos_l";
static std::string $POS_R = "LBR100.GR.$pos_r";

static std::string ANTRIEBE_AN = "LBR100.CTR.AntriebeAn";
static std::string ANTRIEBE_SIND_AN = "LBR100.CTR.AntriebeSindAn";

static std::string EXTERN_START = "LBR100.CTR.ExternStart";
static std::string GREIFER_IST_AUF = "LBR100.CTR.GreiferIstAuf";
static std::string GREIFER_IST_ZU = "LBR100.CTR.GreiferIstZu";
static std::string GREIFER_AUF = "LBR100.CTR.GreiferAuf";

static std::string SOLL_A1 = "LBR100.CTR.Soll_A1";
static std::string SOLL_A2 = "LBR100.CTR.Soll_A2";
static std::string SOLL_A3 = "LBR100.CTR.Soll_A3";
static std::string SOLL_A4 = "LBR100.CTR.Soll_A4";
static std::string SOLL_A5 = "LBR100.CTR.Soll_A5";
static std::string SOLL_A6 = "LBR100.CTR.Soll_A6";
static std::string SOLL_A7 = "LBR100.CTR.Soll_A7";

static std::string STATE_TRIGGER = "LBR100.StateTrigger";


IDevice * DummyDevLBR100::createFunction(void * arg) {
    DeviceConfig * deviceConfig = static_cast<DeviceConfig *>(arg);
    return new DummyDevLBR100(*deviceConfig);
}


std::string DummyDevLBR100::getDeviceName() {
    return "DummyDevLBR100";
}


DummyDevLBR100::AState::AState(int threshold) :
    value(0),
    increment(0),
    threshold(threshold) {
}


DummyDevLBR100::AState::~AState() {
}


bool DummyDevLBR100::AState::isOn() const {
    return this->value > this->threshold;
}


void DummyDevLBR100::AState::setOn(bool on) {
    if (on) {
        this->increment = 1;
    } else {
        this->increment = 0;
        this->value = 0;
    }
}


void DummyDevLBR100::AState::tick() {
    this->value += increment;
}


DummyDevLBR100::AValue::AValue(float increment, float minValue, float maxValue) :
    override(false),
    increment(increment),
    minValue(minValue),
    maxValue(maxValue),
    currentValue(0),
    targetValue(0),
    overrideValue(0) {
}



DummyDevLBR100::AValue::~AValue() {
}


void DummyDevLBR100::AValue::setOverride(bool on) {
    this->override = on;
}


void DummyDevLBR100::AValue::setTargetValue(float value) {
    this->targetValue = value;
}


void DummyDevLBR100::AValue::setOverrideValue(float value) {
    this->overrideValue = value;
}


float DummyDevLBR100::AValue::getCurrentValue() const {

    if (this->override) {
        return this->overrideValue;
    }

    return this->currentValue;
}


void DummyDevLBR100::AValue::tick() {
    if (this->currentValue < this->targetValue) {
        this->currentValue += increment;
        if (this->currentValue > this->targetValue) {
            this->targetValue = this->currentValue;
        }
    } else if (this->currentValue > this->targetValue) {
        this->currentValue -= increment;
        if (this->currentValue < this->targetValue) {
            this->targetValue = this->currentValue;
        }
    }
}



DummyDevLBR100::DummyDevLBR100(const DeviceConfig & deviceConfig) :
    stateTrigger(true) {

    this->deviceDescriptor.setEntityID(deviceConfig.getEntityID());
    this->entityID = this->deviceDescriptor.getEntityID();

    map<string, Port> portMap;

    portMap[$A1] = Port($A1, "AnalogChannel", Port::SourceAndSink);
    portMap[$A2] = Port($A2, "AnalogChannel", Port::SourceAndSink);
    portMap[$A3] = Port($A3, "AnalogChannel", Port::SourceAndSink);
    portMap[$A4] = Port($A4, "AnalogChannel", Port::SourceAndSink);
    portMap[$A5] = Port($A5, "AnalogChannel", Port::SourceAndSink);
    portMap[$A6] = Port($A6, "AnalogChannel", Port::SourceAndSink);
    portMap[$A7] = Port($A7, "AnalogChannel", Port::SourceAndSink);

    portMap[$POS_L] = Port($POS_L, "AnalogChannel", Port::SourceAndSink);
    portMap[$POS_R] = Port($POS_R, "AnalogChannel", Port::SourceAndSink);

    portMap[ANTRIEBE_AN] = Port(ANTRIEBE_AN, "DigitalChannel", Port::Sink);
    portMap[ANTRIEBE_SIND_AN] = Port(ANTRIEBE_SIND_AN, "DigitalChannel", Port::Source);

    portMap[EXTERN_START] = Port(EXTERN_START, "DigitalChannel", Port::SourceAndSink);
    portMap[GREIFER_IST_AUF] = Port(GREIFER_IST_AUF, "DigitalChannel", Port::Source);
    portMap[GREIFER_IST_ZU] = Port(GREIFER_IST_ZU, "DigitalChannel", Port::Source);
    portMap[GREIFER_AUF] = Port(GREIFER_AUF, "DigitalChannel", Port::SourceAndSink);

    portMap[SOLL_A1] = Port(SOLL_A1, "AnalogChannel", Port::Sink);
    portMap[SOLL_A2] = Port(SOLL_A2, "AnalogChannel", Port::Sink);
    portMap[SOLL_A3] = Port(SOLL_A3, "AnalogChannel", Port::Sink);
    portMap[SOLL_A4] = Port(SOLL_A4, "AnalogChannel", Port::Sink);
    portMap[SOLL_A5] = Port(SOLL_A5, "AnalogChannel", Port::Sink);
    portMap[SOLL_A6] = Port(SOLL_A6, "AnalogChannel", Port::Sink);
    portMap[SOLL_A7] = Port(SOLL_A7, "AnalogChannel", Port::Sink);

    //portMap["LBR100.INF.Scripts"] = Port("LBR100.INF.Scripts", "TextVectorChannel", Port::Source, "WinMod Scripts");
    //portMap["LBR100.INF.Additional"] = Port("LBR100.INF.Additional", "TextChannel", Port::Source, "Zusatzinformationen");

    portMap[STATE_TRIGGER] = Port(STATE_TRIGGER, "DigitalChannel", Port::Sink);

    DeviceType deviceType;
    deviceType.setPortMap(portMap);
    deviceType.setDeviceTypeName(getDeviceName());
    deviceType.setDescription("LBR100 Test Device");
    this->deviceDescriptor.setDeviceType(deviceType);

    std::map<std::string, int> nameChannelNrMap;
    int nr = 1;
    map<string, Port>::iterator i = portMap.begin();
    map<string, Port>::iterator e = portMap.end();
    while (i != e) {
        nameChannelNrMap[(*i).second.getName()] = nr;
        ++nr;
        ++i;
    }

    this->deviceDescriptor.setNameChannelNrMap(nameChannelNrMap);

    this->enginePortNr = this->deviceDescriptor.getNameChannelNrMap()[ANTRIEBE_AN];
    this->greiferAufPortNr = this->deviceDescriptor.getNameChannelNrMap()[GREIFER_AUF];
    this->stateTriggerPortNr = this->deviceDescriptor.getNameChannelNrMap()[STATE_TRIGGER];
    this->greiferIstAufPortNr = this->deviceDescriptor.getNameChannelNrMap()[GREIFER_IST_AUF];
    this->greiferIstZuPortNr = this->deviceDescriptor.getNameChannelNrMap()[GREIFER_IST_ZU];
    this->engineIsOnPortNr = this->deviceDescriptor.getNameChannelNrMap()[ANTRIEBE_SIND_AN];

    this->channelNrAValueMap[nameChannelNrMap[$A1]] = AValue();
    this->channelNrAValueMap[nameChannelNrMap[$A2]] = AValue();
    this->channelNrAValueMap[nameChannelNrMap[$A3]] = AValue();
    this->channelNrAValueMap[nameChannelNrMap[$A4]] = AValue();
    this->channelNrAValueMap[nameChannelNrMap[$A5]] = AValue();
    this->channelNrAValueMap[nameChannelNrMap[$A6]] = AValue();
    this->channelNrAValueMap[nameChannelNrMap[$A7]] = AValue();
    this->channelNrAValueMap[nameChannelNrMap[$POS_L]] = AValue();
    this->channelNrAValueMap[nameChannelNrMap[$POS_R]] = AValue();

    this->channelNrInternalAValueNrMap[nameChannelNrMap[SOLL_A1]] = nameChannelNrMap[$A1];
    this->channelNrInternalAValueNrMap[nameChannelNrMap[SOLL_A2]] = nameChannelNrMap[$A2];
    this->channelNrInternalAValueNrMap[nameChannelNrMap[SOLL_A3]] = nameChannelNrMap[$A3];
    this->channelNrInternalAValueNrMap[nameChannelNrMap[SOLL_A4]] = nameChannelNrMap[$A4];
    this->channelNrInternalAValueNrMap[nameChannelNrMap[SOLL_A5]] = nameChannelNrMap[$A5];
    this->channelNrInternalAValueNrMap[nameChannelNrMap[SOLL_A6]] = nameChannelNrMap[$A6];
    this->channelNrInternalAValueNrMap[nameChannelNrMap[SOLL_A7]] = nameChannelNrMap[$A7];
}


DummyDevLBR100::~DummyDevLBR100() {
}



bool DummyDevLBR100::deviceExecute() {
    {
        int rc = pthread_create(&this->outputLoopThread, NULL, DummyDevLBR100::outputLoopThread_run, this);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
        }
    }
    {
        int rc = pthread_create(&this->inputLoopThread, NULL, DummyDevLBR100::inputLoopThread_run, this);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
        }
    }

    return true;
}


void DummyDevLBR100::deviceStop() {
    pthread_cancel(this->inputLoopThread);
    pthread_join(this->inputLoopThread, 0);
    pthread_cancel(this->outputLoopThread);
    pthread_join(this->outputLoopThread, 0);
}


void DummyDevLBR100::push(tuiframework::IEvent * event) {
    this->outputEventQueue.push(event);
}


void DummyDevLBR100::deviceConnect(tuiframework::ITUIServer & tuiServer) {
    tuiServer.tuiServerRegisterDevice(this->entityID, *this);
    tuiServer.tuiServerRegisterEventSink(this->entityID, *this);
    this->tuiServer = &tuiServer;
}


void DummyDevLBR100::deviceDisconnect() {
    if (tuiServer) {
        this->tuiServer->tuiServerDeregisterDevice(this->entityID);
        this->tuiServer->tuiServerDeregisterEventSink(this->entityID);
        this->tuiServer = 0;
    }
}


void DummyDevLBR100::deviceSetEventSink(tuiframework::IEventSink * eventSink) {
    this->eventSink = eventSink;
}


const DeviceDescriptor & DummyDevLBR100::getDeviceDescriptor() const {
    return this->deviceDescriptor;
}


void * DummyDevLBR100::inputLoopThread_run(void * arg) {
    printf("DummyDevLBR100 - input loop thread started\n");
    DummyDevLBR100 * dummyDevice = static_cast<DummyDevLBR100 *>(arg);
    dummyDevice->executeInputLoop();
    return 0;
}

  // not used at the moment
void DummyDevLBR100::sendInfoEvents2() {
    {
        std::vector<std::string> vs;
        vs.push_back("script.1...script.1...script.1\nscript.1...script.1...script.1\nscript.1...script.1...script.1\n");
        vs.push_back("script.2...script.2...script.2\nscript.2...script.2...script.2\nscript.2...script.2...script.2\n");
        vs.push_back("script.3...script.3...script.3\nscript.3...script.3...script.3\nscript.3...script.3...script.3\n");
        TextVector tv;
        tv.setTextVector(vs);
        TextVectorChangedEvent * event = new TextVectorChangedEvent();
        event->setAddress(EPAddress(this->entityID, this->deviceDescriptor.getNameChannelNrMap()["LBR100.INF.Scripts"]));
        event->setPayload(tv);
        eventSink->push(event);
    }

    {
        std::string text = "additional informaton  additional information  additional information";
        Text t;
        t.setText(text);
        TextChangedEvent * event = new TextChangedEvent();
        event->setAddress(EPAddress(this->entityID, this->deviceDescriptor.getNameChannelNrMap()["LBR100.INF.Additional"]));
        event->setPayload(t);
        eventSink->push(event);
    }
}


bool DummyDevLBR100::istGreiferAuf() {
    return this->channelNrAValueMap[this->deviceDescriptor.getNameChannelNrMap()[$POS_L]].getCurrentValue() == 25 &&
      this->channelNrAValueMap[this->deviceDescriptor.getNameChannelNrMap()[$POS_R]].getCurrentValue() == 25;
}


bool DummyDevLBR100::istGreiferZu() {
    return this->channelNrAValueMap[this->deviceDescriptor.getNameChannelNrMap()[$POS_L]].getCurrentValue() == 0 &&
          this->channelNrAValueMap[this->deviceDescriptor.getNameChannelNrMap()[$POS_R]].getCurrentValue() == 0;
}


void DummyDevLBR100::executeInputLoop() {

    this->engine.setOn(true);
    this->channelNrAValueMap[this->deviceDescriptor.getNameChannelNrMap()[$A1]].setTargetValue(100);

    this->inputLoopRunning = true;
    while (this->inputLoopRunning) {

#ifndef _WIN32
        fd_set rfds;
        struct timeval tv;
        int retval;

        FD_ZERO(&rfds);
        FD_SET(0, &rfds);

        //tv.tv_sec = 1;
        tv.tv_sec = 0;
        tv.tv_usec = 100000;
        retval = select(1, &rfds, 0, 0, &tv);
#endif

#ifdef _WIN32
        Sleep(100);
#endif
        this->engine.tick();
        if (this->engine.isOn()) {
            // invoke "tick" if the engine is on
            std::map<int, AValue>::iterator i = this->channelNrAValueMap.begin();
            std::map<int, AValue>::iterator e = this->channelNrAValueMap.end();
            while (i != e) {
                (*i).second.tick();
                ++i;
            }
        }

        if (this->eventSink) {
            // send the $AX, pox_x events
            std::map<int, AValue>::iterator i = this->channelNrAValueMap.begin();
            std::map<int, AValue>::iterator e = this->channelNrAValueMap.end();
            while (i != e) {
                AnalogChangedEvent * event = new AnalogChangedEvent();
                event->setAddress(EPAddress(this->entityID, (*i).first));
                event->setPayload((*i).second.getCurrentValue());
                eventSink->push(event);
                ++i;
            }

            if (this->stateTrigger) {
                {
                    this->greiferIstAuf = this->istGreiferAuf();
                    DigitalChangedEvent * event = new DigitalChangedEvent();
                    event->setAddress(EPAddress(this->entityID, this->greiferIstAufPortNr));
                    event->setPayload(greiferIstAuf);
                    eventSink->push(event);
                }
                {
                    this->greiferIstZu = this->istGreiferZu();
                    DigitalChangedEvent * event = new DigitalChangedEvent();
                    event->setAddress(EPAddress(this->entityID, this->greiferIstZuPortNr));
                    event->setPayload(greiferIstZu);
                    eventSink->push(event);
                }
                {
                    this->engineIsOn = this->engine.isOn();
                    DigitalChangedEvent * event = new DigitalChangedEvent();
                    event->setAddress(EPAddress(this->entityID, this->engineIsOnPortNr));
                    event->setPayload(engineIsOn);
                    eventSink->push(event);
                }

                this->stateTrigger = false;
            } else {
                {
                    bool state = this->istGreiferAuf();
                    if (this->greiferIstAuf != state) {
                        this->greiferIstAuf = state;
                        DigitalChangedEvent * event = new DigitalChangedEvent();
                        event->setAddress(EPAddress(this->entityID, this->greiferIstAufPortNr));
                        event->setPayload(greiferIstAuf);
                        eventSink->push(event);
                    }
                }
                {
                    bool state = this->istGreiferZu();
                    if (this->greiferIstZu != state) {
                        this->greiferIstZu = state;
                        DigitalChangedEvent * event = new DigitalChangedEvent();
                        event->setAddress(EPAddress(this->entityID, this->greiferIstZuPortNr));
                        event->setPayload(greiferIstZu);
                        eventSink->push(event);
                    }
                }
                {
                    bool state = this->engine.isOn();
                    if (this->engineIsOn != state) {
                        this->engineIsOn = state;
                        DigitalChangedEvent * event = new DigitalChangedEvent();
                        event->setAddress(EPAddress(this->entityID, this->engineIsOnPortNr));
                        event->setPayload(this->engineIsOn);
                        eventSink->push(event);
                    }
                }
            }
        }
    }
}


void DummyDevLBR100::executeOutputLoop() {



    this->outputLoopRunning = true;
    while (outputLoopRunning) {
        this->outputEventQueue.waitForData();
        IEvent * event = this->outputEventQueue.pop();
        if (event) {
            cout << "DummyDevLBR100: " << event->getEventTypeID() << " " << event << endl;

            if (event->getAddressTypeID() == EPAddress::AddressTypeID()) {
                IEventMsg<EPAddress> * e = static_cast<IEventMsg<EPAddress> *>(event);
                const EPAddress & address = e->getAddress();
                cout << "EPAddress: " << address << endl;

                  // handling AnalogChangedEvent
                if (event->getEventTypeID() == AnalogChangedEvent::EventTypeID()) {
                    AnalogChangedEvent * acEvent = static_cast<AnalogChangedEvent *>(event);

                    {
                          // Override Value
                        std::map<int, AValue>::iterator iter = this->channelNrAValueMap.find(address.getPortNr());
                        if (iter != this->channelNrAValueMap.end()) {
                            (*iter).second.setOverrideValue(acEvent->getPayload());
                        }
                    }
                    {
                          // Target Value
                        std::map<int, int>::iterator iter = this->channelNrInternalAValueNrMap.find(address.getPortNr());
                        if (iter != this->channelNrInternalAValueNrMap.end()) {
                            this->channelNrAValueMap[(*iter).second].setTargetValue(acEvent->getPayload());
                        }
                    }
                }

                  // handling DigitalChangedEvent
                if (event->getEventTypeID() == DigitalChangedEvent::EventTypeID()) {
                    DigitalChangedEvent * dcEvent = static_cast<DigitalChangedEvent *>(event);
                    if (this->enginePortNr == address.getPortNr()) {
                        this->engine.setOn(dcEvent->getPayload());
                    } else if (this->greiferAufPortNr == address.getPortNr()) {
                        this->channelNrAValueMap[this->deviceDescriptor.getNameChannelNrMap()[$POS_L]]
                            .setTargetValue(dcEvent->getPayload() ? 25 : 0);
                        this->channelNrAValueMap[this->deviceDescriptor.getNameChannelNrMap()[$POS_R]]
                            .setTargetValue(dcEvent->getPayload() ? 25 : 0);
                    } else if (this->stateTriggerPortNr == address.getPortNr()) {
                        this->stateTrigger = true;
                    }
                }
            }

            delete event;
        }
    }
}


void * DummyDevLBR100::outputLoopThread_run(void * arg) {
    printf("DummyDevLBR100 - output loop thread started\n");
    DummyDevLBR100 * dummyDevice = static_cast<DummyDevLBR100 *>(arg);
    dummyDevice->executeOutputLoop();
    return 0;
}

}

