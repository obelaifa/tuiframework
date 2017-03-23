#pragma once
#include <Windows.h>

#include <tuiframework/core/EventQueue.h>
#include <tuiframework/core/IDevice.h>
#include <tuiframework/core/IEventSink.h>
#include <tuiframework/server/DeviceDescriptor.h>

#include <tuitypes/common/CommonTypeReg.h>

#include <iostream>
#include <vector>
#include <Xinput.h>


namespace tuiframework {
    class ITUIServer;
}

namespace tuidevices{
	class XControllerDev : public tuiframework::IDevice, public tuiframework::IEventSink
	{
		public:
			XControllerDev(const tuiframework::DeviceConfig & deviceConfig);
			virtual ~XControllerDev();
		
			static IDevice * __cdecl createFunction(void * arg);
			static std::string __cdecl getDeviceName();

			 tuiframework::IEventSink * getEventSink() const;
			 int getEntityID() const;

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
		static void * inputLoopThread_run(void * arg);
		void executeInputLoop();

		//static void * outputLoopThread_run(void * arg);
		//void executeOutputLoop();

		//volatile bool outputLoopRunning;
		//pthread_t outputLoopThread;
		volatile bool inputLoopRunning;
		pthread_t inputLoopThread;

		//tuiframework::EventQueue outputEventQueue;

	private:
		tuiframework::DeviceDescriptor deviceDescriptor;

		int entityID;
		tuiframework::ITUIServer * tuiServer;
		tuiframework::IEventSink * eventSink;

		bool is_connected();
		// Activate vibration to Game-Controller 
		void Vibrate();
	};
}