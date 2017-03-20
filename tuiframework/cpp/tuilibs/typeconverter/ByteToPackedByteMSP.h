#pragma once
#include "../../tuiframework/server/MSPConfig.h"
#include "../../tuiframework/server/MSPType.h"
#include "../../tuiframework/core/IMSP.h"
#include "../../tuiframework/core/EventDelegate.h"
#include "../../TUIPlugins/tuitypes/common/CommonTypeReg.h"

namespace tuiframework {
	class ByteToPackedByteMSP :
		public IMSP
	{
	public:

		ByteToPackedByteMSP(const MSPConfig & config);
		~ByteToPackedByteMSP();
		static IMSP * createFunction(void * arg);
		static std::string getMSPTypeName();

		virtual const std::string & getTypeName() const;
		virtual IEventSink * getEventSink(const std::string & name);
		virtual void registerEventSink(const std::string & name, IEventSink * eventSink);
		virtual const MSPType & getMSPType() const;

		void handleEvent(PackedIntegerEvent * e);
		void handleEvent2(DigitalChangedEvent * e);

		void findIntToChange();
		std::vector<int> convertTobinary(int intToBinary);
		int convertToInt(std::vector<int> bitToInt);
		int changeByteVector();
	protected:
		MSPConfig config;
		MSPType type;


		EventDelegateNC < PackedIntegerEvent, ByteToPackedByteMSP > eventDelegate;
		EventDelegateNC < DigitalChangedEvent, ByteToPackedByteMSP > eventDelegate2;

		PackedType<int> packedInt;
		int eventDigital;
		IEventSink * out;
		std::map<std::string, int> nameToIdMap;

		int id;
		int size;
		int intToChange;


	};
}

