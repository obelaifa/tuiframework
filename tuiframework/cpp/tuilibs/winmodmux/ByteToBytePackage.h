#pragma once
#include <tuiframework/server/MSPConfig.h>
#include <tuiframework/server/MSPType.h>
#include <tuitypes/common/CommonTypeReg.h>
#include <tuiframework/core/IMSP.h>
#include <tuiframework/core/EventDelegate.h>

namespace tuiframework {
	class ByteToBytePackage :
		public IMSP
	{
	public:
		ByteToBytePackage(const MSPConfig & config);
		~ByteToBytePackage();

		static IMSP * createFunction(void * arg);
		static std::string getMSPTypeName();

		virtual const std::string & getTypeName() const;
		virtual IEventSink * getEventSink(const std::string & name);
		virtual void registerEventSink(const std::string & name, IEventSink * eventSink);
		virtual const MSPType & getMSPType() const;

		void handleEvent(DigitalChangedEvent * e);
		void initEvent(const int & entityID, const int & portID);

	protected:
		MSPConfig config;
		MSPType type;

		EventDelegateNC<DigitalChangedEvent, ByteToBytePackage> eventDelegate;
		void initInTag();

		IEventSink * out;
		std::map<std::string, int> nameToIdMap;
		std::map<std::string, int> eventOrder;
		int index = 0;

		PackedType <int> packedByte;
		vector<std::string> inTag;
		int id;
		int byteSize;
	};
}
