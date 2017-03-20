#pragma once
#include "../../tuiframework/server/MSPConfig.h"
#include "../../tuiframework/server/MSPType.h"
#include "../../TUIPlugins/tuitypes/common/CommonTypeReg.h"
#include "../../tuiframework/core/IMSP.h"
#include "../../tuiframework/core/EventDelegate.h"

namespace tuiframework {
class FloatToPackedFloatMSP : 
	public IMSP
{
	public:

		FloatToPackedFloatMSP(const MSPConfig & config);
		~FloatToPackedFloatMSP();
		static IMSP * createFunction(void * arg);
		static std::string getMSPTypeName();

		virtual const std::string & getTypeName() const;
		virtual IEventSink * getEventSink(const std::string & name);
		virtual void registerEventSink(const std::string & name, IEventSink * eventSink);
		virtual const MSPType & getMSPType() const;

		void handleEvent(PackedAnalogEvent * e);
		void handleEvent2(AnalogChangedEvent * e);
	protected:
		MSPConfig config;
		MSPType type;


		EventDelegateNC < PackedAnalogEvent,  FloatToPackedFloatMSP > eventDelegate;
		EventDelegateNC < AnalogChangedEvent, FloatToPackedFloatMSP > eventDelegate2;

		PackedType<float> packedFloat;
		float eventAnalog;
		IEventSink * out;
		std::map<std::string, int> nameToIdMap;

		int id;
		int size;



};
}

