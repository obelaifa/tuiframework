#pragma once
#include <Windows.h>
#include <chrono>

#include <tuiframework/core/EventQueue.h>
#include <tuiframework/core/IDevice.h>
#include <tuiframework/core/IEventSink.h>
#include <tuiframework/server/DeviceDescriptor.h>

#include <tuitypes/common/CommonTypeReg.h>

#include <iostream>



namespace tuiframework {
	class ITUIServer;
}

namespace tuidevices {
	class DummyDevWinMod : public tuiframework::IDevice, public tuiframework::IEventSink
	{
	public:
		static IDevice * createFunction(void * arg);
		static std::string getDeviceName();

		DummyDevWinMod(const tuiframework::DeviceConfig & deviceConfig);
		virtual ~DummyDevWinMod();

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

		static void * outputLoopThread_run(void * arg);
		void executeOutputLoop();

		int timer;
		int floatSize;
		int boolSize;
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
	};

}