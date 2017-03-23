#include "FloatToPackedFloatMSP.h"
#include "../../tuiframework/core/Exception.h"
#define USE_TFDEBUG
#include "../../TUIFramework/logging/Logger.h"

static const char * inTag = "in";
static const char * inTagPacked = "inPacked";
static const char * outTagPacked = "outPacked";

namespace tuiframework {

	IMSP * FloatToPackedFloatMSP::createFunction(void * arg)
	{
		MSPConfig * config = static_cast<MSPConfig *>(arg);
		return new FloatToPackedFloatMSP(*config);
	}

	static std::string typeName = "FloatToPackedFloatMSP";


	std::string FloatToPackedFloatMSP::getMSPTypeName()
	{
		return typeName;
	}

	FloatToPackedFloatMSP::FloatToPackedFloatMSP(const MSPConfig & config) 
		:config(config), eventAnalog(INT32_MIN) 
	{

		this->out= 0;

		this->nameToIdMap[outTagPacked] = 0;

		try {
			this->id = config.getParameterGroup().getInt("Convert|id");
			this->size = config.getParameterGroup().getInt("Convert|size");
			
			TFDEBUG("ID = " << this->id);
			TFDEBUG("size = " << this->size);

		}
		catch (Exception & e) {
			TFERROR(e.getFormattedString());
		}

		this->eventDelegate.setReceiver(this, &FloatToPackedFloatMSP::handleEvent);
		this->eventDelegate2.setReceiver(this, &FloatToPackedFloatMSP::handleEvent2);

		std::vector<std::pair<int, float>> floatVector;
		for (int i = 0; i < this->size; i++)
		{
			floatVector.push_back(pair<int, float >(i, INT32_MIN));
		}
		packedFloat.setItems(floatVector);

	}

	FloatToPackedFloatMSP::~FloatToPackedFloatMSP()
	{
	}

	const std::string & FloatToPackedFloatMSP::getTypeName() const
	{
		return this->type.getTypeName();
	}

	IEventSink * FloatToPackedFloatMSP::getEventSink(const std::string & name)
	{
		if (name.compare(inTag) == 0) {
			return &eventDelegate2;
		}
		if (name.compare(inTagPacked) == 0) {
			return &eventDelegate;
		}
		return 0;
	}

	void FloatToPackedFloatMSP::registerEventSink(const std::string & name, IEventSink * eventSink)
	{
		map<string, int>::iterator iter = this->nameToIdMap.find(name);
		if (iter == this->nameToIdMap.end()) {
			return;
		}
		this->out = eventSink;
	}

	const MSPType & FloatToPackedFloatMSP::getMSPType() const
	{
		return this->type;
	}
	void FloatToPackedFloatMSP::handleEvent(PackedAnalogEvent * e)
	{

		if (this->out)
		{
			packedFloat = e->getPayload();
			packedFloat.getItems().at(this->id).second = this->eventAnalog;
			
			PackedAnalogEvent* event = new PackedAnalogEvent(-1, -1, packedFloat);

			this->out->push(event);

		}
	}

	void FloatToPackedFloatMSP::handleEvent2(AnalogChangedEvent * e)
	{
		if (this->out)
		{
			this->eventAnalog = e->getPayload();
			packedFloat.getItems().at(this->id).second = this->eventAnalog;

			PackedAnalogEvent* event = new PackedAnalogEvent(-1, -1, packedFloat);
			this->out->push(event);

		}
		
	}
}
