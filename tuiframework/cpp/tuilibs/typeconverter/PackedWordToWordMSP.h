#pragma once
#include <tuiframework/server/MSPConfig.h>
#include <tuiframework/server/MSPType.h>
#include <tuiframework/core/IMSP.h>
#include <tuiframework/core/EventDelegate.h>

#include <tuitypes/common/CommonTypeReg.h>

namespace tuiframework {

	class PackedWordToWordMSP :
		public IMSP
	{
	public:
		static IMSP * createFunction(void * arg);
		static std::string getMSPTypeName();

		PackedWordToWordMSP(const MSPConfig & config);
		~PackedWordToWordMSP();

		virtual const std::string & getTypeName() const;
		virtual IEventSink * getEventSink(const std::string & name);
		virtual void registerEventSink(const std::string & name, IEventSink * eventSink);
		virtual const MSPType & getMSPType() const;

		void handleEvent(PackedWORDEvent * e);
	protected:
		MSPConfig config;
		MSPType type;

		EventDelegateNC<PackedWORDEvent, PackedWordToWordMSP> eventDelegate;

		IEventSink * out[2];
		std::map<std::string, int> nameToIdMap;

		int id;

	};

}