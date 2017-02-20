#include <xcontroller/XControllerDev.h>

#include <tuiframework/core/ITUIServer.h>
#include <tuiframework/core/IEvent.h>
#include <tuiframework/server/DeviceConfig.h>
#include <tuiframework/core/Exception.h>

#include <iostream>
#include <sstream>



using namespace tuiframework;
using namespace std;

namespace tuidevices 
{
	IDevice * __cdecl XControllerDev::createFunction(void * arg) 
	{
		DeviceConfig * deviceConfig = static_cast<DeviceConfig *>(arg);
		return new XControllerDev(*deviceConfig);
	}

	std::string XControllerDev::getDeviceName() {
    return "XControllerDevice";
}

}

namespace tuidevices {

XControllerDev::XControllerDev(const DeviceConfig & deviceConfig)
{
	this->deviceDescriptor.setEntityID(deviceConfig.getEntityID());
    this->entityID = this->deviceDescriptor.getEntityID();

    map<string, Port> portMap;

	// Mapping of Ports for Device Instance, maybe autogeneration based on XML-Configfile later
	portMap["x1"] = Port("x1", "XControllerChannel", Port::Source);
    portMap["x2"] = Port("x2", "XControllerChannel", Port::Source);
    portMap["x3"] = Port("x3", "XControllerChannel", Port::Source);
    portMap["x4"] = Port("x4", "XControllerChannel", Port::Source);

	DeviceType deviceType;
    deviceType.setPortMap(portMap);
    deviceType.setDeviceTypeName(getDeviceName());
    deviceType.setDescription("XController - Interface");
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

	try {
        //TFDEBUG("PortNr = " << this->portNr);
    }
    catch(Exception & e) {
        //TFERROR(e.getFormattedString());
    }

	//this->receiver.setMyPort(this->portNr);

    this->deviceDescriptor.setNameChannelNrMap(nameChannelNrMap);

}


XControllerDev::~XControllerDev(void)
{
}



tuiframework::IEventSink * XControllerDev::getEventSink() const {
    return this->eventSink;
}


int XControllerDev::getEntityID() const {
    return this->entityID;
}

// Creates a Thread for starting the Input- or OutputLoop or Both
bool XControllerDev::deviceExecute() 
{
	{
   //     int rc = pthread_create(&this->outputLoopThread, NULL, XControllerDev::outputLoopThread_run, this);
   //     if (rc) {
   //        printf("ERROR; return code from pthread_create() is %d\n", rc);
   //    }
    }

    {
        int rc = pthread_create(&this->inputLoopThread, NULL, XControllerDev::inputLoopThread_run, this);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
        }
    }

    return true;
}

// Stops the running threads
void XControllerDev::deviceStop()
{
 	pthread_cancel(this->inputLoopThread);
    pthread_join(this->inputLoopThread, 0);
    
//	pthread_cancel(this->outputLoopThread);
//  pthread_join(this->outputLoopThread, 0);
	printf("Closing...\n");
}

//Pushs a Event to a Queue 
void XControllerDev::push(IEvent * event) 
{
 //   this->outputEventQueue.push(event);
}


void XControllerDev::deviceConnect(tuiframework::ITUIServer & tuiServer) 
{
    tuiServer.tuiServerRegisterDevice(this->entityID, *this);
    tuiServer.tuiServerRegisterEventSink(this->entityID, *this);
    this->tuiServer = &tuiServer;
}


void XControllerDev::deviceDisconnect() 
{
    if (tuiServer) {
        this->tuiServer->tuiServerDeregisterDevice(this->entityID);
        this->tuiServer->tuiServerDeregisterEventSink(this->entityID);
        this->tuiServer = 0;
    }
}


void XControllerDev::deviceSetEventSink(tuiframework::IEventSink * eventSink) 
{
    this->eventSink = eventSink;
}


const DeviceDescriptor & XControllerDev::getDeviceDescriptor() const 
{
    return this->deviceDescriptor;
}

void * XControllerDev::inputLoopThread_run(void * arg) 
{
    printf("XControllerDev - input loop thread started\n");
    XControllerDev * xControllerDevice = static_cast<XControllerDev *>(arg);
    xControllerDevice->executeInputLoop();
    return 0;
}


void XControllerDev::executeInputLoop() 
{

	this->inputLoopRunning = true;


	while (this->inputLoopRunning) 
	{
		
		// Sleeptimer for interval controll
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
				Sleep(40); // 0,04 seconds
		#endif
		
	
		XControllerData xd(1); // Create a new XControllerData to store the ControllerStates

		// 1 ports supported
		if(xd.is_connected()) // Checks if an GamePad is connected
		{
			if (xd.getId() > 0 && xd.getId() <= 4)
			{
				XControllerEvent * e = new XControllerEvent(); // Generate a new Event from Type XControllerEvent
				e->setAddress(EPAddress(this->entityID, xd.getId()));
				e->setPayload(xd); //Sets a Value to Event,  XControllerEvent expects only Values from type XControllerData
				//TFDEBUG(e)
				eventSink->push(e); // Push the event to an eventsink
			}	
		}
		else
		{
			cout << "No XBox Controller Connected"<< endl;
		}
	}
}



}