#pragma once
#include <tuiframework/server/MSPConfig.h>
#include <tuiframework/server/MSPType.h>
#include <tuiframework/core/IMSP.h>
#include <tuiframework/core/EventDelegate.h>

#include <tuitypes/common/CommonTypeReg.h>

namespace tuiframework {

	class PackedFloatToFloatMSP :
		public IMSP
	{
	public:
		static IMSP * createFunction(void * arg);
		static std::string getMSPTypeName();

		PackedFloatToFloatMSP(const MSPConfig & config);
		~PackedFloatToFloatMSP();

		virtual const std::string & getTypeName() const;
		virtual IEventSink * getEventSink(const std::string & name);
		virtual void registerEventSink(const std::string & name, IEventSink * eventSink);
		virtual const MSPType & getMSPType() const;

		void handleEvent(PackedAnalogEvent * e);
	protected:
		MSPConfig config;
		MSPType type;

		EventDelegateNC<PackedAnalogEvent, PackedFloatToFloatMSP> eventDelegate;

		IEventSink * out[2];
		std::map<std::string, int> nameToIdMap;

		int id;

	};

}