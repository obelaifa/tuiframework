/*
    Copyright (C) 2010, 2011, 2012 The Fraunhofer Institute for Production Systems and
    Design Technology IPK. All rights reserved.

    This file is part of the TUIFramework library.
    It includes a software framework which contains common code
    providing generic functionality for developing applications
    with a tangible user interface (TUI).
    
    The TUIFramework library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    The TUIFramework is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with the TUIFramework.  If not, see <http://www.gnu.org/licenses/>.
*/



#ifndef _tuidevices_Matrix4CalibrationDev_h_
#define _tuidevices_Matrix4CalibrationDev_h_

#include <tuitypes/common/CommonTypeReg.h>
#include <tuiframework/server/DeviceDescriptor.h>

#include <tuiframework/core/EventQueue.h>
#include <tuiframework/core/IDevice.h>
#include <tuiframework/core/IEventSink.h>

#include <vector>
#include <pthread.h>

#include <map>

namespace tuiframework {
    class ITUIServer;
}

namespace tuidevices {


class Matrix4CalibrationDev  : public tuiframework::IDevice, public tuiframework::IEventSink {
public:
    static IDevice * createFunction(void * arg);
    static std::string getDeviceName();

    Matrix4CalibrationDev(const tuiframework::DeviceConfig & deviceConfig);
    virtual ~Matrix4CalibrationDev();

        // IDevice
    virtual void deviceConnect(tuiframework::ITUIServer & tuiServer);
    virtual void deviceDisconnect();
    virtual bool deviceExecute();
    virtual void deviceStop();
    virtual void deviceSetEventSink(tuiframework::IEventSink * eventSink);
    virtual const tuiframework::DeviceDescriptor & getDeviceDescriptor() const;

        // IEventSink
    virtual void push(tuiframework::IEvent * event);

protected:
    static void * senderThread_run(void * arg);
    void senderThreadLoop();

    static void * receiverThread_run(void * arg);
    void receiverThreadLoop();
    
protected:
    void handleVector1(Vector4Event * event);
    void handleVector2(Vector4Event * event);
    void applyVectors(DigitalChangedEvent * event);
    void clearVectors(DigitalChangedEvent * event);
    void loadCalibratedMatrix(DigitalChangedEvent * event);
    void saveCalibratedMatrix(DigitalChangedEvent * event);
    void sendCalibratedMatrix(DigitalChangedEvent * event);
    void calculateCalibratedMatrix(DigitalChangedEvent * event);
    
    void applyVectors();
        
protected:
    tuiframework::DeviceDescriptor deviceDescriptor;

    int entityID;
    tuiframework::ITUIServer * tuiServer;
    tuiframework::IEventSink * eventSink;

    volatile bool senderThreadActive;
    pthread_t senderThread;
    volatile bool receiverThreadActive;
    pthread_t receiverThread;

    tuiframework::EventQueue receiverEventQueue;
    
    bool initialSend;
    std::string calibratedMatrixPath;
    bool premultiply;
    bool useAverage;
    
protected:
    Vector4<double> vec1;
    int vec1Size;
    Vector4<double> vec2;
    int vec2Size;
    
    bool trackVectors;
    
    std::vector<std::pair<Vector4<double>, Vector4<double> > > vecPairVector;
    
    Matrix4<double> matrix;
};

}

#endif
