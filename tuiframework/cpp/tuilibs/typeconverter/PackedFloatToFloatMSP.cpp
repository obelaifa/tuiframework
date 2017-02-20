#include "PackedFloatToFloatMSP.h"

#include <tuiframework/core/Exception.h>
#define USE_TFDEBUG
#include <tuiframework/logging/Logger.h>

static const char * inTag = "in";
static const char * outTagValue = "out";
static const char * outTagPacked = "outPacked";

namespace tuiframework {
	IMSP * PackedFloatToFloatMSP::createFunction(void * arg)
	{
		MSPConfig * config = static_cast<MSPConfig *>(arg);
		return new PackedFloatToFloatMSP(*config);
	}

	static std::string typeName = "PackedFloatToFloatMSP";


	std::string PackedFloatToFloatMSP::getMSPTypeName()
	{
		return typeName;
	}

	PackedFloatToFloatMSP::PackedFloatToFloatMSP(const MSPConfig & config) :
		config(config){

		this->eventDelegate.setReceiver(this, &PackedFloatToFloatMSP::handleEvent);

		for (int i = 0; i < 2; ++i) {
			this->out[i] = 0;
		}
		this->nameToIdMap[outTagValue] = 0;
		this->nameToIdMap[outTagPacked] = 1;

		try {
			this->id = config.getParameterGroup().getInt("Convert|id");

			TFDEBUG("ID = " << this->id);

		}
		catch (Exception & e) {
			TFERROR(e.getFormattedString());
		}
	}

	PackedFloatToFloatMSP::~PackedFloatToFloatMSP()
	{
	}

	const std::string & PackedFloatToFloatMSP::getTypeName() const
	{
		return this->type.getTypeName();
	}

	IEventSink * PackedFloatToFloatMSP::getEventSink(const std::string & name)
	{
		if (name.compare(inTag) == 0) {
			return &eventDelegate;
		}
		return 0;
	}

	void PackedFloatToFloatMSP::registerEventSink(const std::string & name, IEventSink * eventSink)
	{
		map<string, int>::iterator iter = this->nameToIdMap.find(name);
		if (iter == this->nameToIdMap.end()) {
			return;
		}
		this->out[(*iter).second] = eventSink;
	}

	const MSPType & PackedFloatToFloatMSP::getMSPType() const
	{
		return this->type;
	}
	void PackedFloatToFloatMSP::handleEvent(PackedAnalogEvent * e)
	{
		if (this->out[0])
		{
			AnalogChangedEvent* event = new AnalogChangedEvent(-1, -1, e->getPayload().getItems().at(this->id).second);
			//for(int i=0;i<wd.getFloats().size();i++)
			//cout <<"MSPOut: Floats: "  << event2->getPayload().at(i)<< endl;

			this->out[0]->push(event);
		}

		if (this->out[1])
		{
			//for(int i=0;i<wd.getBytes().size();i++)
			//cout <<"MSPOut: Bytes: "  << event->getPayload().at(i)<< endl;
			this->out[1]->push(e);
		}
	}
}