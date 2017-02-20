#include  "PackedByteToByteMSP.h"

#include <tuiframework/core/Exception.h>
#define USE_TFDEBUG
#include <tuiframework/logging/Logger.h>

static const char * inTag = "in";
static const char * outTagValue = "out";
static const char * outTagPacked = "outPacked";


using namespace std;

namespace tuiframework {



	IMSP * PackedByteToByteMSP::createFunction(void * arg)
	{
		MSPConfig * config = static_cast<MSPConfig *>(arg);
		return new PackedByteToByteMSP(*config);
	}

	static std::string typeName = "PackedByteToByteMSP";


	std::string PackedByteToByteMSP::getMSPTypeName()
	{
		return typeName;
	}



	PackedByteToByteMSP::PackedByteToByteMSP(const MSPConfig & config) :
		config(config){

		this->eventDelegate.setReceiver(this, &PackedByteToByteMSP::handleEvent);

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

	PackedByteToByteMSP::~PackedByteToByteMSP()
	{
	}

	const std::string & PackedByteToByteMSP::getTypeName() const
	{
		return this->type.getTypeName();
	}

	IEventSink * PackedByteToByteMSP::getEventSink(const std::string & name)
	{
		if (name.compare(inTag) == 0) {
			return &eventDelegate;
		}
		return 0;
	}

	void PackedByteToByteMSP::registerEventSink(const std::string & name, IEventSink * eventSink)
	{
		map<string, int>::iterator iter = this->nameToIdMap.find(name);
		if (iter == this->nameToIdMap.end()) {
			return;
		}
		this->out[(*iter).second] = eventSink;
	}

	const MSPType & PackedByteToByteMSP::getMSPType() const
	{
		return this->type;
	}

	void PackedByteToByteMSP::handleEvent(PackedIntegerEvent * e)
	{
		if (this->out[0])
		{
			DigitalChangedEvent* event = new DigitalChangedEvent(-1, -1, e->getPayload().getItems().at(this->id).second);
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