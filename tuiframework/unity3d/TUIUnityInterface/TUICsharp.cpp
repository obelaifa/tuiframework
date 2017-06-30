#include "TUICsharp.h"


TUICsharp::TUICsharp()
{
}

TUICsharp::~TUICsharp()
{

}

void TUICsharp::connect()
{
	try {
		// Durchläuft den Vector mit gespeicherten Strukturen
		for (std::vector<TUIUObject>::iterator it = list.begin(); it != list.end(); ++it)
		{
			// Verbindet sich je nach TUITypeID
			switch (it->tuiType)
			{
			case DIGITAL:
				CONNECT(DigitalChangedEvent, it->objectName, it->portName, TUICsharp, this, &TUICsharp::SignalChanged);
				break;
			case ANALOG:
				CONNECT(AnalogChangedEvent, it->objectName, it->portName, TUICsharp, this, &TUICsharp::SignalChanged);
				break;
			case INTEGER:
				CONNECT(IntegerChangedEvent, it->objectName, it->portName, TUICsharp, this, &TUICsharp::SignalChanged);
				break;
			default:
				break;
			}
		}
	}
	catch (const Exception & e) {
		cerr << "Exception" << endl;
		cerr << e.getFormattedString() << endl;
	}

}

void TUICsharp::disconnect()
{
	try
	{
		// Durchläuft den Vector mit gespeicherten Strukturen
		for (std::vector<TUIUObject>::iterator it = list.begin(); it != list.end(); ++it)
		{
			// Verbindet sich je nach TUITypeID
			switch (it->tuiType)
			{
			case DIGITAL:
				DISCONNECT(DigitalChangedEvent, it->objectName, it->portName, TUICsharp, this, &TUICsharp::SignalChanged);
				break;
			case ANALOG:
				DISCONNECT(AnalogChangedEvent, it->objectName, it->portName, TUICsharp, this, &TUICsharp::SignalChanged);
				break;
			case INTEGER:
				DISCONNECT(IntegerChangedEvent, it->objectName, it->portName, TUICsharp, this, &TUICsharp::SignalChanged);
				break;
			default:
				break;
			}
		}
	}
	catch (const Exception & e) {
		cerr << "Exception" << endl;
		cerr << e.getFormattedString() << endl;
	}
}

void TUICsharp::SignalChanged(const IntegerChangedEvent * e)
{
	for (int i = 0; i < list.size(); ++i)
	{
		if (i == (e->getAddress().getPortNr() - 1))
		{
			// Ruft die Callback-Funktion auf
			list.at(i).intCall(e->getPayload());
		}
	}
}

void TUICsharp::SignalChanged(const DigitalChangedEvent * e)
{
	for (int i = 0; i < list.size(); ++i)
	{
		if (list.at(i).portAdress == e->getAddress().getPortNr() && list.at(i).entityID == e->getAddress().getEntityID())
		{
			const char* TUIObjectName = list.at(i).objectName.c_str();
			const char* portName = list.at(i).portName.c_str();
			const char* description = list.at(i).description.c_str();
			const char* trafoType = list.at(i).trafoType.c_str();
			const char* trafoNo = list.at(i).trafoNo.c_str();
			const char* constraintMin = list.at(i).constraintMin.c_str();
			const char* constraintMax = list.at(i).constraintMax.c_str();

			list.at(i).boolCall(TUIObjectName, portName, description, e->getPayload(), trafoType, trafoNo, constraintMin, constraintMax);
		}
	}
}

void TUICsharp::SignalChanged(const AnalogChangedEvent * e)
{
	for (int i = 0; i < list.size(); ++i)
	{
		if (list.at(i).portAdress == e->getAddress().getPortNr() && list.at(i).entityID == e->getAddress().getEntityID())
		{
			const char* TUIObjectName = list.at(i).objectName.c_str();
			const char* portName = list.at(i).portName.c_str();
			const char* description = list.at(i).description.c_str();
			const char* trafoType = list.at(i).trafoType.c_str();
			const char* trafoNo = list.at(i).trafoNo.c_str();
			const char* constraintMin = list.at(i).constraintMin.c_str();
			const char* constraintMax = list.at(i).constraintMax.c_str();

			list.at(i).floatCall(TUIObjectName, portName, description, e->getPayload(), trafoType, trafoNo, constraintMin, constraintMax);
		}
	}
}

void TUICsharp::connectAll(floatCallback call, boolCallback callb)
{
	std::vector<TUIObjectInstance> objectInstances = getAttachedObjects().getTUIObjectInstanceVector();
	std::vector<TUIObjectType> objectTypes = getAttachedObjects().getTUIObjectTypeVector();

	int portAdress = 0;
	int instanceID = 0;

	for (vector<TUIObjectInstance>::iterator it = objectInstances.begin(); it != objectInstances.end(); it++) {
		for (vector<TUIObjectType>::iterator typeIt = objectTypes.begin(); typeIt != objectTypes.end(); typeIt++) {
			if (typeIt->getName() == it->getTypeName() && instanceID != it->getID()) {
				instanceID = it->getID();
				portAdress = 0;

				for (map<string, tuiframework::Port>::iterator typeMapIt2 = typeIt->getPortMap().begin(); typeMapIt2 != typeIt->getPortMap().end(); typeMapIt2++)
				{
					portAdress++;
					if (typeMapIt2->second.getDataFlowDirection() == 2)
						continue;

					std::string constraintMin = "empty";
					std::string constraintMax = "empty";
					std::string trafoType = "empty";
					std::string trafoNo = "empty";

					if (!typeMapIt2->second.getParameterGroup().getParameterGroupMap().empty()) {
						constraintMin = typeMapIt2->second.getParameterGroup().getParameterGroup("Constraint").getParameterMap().at("min");
						constraintMax = typeMapIt2->second.getParameterGroup().getParameterGroup("Constraint").getParameterMap().at("max");
						trafoType = typeMapIt2->second.getParameterGroup().getParameterGroup("Meta").getParameterMap().at("TrafoType");
						trafoNo = typeMapIt2->second.getParameterGroup().getParameterGroup("Meta").getParameterMap().at("TrafoNo");
					}

					if (typeMapIt2->second.getTypeName().compare("AnalogChannel") == 0) {
						TUIUObject values(it->getName(), typeMapIt2->second.getName(), typeMapIt2->second.getDescription(), ANALOG, instanceID, portAdress, call);
						values.metaData(constraintMin, constraintMax, trafoType, trafoNo);
						list.push_back(values);
					}
					else if (typeMapIt2->second.getTypeName().compare("DigitalChannel") == 0) {
						TUIUObject values(it->getName(), typeMapIt2->second.getName(), typeMapIt2->second.getDescription(), DIGITAL, instanceID, portAdress, callb);
						values.metaData(constraintMin, constraintMax, trafoType, trafoNo);
						list.push_back(values);
					}					
				}
			}
		}
	}
	this->connect();
}

void TUICsharp::sendEvent(const std::string & tuiObjectName, const std::string & portName, const std::string & serializedPayload) {
	TUIObjectStubContainer & tc = TUIClientAppProvider::getInstance()->getTUIObjectStubContainer();
	TUIObjectStub * t = tc.getStub(tuiObjectName);
	IEventChannel * iec = t->getSinkChannel(portName);

	IEvent * event = TUIClientAppProvider::getInstance()->getEventFactory().createInstance(iec->getChannelTypeID());

	if (event) {
		stringstream ss;
		ss << "-1 -1 " << serializedPayload;
		ss >> event;
		iec->push(event);
	}
}
