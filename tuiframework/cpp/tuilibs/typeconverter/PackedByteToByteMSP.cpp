#include "PackedByteToByteMSP.h"

#include "../../tuiframework/core/Exception.h"
#define USE_TFDEBUG
#include "../../tuiframework/logging/Logger.h"

static const char * inTag = "in";
static const char * bit0TagValue = "bit0";
static const char * bit1TagValue = "bit1";
static const char * bit2TagValue = "bit2";
static const char * bit3TagValue = "bit3";
static const char * bit4TagValue = "bit4";
static const char * bit5TagValue = "bit5";
static const char * bit6TagValue = "bit6";
static const char * bit7TagValue = "bit7";
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

		for (int i = 0; i < 9; ++i) {
			this->out[i] = 0;
		}
		this->nameToIdMap[outTagPacked] = 8;
		this->nameToIdMap[bit0TagValue] = 0;
		this->nameToIdMap[bit1TagValue] = 1;
		this->nameToIdMap[bit2TagValue] = 2;
		this->nameToIdMap[bit3TagValue] = 3;
		this->nameToIdMap[bit4TagValue] = 4;
		this->nameToIdMap[bit5TagValue] = 5;
		this->nameToIdMap[bit6TagValue] = 6;
		this->nameToIdMap[bit7TagValue] = 7;

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
		for (int i = 0; i < 8; i++)
		{
			if (this->out[i])
			{
				int div = std::pow(2, i);
				int bit = ((e->getPayload().getItems().at(this->id).second)/div) % 2;
				DigitalChangedEvent* event = new DigitalChangedEvent(-1, -1, bit);
				//cout << "bit numero 0 : " << bit0 << endl;
				this->out[i]->push(event);
			}

		}
		
		/*if (this->out[0])
		{
			int bit0 = (e->getPayload().getItems().at(this->id).second )% 2;
			DigitalChangedEvent* event = new DigitalChangedEvent(-1, -1, bit0);
			//cout << "bit numero 0 : " << bit0 << endl;
			this->out[0]->push(event);
		}

		if (this->out[1])
		{
			int bit1= ( (e->getPayload().getItems().at(this->id).second)/2)% 2;
			DigitalChangedEvent* event = new DigitalChangedEvent(-1, -1, bit1);
			//cout << "bit numero 1 : " << bit1 << endl;

			this->out[1]->push(event);
		}

		if (this->out[2])
		{
			int bit2 = (((e->getPayload().getItems().at(this->id).second) / 2)/2) % 2;
			DigitalChangedEvent* event = new DigitalChangedEvent(-1, -1, bit2);
			//cout << "bit numero 2 : " << bit2 << endl;

			this->out[2]->push(event);
		}

		if (this->out[3])
		{
			int bit3 = ((((e->getPayload().getItems().at(this->id).second) / 2) / 2) /2) % 2;
			DigitalChangedEvent* event = new DigitalChangedEvent(-1, -1, bit3);
			//cout << "bit numero 3 : " << bit3 << endl;
			this->out[3]->push(event);
		}
		if (this->out[4])
		{
			int bit4 = (((((e->getPayload().getItems().at(this->id).second) / 2) / 2) / 2) /2) % 2;
			DigitalChangedEvent* event = new DigitalChangedEvent(-1, -1, bit4);
			//cout << "bit numero 4 : " << bit4 << endl;
			this->out[4]->push(event);
		}

		if (this->out[5])
		{
			int bit5 = ((((((e->getPayload().getItems().at(this->id).second) / 2) / 2) / 2) / 2) /2) % 2;
			DigitalChangedEvent* event = new DigitalChangedEvent(-1, -1, bit5);
			//cout << "bit numero 5 : " << bit5 << endl;

			this->out[5]->push(event);
		}
		if (this->out[6])
		{
			int bit6 = (((((((e->getPayload().getItems().at(this->id).second) / 2) / 2) / 2) / 2) / 2) /2) % 2;
			DigitalChangedEvent* event = new DigitalChangedEvent(-1, -1, bit6);
			//cout << "bit numero 6 : " << bit6 << endl;
			//for(int i=0;i<wd.getFloats().size();i++)
			//cout <<"MSPOut: Floats: "  << event2->getPayload().at(i)<< endl;

			this->out[6]->push(event);
		}

		if (this->out[7])
		{
			int bit7 = ((((((((e->getPayload().getItems().at(this->id).second) / 2) / 2) / 2) / 2) / 2) / 2) /2) % 2;
			DigitalChangedEvent* event = new DigitalChangedEvent(-1, -1, bit7);
			//cout << "bit numero 7 : " << bit7 << endl;
			//for(int i=0;i<wd.getFloats().size();i++)
			//cout <<"MSPOut: Floats: "  << event2->getPayload().at(i)<< endl;

			this->out[7]->push(event);
		}*/




		if (this->out[8])
		{
			this->out[8]->push(e);
			//cout << "packedInteger : " << endl;
		}
	}
}