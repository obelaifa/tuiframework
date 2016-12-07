#include "DummyDevLBR100.h"

#include <tuiframework/core/ITUIServer.h>
#include <tuiframework/core/IEvent.h>
#include <tuiframework/server/DeviceConfig.h>


#include <cstdlib> // GCC 4.3 related build problem

#include <ctime>

#include <iostream>

#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

#include <cmath>

using namespace tuiframework;
using namespace std;



namespace tuidevices {


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

    portMap["LBR100.M01.$A1"] = Port("LBR100.M01.$A1", "AnalogChannel", Port::SourceAndSink);
    portMap["LBR100.M02.$A2"] = Port("LBR100.M02.$A2", "AnalogChannel", Port::SourceAndSink);
    portMap["LBR100.M03.$A3"] = Port("LBR100.M03.$A3", "AnalogChannel", Port::SourceAndSink);
    portMap["LBR100.M04.$A4"] = Port("LBR100.M04.$A4", "AnalogChannel", Port::SourceAndSink);
    portMap["LBR100.M05.$A5"] = Port("LBR100.M05.$A5", "AnalogChannel", Port::SourceAndSink);
    portMap["LBR100.M06.$A6"] = Port("LBR100.M06.$A6", "AnalogChannel", Port::SourceAndSink);
    portMap["LBR100.M07.$A7"] = Port("LBR100.M07.$A7", "AnalogChannel", Port::SourceAndSink);

    portMap["LBR100.GR.$pos_l"] = Port("LBR100.GR.$pos_l", "AnalogChannel", Port::SourceAndSink);
    portMap["LBR100.GR.$pos_r"] = Port("LBR100.GR.$pos_r", "AnalogChannel", Port::SourceAndSink);

    portMap["LBR100.CTR.AntriebeAn"] = Port("LBR100.CTR.AntriebeAn", "DigitalChannel", Port::Sink);
    portMap["LBR100.CTR.AntriebeSindAn"] = Port("LBR100.CTR.AntriebeSindAn", "DigitalChannel", Port::Source);

    portMap["LBR100.CTR.ExternStart"] = Port("LBR100.CTR.ExternStart", "DigitalChannel", Port::SourceAndSink);
    portMap["LBR100.CTR.GreiferIstAuf"] = Port("LBR100.CTR.GreiferIstAuf", "DigitalChannel", Port::Source);
    portMap["LBR100.CTR.GreiferIstZu"] = Port("LBR100.CTR.GreiferIstZu", "DigitalChannel", Port::Source);
    portMap["LBR100.CTR.GreiferAuf"] = Port("LBR100.CTR.GreiferAuf", "DigitalChannel", Port::SourceAndSink);

    portMap["LBR100.CTR.Soll_A1"] = Port("LBR100.CTR.Soll_A1", "AnalogChannel", Port::Sink);
    portMap["LBR100.CTR.Soll_A2"] = Port("LBR100.CTR.Soll_A2", "AnalogChannel", Port::Sink);
    portMap["LBR100.CTR.Soll_A3"] = Port("LBR100.CTR.Soll_A3", "AnalogChannel", Port::Sink);
    portMap["LBR100.CTR.Soll_A4"] = Port("LBR100.CTR.Soll_A4", "AnalogChannel", Port::Sink);
    portMap["LBR100.CTR.Soll_A5"] = Port("LBR100.CTR.Soll_A5", "AnalogChannel", Port::Sink);
    portMap["LBR100.CTR.Soll_A6"] = Port("LBR100.CTR.Soll_A6", "AnalogChannel", Port::Sink);
    portMap["LBR100.CTR.Soll_A7"] = Port("LBR100.CTR.Soll_A7", "AnalogChannel", Port::Sink);

    //portMap["LBR100.INF.Scripts"] = Port("LBR100.INF.Scripts", "TextVectorChannel", Port::Source, "WinMod Scripts");
    //portMap["LBR100.INF.Additional"] = Port("LBR100.INF.Additional", "TextChannel", Port::Source, "Zusatzinformationen");

