#pragma once
#include <tuiframework/server/MSPConfig.h>
#include <tuiframework/server/MSPType.h>
#include <tuiframework/core/IMSP.h>
#include <tuiframework/core/EventDelegate.h>
#include <tuitypes/common/CommonTypeReg.h>

namespace tuiframework {

	class PackedByteToByteMSP :
		public IMSP
	{
	public:
		static IMSP * createFunction(void * arg);
		static std::string getMSPTypeName();

		PackedByteToByteMSP(const MSPConfig & config);
		~PackedByteToByteMSP();

		virtual const std::string & getTypeName() const;
		virtual IEventSink * getEventSink(const std::string & name);
		virtual void registerEventSink(const std::string & name, IEventSink * eventSink);
		virtual const MSPType & getMSPType() const;

		void handleEvent(PackedIntegerEvent * e);
	protected:
		MSPConfig config;
		MSPType type;

		EventDelegateNC<PackedIntegerEvent, PackedByteToByteMSP> eventDelegate;

		IEventSink * out[9];
		std::map<std::string, int> nameToIdMap;

		int id;
	};

}