#include "FloatToFloatPackage.h"
#include <tuiframework/core/Exception.h>
#define USE_TFDEBUG
#include <tuiframework/logging/Logger.h>


static const char * outTagPacked = "outPacked";



namespace tuiframework {
	IMSP * FloatToFloatPackage::createFunction(void * arg)
	{
		MSPConfig * config = static_cast<MSPConfig *>(arg);
		return new FloatToFloatPackage(*config);
	}

	static std::string typeName = "FloatToFloatPackage";


	std::string FloatToFloatPackage::getMSPTypeName()
	{
		return typeName;
	}

	FloatToFloatPackage::FloatToFloatPackage(const MSPConfig & config) :
		config(config) {


		this->eventDelegate.setReceiver(this, &FloatToFloatPackage::handleEvent);

		this->out = 0;
		this->nameToIdMap[outTagPacked] = 0;

		try {
			this->id = config.getParameterGroup().getInt("Convert|id");
			this->floatSize = config.getParameterGroup().getInt("Convert|floatSize");
			TFDEBUG("ID = " << this->id);
			TFDEBUG("FloatSize = " << this->floatSize);
			initInTag();
		}
		catch (Exception & e) {
			TFERROR(e.getFormattedString());
		}

		std::vector<std::pair<int, float>> floatVector;
		for (int i = 0; i < floatSize; ++i)
		{
			floatVector.push_back(pair<int, float >(i, INT32_MIN));
		}
		packedFloat.setItems(floatVector);
	}

	FloatToFloatPackage::~FloatToFloatPackage()
	{
	}

	const std::string & FloatToFloatPackage::getTypeName() const
	{
		return this->type.getTypeName();
	}

	IEventSink * FloatToFloatPackage::getEventSink(const std::string & name)
	{	
		for (string inTag : this->inTag)
		{
			if (name.compare(inTag) == 0)
				return &eventDelegate;
		}

		return 0;
	}

	void FloatToFloatPackage::registerEventSink(const std::string & name, IEventSink * eventSink)
	{
		map<string, int>::iterator iter = this->nameToIdMap.find(name);
		if (iter == this->nameToIdMap.end()) {
			return;
		}
		this->out = eventSink;
	}

	const MSPType & FloatToFloatPackage::getMSPType() const
	{
		return this->type;
	}

	void FloatToFloatPackage::handleEvent(AnalogChangedEvent * e)
	{

		//cout << "Event Address:" << e->getAddress() << " EventAdresstype: " <<e->getAddressTypeID() << "Event: " <<e << endl;


		if (this->out)
			{
			/*pair<int, float> value_pair(0,e->getPayload());
			vector<pair<int, float>> value_vector;
			value_vector.push_back(value_pair);*/
			int entityID = e->getAddress().getEntityID();
			int portID = e->getAddress().getPortNr();

			//cout << "Packed Float event" << endl << packedFloat << endl;
			
			if (this->index <= this->floatSize - 1)
				initEvent(entityID, portID);
			
			//cout <<"PackedFloatSize: " <<packedFloat.getItems().size() << endl;
			map<std::string, int>::iterator m;
			for (m = eventOrder.begin(); m != eventOrder.end(); m++)
			{
				cout << "EntityID+portID : " << m->first << endl;
				cout << " index du packedFloat : " << m->second << endl;
			}

			//packedFloat.getItems().at(entityID-1).second = e->getPayload();
			packedFloat.getItems().at(this->eventOrder[std::to_string(entityID) + std::to_string(portID)]).second = e->getPayload();
			//packedFloat.getItems().at(0).second = e->getPayload();
			PackedAnalogEvent* event = new PackedAnalogEvent(-1, -1, packedFloat);


			this->out->push(event);
			cout << "Packed : " << packedFloat << endl;
		}
	}

	void FloatToFloatPackage::initEvent(const int & entityID, const int & portID)
	{
		this->eventOrder[std::to_string(entityID) + std::to_string(portID)] = this->index;
		++index;
	}

	void FloatToFloatPackage::initInTag()
	{
		for (int i = 0; i < this->floatSize; i++)
		{
			this->inTag.push_back("in" + std::to_string(i));
		}
	}
}