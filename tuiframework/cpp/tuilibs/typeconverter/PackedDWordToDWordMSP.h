#pragma once
#include <tuiframework/server/MSPConfig.h>
#include <tuiframework/server/MSPType.h>
#include <tuiframework/core/IMSP.h>
#include <tuiframework/core/EventDelegate.h>

#include <tuitypes/common/CommonTypeReg.h>

namespace tuiframework {

	class PackedDWordToDWordMSP :
		public IMSP
	{
	public:
		static IMSP * createFunction(void * arg);
		static std::string getMSPTypeName();

		PackedDWordToDWordMSP(const MSPConfig & config);
		~PackedDWordToDWordMSP();

		virtual const std::string & getTypeName() const;
		virtual IEventSink * getEventSink(const std::string & name);
		virtual void registerEventSink(const std::string & name, IEventSink * eventSink);
		virtual const MSPType & getMSPType() const;

		void handleEvent(PackedDWORDEvent * e);
	protected:
		MSPConfig config;
		MSPType type;

		EventDelegateNC<PackedDWORDEvent, PackedDWordToDWordMSP> eventDelegate;

		IEventSink * out[2];
		std::map<std::string, int> nameToIdMap;

		int id;

	};

}