    portMap["LBR100.CMD.StateTrigger"] = Port("LBR100.CMD.StateTrigger", "DigitalChannel", Port::Sink);

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

    this->enginePortNr = this->deviceDescriptor.getNameChannelNrMap()["LBR100.CTR.AntriebeAn"];
    this->greiferAufPortNr = this->deviceDescriptor.getNameChannelNrMap()["LBR100.CTR.GreiferAuf"];
    this->stateTriggerPortNr = this->deviceDescriptor.getNameChannelNrMap()["LBR100.CMD.StateTrigger"];
    this->greiferIstAufPortNr = this->deviceDescriptor.getNameChannelNrMap()["LBR100.CTR.GreiferIstAuf"];
    this->greiferIstZuPortNr = this->deviceDescriptor.getNameChannelNrMap()["LBR100.CTR.GreiferIstZu"];
    this->engineIsOnPortNr = this->deviceDescriptor.getNameChannelNrMap()["LBR100.CTR.AntriebeSindAn"];

    this->channelNrAValueMap[nameChannelNrMap["LBR100.M01.$A1"]] = AValue();
    this->channelNrAValueMap[nameChannelNrMap["LBR100.M01.$A2"]] = AValue();
    this->channelNrAValueMap[nameChannelNrMap["LBR100.M01.$A3"]] = AValue();
    this->channelNrAValueMap[nameChannelNrMap["LBR100.M01.$A4"]] = AValue();
    this->channelNrAValueMap[nameChannelNrMap["LBR100.M01.$A5"]] = AValue();
    this->channelNrAValueMap[nameChannelNrMap["LBR100.M01.$A6"]] = AValue();
    this->channelNrAValueMap[nameChannelNrMap["LBR100.M01.$A7"]] = AValue();
    this->channelNrAValueMap[nameChannelNrMap["LBR100.GR.$pos_l"]] = AValue();
    this->channelNrAValueMap[nameChannelNrMap["LBR100.GR.$pos_r"]] = AValue();

