#include <tuiframework/core/ITUIServer.h>
#include <tuiframework/core/IEvent.h>
#include <tuiframework/server/DeviceConfig.h>

#include <cstdlib> // GCC 4.3 related build problem

#include <ctime>

#include <iostream>
#include <bitset>

#ifdef _WIN32
#include <windows.h>
#endif



#include "DummyDevWinMod.h"

using namespace tuiframework;
using namespace std;

namespace tuidevices
{
	IDevice * DummyDevWinMod::createFunction(void * arg) {
		DeviceConfig * deviceConfig = static_cast<DeviceConfig *>(arg);
		return new DummyDevWinMod(*deviceConfig);
	}


	std::string DummyDevWinMod::getDeviceName() {
		return "DummyDeviceWinMod";
	}


	DummyDevWinMod::DummyDevWinMod(const DeviceConfig & deviceConfig)
	{
		this->deviceDescriptor.setEntityID(deviceConfig.getEntityID());
		this->entityID = this->deviceDescriptor.getEntityID();

		map<string, Port> portMap;

		// Port Mapping of In-/Output Ports
		portMap["wO"] = Port("wO", "WinModChannel", Port::Sink);
		portMap["wI"] = Port("wI", "WinModChannel", Port::Source);

		portMap["wordOutput"] = Port("wordOutput", "PackedWord", Port::Sink);
		portMap["dwordOutput"] = Port("dwordOutput", "PackedDWord", Port::Sink);
		portMap["analogOutput"] = Port("analogOutput", "PackedAnalog", Port::Sink);
		portMap["byteOutput"] = Port("byteOutput", "PackedInteger", Port::Sink);

		DeviceType deviceType;
		deviceType.setPortMap(portMap);
		deviceType.setDeviceTypeName(getDeviceName());
		deviceType.setDescription("DummyWinMod - Interface");
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


		this->timer = deviceConfig.getParameterGroup().getInt("Client|timer");
		this->floatSize = deviceConfig.getParameterGroup().getInt("Client|floatSize");
		this->boolSize = deviceConfig.getParameterGroup().getInt("Client|boolSize");


		//this->receiver.setMyPort(this->portNr);

		this->deviceDescriptor.setNameChannelNrMap(nameChannelNrMap);
	}


	DummyDevWinMod::~DummyDevWinMod()
	{
	}


	bool DummyDevWinMod::deviceExecute() {

		/*
		{
			// Starts the Output-Thread
			int rc = pthread_create(&this->outputLoopThread, NULL, DummyDevWinMod::outputLoopThread_run, this);
			if (rc)
			{
				printf("ERROR; return code from pthread_create() is %d\n", rc);
			}

		}*/

		{
			// Starts the Input-Thread
			int rc = pthread_create(&this->inputLoopThread, NULL, DummyDevWinMod::inputLoopThread_run, this);
			if (rc) {
				printf("ERROR; return code from pthread_create() is %d\n", rc);
			}

		}

		return true;
	}


	void DummyDevWinMod::deviceStop() {
		// Stops Input-Thread
		pthread_cancel(this->inputLoopThread);
		pthread_join(this->inputLoopThread, 0);

		// Stops Output-Thread
		pthread_cancel(this->outputLoopThread);
		pthread_join(this->outputLoopThread, 0);

		printf("Closing...\n");
	}


	void DummyDevWinMod::push(IEvent * event) {
		// Pushes an Event to the output Queue
		this->outputEventQueue.push(event);
	}

	void DummyDevWinMod::deviceConnect(tuiframework::ITUIServer & tuiServer) {
		// Making known this WinMod-Device-Type to the TUIServer 
		tuiServer.tuiServerRegisterDevice(this->entityID, *this);
		tuiServer.tuiServerRegisterEventSink(this->entityID, *this);
		this->tuiServer = &tuiServer;
	}


	void DummyDevWinMod::deviceDisconnect() {
		// Disconnects this WinMod-Device-Type from the TUIServer
		if (tuiServer) {
			this->tuiServer->tuiServerDeregisterDevice(this->entityID);
			this->tuiServer->tuiServerDeregisterEventSink(this->entityID);
			this->tuiServer = 0;
		}
	}


	void DummyDevWinMod::deviceSetEventSink(tuiframework::IEventSink * eventSink)
	{
		this->eventSink = eventSink;
	}


