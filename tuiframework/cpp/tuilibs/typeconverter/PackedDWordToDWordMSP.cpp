#include "PackedDWordToDWordMSP.h"

#include <tuiframework/core/Exception.h>
#define USE_TFDEBUG
#include <tuiframework/logging/Logger.h>

static const char * inTag = "in";
static const char * outTagValue = "out";
static const char * outTagPacked = "outPacked";

namespace tuiframework {
	IMSP * PackedDWordToDWordMSP::createFunction(void * arg)
	{
		MSPConfig * config = static_cast<MSPConfig *>(arg);
		return new PackedDWordToDWordMSP(*config);
	}

	static std::string typeName = "PackedDWordToDWordMSP";


	std::string PackedDWordToDWordMSP::getMSPTypeName()
	{
		return typeName;
	}



	PackedDWordToDWordMSP::PackedDWordToDWordMSP(const MSPConfig & config) :
		config(config){

		this->eventDelegate.setReceiver(this, &PackedDWordToDWordMSP::handleEvent);
		
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

	PackedDWordToDWordMSP::~PackedDWordToDWordMSP()
	{
	}

	const std::string & PackedDWordToDWordMSP::getTypeName() const
	{
		return this->type.getTypeName();
	}

	IEventSink * PackedDWordToDWordMSP::getEventSink(const std::string & name)
	{
		if (name.compare(inTag) == 0) {
			return &eventDelegate;
		}
		return 0;
	}

	void PackedDWordToDWordMSP::registerEventSink(const std::string & name, IEventSink * eventSink)
	{
		map<string, int>::iterator iter = this->nameToIdMap.find(name);
		if (iter == this->nameToIdMap.end()) {
			return;
		}
		this->out[(*iter).second] = eventSink;
	}

	const MSPType & PackedDWordToDWordMSP::getMSPType() const
	{
		return this->type;
	}

	void PackedDWordToDWordMSP::handleEvent(PackedDWORDEvent * e)
	{
		if (this->out[0])
		{
			DWordChangedEvent* event = new DWordChangedEvent(-1, -1, e->getPayload().getItems().at(this->id).second);
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