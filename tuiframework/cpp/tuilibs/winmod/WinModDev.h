#pragma once
#include <Windows.h>
#include <chrono>

#include <tuiframework/core/EventQueue.h>
#include <tuiframework/core/IDevice.h>
#include <tuiframework/core/IEventSink.h>
#include <tuiframework/server/DeviceDescriptor.h>
#include <tuitypes/common/CommonTypeReg.h>

#include <iostream>

// WinMod Y200-API
#include <Y200Clnt.h>

namespace tuiframework {
    class ITUIServer;
}

namespace tuidevices{

	/**
	 * \brief Class for a WinModDevice, used to read and write from/to WinMod
	 * 
	 * This Class is used for reading and writing Floats, Bytes, Words and DWord-Values from a
	 * WinMod-Project with Y200-Drivers. Using the Y200-API in this Class allow us to connect to the
	 * shared memorey managed by the Y200-Drivers.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * ### remarks Sebastian Keppler, 04.02.2016.
	 */

	class WinModDev : public tuiframework::IDevice, public tuiframework::IEventSink
	{
		public:

			/**
			 * \brief Constructor.
			 *
			 * \author Sebastian Keppler
			 * \date 04.02.2016
			 * 
			 * The Constructor if this class, used to create an instance of a WinModDevice.
			 *
			 * \param deviceConfig The device configuration.
			 */

			WinModDev(const tuiframework::DeviceConfig & deviceConfig);

			/**
			 * \brief Destructor
			 * 
			 * Destructor of this Class.
			 *
			 * \author Sebastian Keppler
			 * \date 04.02.2016
			 */

			virtual ~WinModDev();

			/**
			 * \brief Creates a function.
			 *
			 * \author Sebastian Keppler
			 * \date 04.02.2016
			 *
			 * \param [in,out] arg If non-null, the argument.
			 *
			 * \return null if it fails, else the new function.
			 */

			static IDevice * __cdecl createFunction(void * arg);

			/**
			 * \brief Gets device name.
			 *
			 * \author Sebastian Keppler
			 * \date 04.02.2016
			 *
			 * \return The device name.
			 */

			static std::string __cdecl getDeviceName();

			 /**
			  * \brief Gets event sink.
			  *
			  * \author Sebastian Keppler
			  * \date 04.02.2016
			  *
			  * \return null if it fails, else the event sink.
			  */

			 tuiframework::IEventSink * getEventSink() const;

			 /**
			  * \brief Gets entity identifier.
			  *
			  * \author Sebastian Keppler
			  * \date 04.02.2016
			  *
			  * \return The entity identifier.
			  */

			 int getEntityID() const;

			/**
			 * \brief IDevice.
			 *
			 * \author Sebastian Keppler
			 * \date 04.02.2016
			 *
			 * \param [in,out] tuiServer The tui server.
			 */

			virtual void deviceConnect(tuiframework::ITUIServer & tuiServer);

			/**
			 * \brief Device disconnect.
			 *
			 * \author Sebastian Keppler
			 * \date 04.02.2016
			 */

			virtual void deviceDisconnect();

			/**
			 * \brief Determines if we can device execute.
			 *
			 * \author Sebastian Keppler
			 * \date 04.02.2016
			 *
			 * \return true if it succeeds, false if it fails.
			 */

			virtual bool deviceExecute();

			/**
			 * \brief Device stop.
			 *
			 * \author Sebastian Keppler
			 * \date 04.02.2016
			 */

			virtual void deviceStop();

			/**
			 * \brief Device set event sink.
			 *
			 * \author Sebastian Keppler
			 * \date 04.02.2016
			 *
			 * \param [in,out] eventSink If non-null, the event sink.
			 */

			virtual void deviceSetEventSink(tuiframework::IEventSink * eventSink);

			/**
			 * \brief Gets device descriptor.
			 *
			 * \author Sebastian Keppler
			 * \date 04.02.2016
			 *
			 * \return The device descriptor.
			 */

			virtual const tuiframework::DeviceDescriptor & getDeviceDescriptor() const;

			/**
			 * \brief IEventSink.
			 *
			 * \author Sebastian Keppler
			 * \date 04.02.2016
			 *
			 * \param [in,out] event If non-null, the event to push.
			 */

			virtual void push(tuiframework::IEvent * event);

	protected:

		/**
		 * \brief Input loop thread run.
		 *
		 * \author Sebastian Keppler
		 * \date 04.02.2016
		 *
		 * \param [in,out] arg If non-null, the argument.
		 *
		 */

		static void * inputLoopThread_run(void * arg);

		/**
		 * \brief Executes the input loop operation.
		 *
		 * \author Sebastian Keppler
		 * \date 04.02.2016
		 */

		void executeInputLoop();

		/**
		 * \brief Output loop thread run.
		 * 
		 * \author Sebastian Keppler
		 * \date 04.02.2016
		 *
		 * \param [in,out] arg If non-null, the argument.
		 *
		 */

		static void * outputLoopThread_run(void * arg);

		/**
		 * \brief Executes the output loop operation.
		 *
		 * \author Sebastian Keppler
		 * \date 04.02.2016
		 */

		void executeOutputLoop();

		/** \brief true to output loop running. */
		volatile bool outputLoopRunning;

		/** \brief The output loop thread. */
		pthread_t outputLoopThread;
		
		/** \brief true to input loop running. */
		volatile bool inputLoopRunning;

		/** \brief The input loop thread. */
		pthread_t inputLoopThread;

		/** \brief Queue of output events. */
		tuiframework::EventQueue outputEventQueue;

	private:
		/**
		 * \brief Ipc string to lpctsrt.
		 *
		 * Convert a String of IPCName to LPCTSTR Format(not used?)
		 * \author Sebastian Keppler
		 * \date 04.02.2016
		 *
		 * \param ipcName Name of the ipc.
		 *
		 * \return A LPCTSTR.
		 */

		LPCTSTR ipcStringToLPCTSRT(std::string ipcName);
		
		/** \brief Information describing the device. */
		tuiframework::DeviceDescriptor deviceDescriptor;
		
		/** \brief Identifier for the entity. */
		int entityID;
		
		/** \brief The tui server. */
		tuiframework::ITUIServer * tuiServer;
		/** \brief The event sink. */
		tuiframework::IEventSink * eventSink;

		/** \brief The range-handler to connect to the shared memory. */
		WMY200RANGEHANDLE m_hRange;
		/** \brief IPCName of WinMod Shared-Memory (Not used?) */
		std::string ipcName;
		/** \brief Offset for Read-Block. */
		int readOffset;
		/** \brief Size of Read-Block. */
		int readSize;
		/** \brief Offset for Write-Block. */
		int writeOffset;
		/** \brief Size of Write-Block. */
		int writeSize;
		/** \brief Offset of Float-Values. */
		int floatOff;
		/** \brief Size of Float-Values. */
		int floatSize;
		/** \brief OffSet of Byte-Values(Buttons) */
		int byteOff;
		/** \brief Size of Byte-Values(Buttons) */
		int byteSize;
		/** \brief Offset of Word-Values. */
		int wordOff;
		/** \brief Size of Word-Size. */
		int wordSize;
		/** \brief Offset of DWord-Values. */
		int dWordOff;
		/** \brief Size of DwOrd-Values. */
		int dWordSize;
		PackedType<int> packedInteger;
	};
}