    this->channelNrInternalAValueNrMap[nameChannelNrMap["LBR100.CTR.Soll_A1"]] = nameChannelNrMap["LBR100.M01.$A1"];
    this->channelNrInternalAValueNrMap[nameChannelNrMap["LBR100.CTR.Soll_A2"]] = nameChannelNrMap["LBR100.M01.$A2"];
    this->channelNrInternalAValueNrMap[nameChannelNrMap["LBR100.CTR.Soll_A3"]] = nameChannelNrMap["LBR100.M01.$A3"];
    this->channelNrInternalAValueNrMap[nameChannelNrMap["LBR100.CTR.Soll_A4"]] = nameChannelNrMap["LBR100.M01.$A4"];
    this->channelNrInternalAValueNrMap[nameChannelNrMap["LBR100.CTR.Soll_A5"]] = nameChannelNrMap["LBR100.M01.$A5"];
    this->channelNrInternalAValueNrMap[nameChannelNrMap["LBR100.CTR.Soll_A6"]] = nameChannelNrMap["LBR100.M01.$A6"];
    this->channelNrInternalAValueNrMap[nameChannelNrMap["LBR100.CTR.Soll_A7"]] = nameChannelNrMap["LBR100.M01.$A7"];
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


void DummyDevLBR100::sendInfoEvents2() {
    {
        std::vector<std::string> vs;
        vs.push_back("script.1...script.1...script.1\nscript.1...script.1...script.1\nscript.1...script.1...script.1\n");
        vs.push_back("script.2...script.2...script.2\nscript.2...script.2...script.2\nscript.2...script.2...script.2\n");
        vs.push_back("script.3...script.3...script.3\nscript.3...script.3...script.3\nscript.3...script.3...script.3\n");
        TextVector tv;
        tv.setTextVector(vs);
        TextVectorChangedEvent * event = new TextVectorChangedEvent();
        event->setAddress(EPAddress(this->entityID, this->deviceDescriptor.getNameChannelNrMap()["HT100.02|info.Scripts"]));
        event->setPayload(tv);
        eventSink->push(event);
    }

    {
        std::string text = "additional informaton  additional information  additional information";
        Text t;
        t.setText(text);
        TextChangedEvent * event = new TextChangedEvent();
        event->setAddress(EPAddress(this->entityID, this->deviceDescriptor.getNameChannelNrMap()["HT100.02|info.Additional"]));
        event->setPayload(t);
        eventSink->push(event);
    }
}


void DummyDevLBR100::executeInputLoop() {

    this->inputLoopRunning = true;
    while (this->inputLoopRunning) {

#ifndef _WIN32
        fd_set rfds;
        struct timeval tv;
        int retval;

        FD_ZERO(&rfds);
        FD_SET(0, &rfds);

        tv.tv_sec = 0;
        tv.tv_usec = 300000;
        retval = select(1, &rfds, 0, 0, &tv);
#endif

#ifdef _WIN32
        Sleep(1000);
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

            for (int i = 0; i < AVALUE_SIZE; ++i) {
                this->aValue[i].tick();
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
                    this->greiferIstAuf = this->aValue[7].getCurrentValue() == 25 && this->aValue[8].getCurrentValue() == 25;
                    DigitalChangedEvent * event = new DigitalChangedEvent();
                    event->setAddress(EPAddress(this->entityID, this->greiferIstAufPortNr));
                    event->setPayload(greiferIstAuf);
                }
                {
                    this->greiferIstZu = this->aValue[7].getCurrentValue() == 0 && this->aValue[8].getCurrentValue() == 0;
                    DigitalChangedEvent * event = new DigitalChangedEvent();
                    event->setAddress(EPAddress(this->entityID, this->greiferIstZuPortNr));
                    event->setPayload(greiferIstZu);
                }
                {
                    this->engineIsOn = this->engine.isOn();
                    DigitalChangedEvent * event = new DigitalChangedEvent();
                    event->setAddress(EPAddress(this->entityID, this->engineIsOnPortNr));
                    event->setPayload(engineIsOn);
                }
            } else {
                {
                    bool state = this->aValue[7].getCurrentValue() == 25 && this->aValue[8].getCurrentValue() == 25;
                    if (this->greiferIstAuf != state) {
                        this->greiferIstAuf = state;
                        DigitalChangedEvent * event = new DigitalChangedEvent();
                        event->setAddress(EPAddress(this->entityID, this->greiferIstAufPortNr));
                        event->setPayload(greiferIstAuf);
                    }
                }
                {
                    bool state = this->aValue[7].getCurrentValue() == 25 && this->aValue[8].getCurrentValue() == 25;
                    if (this->greiferIstZu != state) {
                        this->greiferIstZu = state;
                        DigitalChangedEvent * event = new DigitalChangedEvent();
                        event->setAddress(EPAddress(this->entityID, this->greiferIstZuPortNr));
                        event->setPayload(greiferIstZu);
                    }
                }
                {
                    bool state = this->engine.isOn();
                    if (this->engineIsOn != state) {
                        this->engineIsOn = state;
                        DigitalChangedEvent * event = new DigitalChangedEvent();
                        event->setAddress(EPAddress(this->entityID, this->engineIsOnPortNr));
                        event->setPayload(this->engineIsOn);
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
                        std::map<int, AValue>::iterator iter = this->channelNrAValueMap.find(address.getPortNr());
                        if (iter != this->channelNrAValueMap.end()) {
                            (*iter).second.setOverrideValue(acEvent->getPayload());
                        }
                    }
                    {
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
                        this->aValue[7].setTargetValue(dcEvent->getPayload() ? 25 : 0);
                        this->aValue[8].setTargetValue(dcEvent->getPayload() ? 25 : 0);
                    } else if (this->stateTriggerPortNr == address.getPortNr()) {
                        this->stateTrigger = true;
                    }
                }
            }

            //delete event;
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

