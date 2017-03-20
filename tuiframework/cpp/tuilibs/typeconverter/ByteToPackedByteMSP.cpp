#include "ByteToPackedByteMSP.h"
#include "../../tuiframework/core/Exception.h"
#define USE_TFDEBUG
#include "../../TUIFramework/logging/Logger.h"

#define SIZE_VECTOR 8


static const char * inTag = "in";
static const char * inTagPacked = "inPacked";
static const char * outTagPacked = "outPacked";

namespace tuiframework {

	IMSP * ByteToPackedByteMSP::createFunction(void * arg)
	{
		MSPConfig * config = static_cast<MSPConfig *>(arg);
		return new ByteToPackedByteMSP(*config);
	}

	static std::string typeName = "ByteToPackedByteMSP";


	std::string ByteToPackedByteMSP::getMSPTypeName()
	{
		return typeName;
	}

	ByteToPackedByteMSP::ByteToPackedByteMSP(const MSPConfig & config)
		:config(config), eventDigital(0)
	{

		this->out = 0;

		this->nameToIdMap[outTagPacked] = 0;

		try {
			this->id = config.getParameterGroup().getInt("Convert|id");
			this->size = config.getParameterGroup().getInt("Convert|size");
			findIntToChange();
			TFDEBUG("ID = " << this->id);
			TFDEBUG("size = " << this->size);
			TFDEBUG("intToChange = " << this->intToChange);
		}
		catch (Exception & e) {
			TFERROR(e.getFormattedString());
		}

		this->eventDelegate.setReceiver(this, &ByteToPackedByteMSP::handleEvent);
		this->eventDelegate2.setReceiver(this, &ByteToPackedByteMSP::handleEvent2);

		std::vector<std::pair<int, int>> intVector;
		for (int i = 0; i < this->size; i++)
		{
			intVector.push_back(pair<int, int>(i, 0));
		}
		packedInt.setItems(intVector);

	}

	ByteToPackedByteMSP::~ByteToPackedByteMSP()
	{
	}

	const std::string & ByteToPackedByteMSP::getTypeName() const
	{
		return this->type.getTypeName();
	}

	IEventSink * ByteToPackedByteMSP::getEventSink(const std::string & name)
	{
		if (name.compare(inTag) == 0) {
			return &eventDelegate2;
		}
		if (name.compare(inTagPacked) == 0) {
			return &eventDelegate;
		}
		return 0;
	}

	void ByteToPackedByteMSP::registerEventSink(const std::string & name, IEventSink * eventSink)
	{
		map<string, int>::iterator iter = this->nameToIdMap.find(name);
		if (iter == this->nameToIdMap.end()) {
			return;
		}
		this->out = eventSink;
	}

	const MSPType & ByteToPackedByteMSP::getMSPType() const
	{
		return this->type;
	}

	void ByteToPackedByteMSP::handleEvent(PackedIntegerEvent * e)
	{
		if (this->out)
		{
			packedInt = e->getPayload();

			packedInt.getItems().at(this->intToChange).second = changeByteVector();
			PackedIntegerEvent* event = new PackedIntegerEvent(-1, -1, packedInt);

			this->out->push(event);

		}
	}

	void ByteToPackedByteMSP::handleEvent2(DigitalChangedEvent * e)
	{
		if (this->out)
		{
			this->eventDigital = e->getPayload();

			packedInt.getItems().at(this->intToChange).second = changeByteVector();
			PackedIntegerEvent* event = new PackedIntegerEvent(-1, -1, packedInt);

			this->out->push(event);

		}

	}

	void ByteToPackedByteMSP::findIntToChange()
	{
		for (int i = 1; i <= this->size; i++) {
			if (this->id < i * SIZE_VECTOR) {
				this->intToChange = i - 1;
				return;
			}
		}
	}

	std::vector<int> ByteToPackedByteMSP::convertTobinary(int intToBinary)
	{
		std::vector<int> binary;
		binary.resize(SIZE_VECTOR);
		for (int i = 0; i <= 7; i++) {
			binary[i] = intToBinary % 2;
			intToBinary /= 2;
		}
		return binary;
	}

	int ByteToPackedByteMSP::convertToInt(std::vector<int> bitToInt)
	{
		int pow = 0;
		int returnInt = 0;
		for (int currentInt : bitToInt) {
			returnInt += std::pow(2, pow) * currentInt;
			pow += 1;
		}

		return returnInt;
	}

	int ByteToPackedByteMSP::changeByteVector()
	{
		std::vector<int> binaryEvent;
		int intEvent;

		binaryEvent = convertTobinary(packedInt.getItems().at(this->intToChange).second);
		binaryEvent[this->id%SIZE_VECTOR] = this->eventDigital;
		intEvent = convertToInt(binaryEvent);

		return intEvent;
	}
}