	const DeviceDescriptor & DummyDevWinMod::getDeviceDescriptor() const {
		return this->deviceDescriptor;
	}

	void * DummyDevWinMod::inputLoopThread_run(void * arg) {
		printf("WinModDummy - input loop thread started\n");
		DummyDevWinMod * dummyDevWinMod = static_cast<DummyDevWinMod *>(arg);
		dummyDevWinMod->executeInputLoop();
		return 0;
	}


	void DummyDevWinMod::executeInputLoop()
	{
		this->inputLoopRunning = true;
		WinModData wd;

		
		vector<float> floatVector;
		int min = -100;
		int max = 100;


		PackedType<float> pf;
		vector<pair<int, float > > & vf = pf.getItems();

		for (int i = 0; i < floatSize; ++i)
		{
			float randomValue = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - (min))));
			vf.push_back(pair<int, float > (i,randomValue));
		}
		

		
		//vector<bool> boolVector;
		PackedType<int> pi;
		vector< pair<int, int> > & vi = pi.getItems();
		vector<unsigned char> vb;
		for (int i = 0; i < boolSize; ++i)
		{
			if (rand() % 2)
			{
				//vb.push_back(true);
				vi.push_back(pair<int, int >(i,true));
			}
			else
			{
				//vb.push_back(false);
				vi.push_back(pair<int, int >(i,false));
			}
		}		
		
		//unsigned char byteArray[10] = {};
		//unsigned short wordArray[10] = {};
		//unsigned long DWordArray[10] = {};

		while (this->inputLoopRunning)
		{
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
						Sleep(timer);
			#endif

			if (this->eventSink)
			{
				int randomPosition = rand() % floatSize;

				float randomValue = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - (min))));
				//v.push_back(pair<int, float > (i,randomValue));
				vf.at(randomPosition).second = randomValue;
				PackedAnalogEvent *event = new PackedAnalogEvent();
				event->setAddress(EPAddress(this->entityID, this->deviceDescriptor.getNameChannelNrMap()["analogOutput"]));
				event->setPayload(pf);
				//cout << "Float Event: "<< event->getPayload() << endl;;
				eventSink->push(event);

				// Boolean
				randomPosition = rand() % boolSize;

				bool randomBoolean = rand() % 2;
				BYTE b = randomBoolean;
				vi.at(randomPosition).second = randomBoolean;

				//PackedIntegerEvent *event2 = new PackedIntegerEvent();
				//event2->setAddress(EPAddress(this->entityID, this->deviceDescriptor.getNameChannelNrMap()["byteOutput"]));
				//event2->setPayload(pi);
				//cout << "Byte Event: " << event2->getPayload() << endl;;

				//eventSink->push(event2);
			}
			//if(rand()%2)
			//{
			// Random Float-Values
			//int randomPosition = rand() % floatSize;
			//float randomValue = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - (min))));
			//cout << randomPosition << endl;
			//floatVector.at(randomPosition) = randomValue;
			//wd.setFloats(&floatVector[0], floatSize);
			
			//}
			/*
			else
			{
				// Random Boolean-Values
				// Random Float-Values
				int randomPosition = rand() % boolSize;
				//cout << randomPosition << endl;
				bool randomValue = rand() % 2;
				boolVector.at(randomPosition) = randomValue;

				//wd.setBytes(&boolVector[0], boolSize);
			}
			*/


			// Create a new WinModEvent
			//WinModEvent *event = new WinModEvent();
			// Set Address of the WinMod Event
			//event->setAddress(EPAddress(this->entityID, this->deviceDescriptor.getNameChannelNrMap()["wO"]));
			// Set the WinMod-Data Object as Payload for the Event
			//event->setPayload(wd);
			//if(eventSink)
			//{
				// Pushes the Event in the EventSink
			//	eventSink->push(event);
			//}
			// Delete to avoid Memory-Leak
			//delete event;
		}		
	}

	void DummyDevWinMod::executeOutputLoop() 
	{

		this->outputLoopRunning = true;

		while (outputLoopRunning)
		{
		
		}
	}

	void * DummyDevWinMod::outputLoopThread_run(void * arg)
	{
		printf("WinModDevDA - output loop thread started\n");
		DummyDevWinMod * dummyDevWinMod = static_cast<DummyDevWinMod *>(arg);
		dummyDevWinMod->executeOutputLoop();

		return 0;
	}
}
