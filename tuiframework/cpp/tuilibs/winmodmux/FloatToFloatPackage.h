#pragma once
#include <tuiframework/server/MSPConfig.h>
#include <tuiframework/server/MSPType.h>
#include <tuitypes/common/CommonTypeReg.h>
#include <tuiframework/core/IMSP.h>
#include <tuiframework/core/EventDelegate.h>

namespace tuiframework {
	class FloatToFloatPackage :
		public IMSP
	{
	public:
		FloatToFloatPackage(const MSPConfig & config);
		~FloatToFloatPackage();

		static IMSP * createFunction(void * arg);
		static std::string getMSPTypeName();

		virtual const std::string & getTypeName() const;
		virtual IEventSink * getEventSink(const std::string & name);
		virtual void registerEventSink(const std::string & name, IEventSink * eventSink);
		virtual const MSPType & getMSPType() const;

		void handleEvent(AnalogChangedEvent * e);
		void initEvent(const int & entityID, const int & portID);

	protected:
		MSPConfig config;
		MSPType type;

		EventDelegateNC<AnalogChangedEvent, FloatToFloatPackage> eventDelegate;
		void initInTag();

		IEventSink * out;
		std::map<std::string, int> nameToIdMap;
		std::map<std::string, int> eventOrder;
		int index = 0;
		vector < std::string > inTag;

		PackedType <float> packedFloat;
		int id;
		int floatSize;
	};
}
