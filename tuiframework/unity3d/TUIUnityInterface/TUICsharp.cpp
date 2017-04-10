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
		for (std::vector<listValues>::iterator it = list.begin(); it != list.end(); ++it)
		{
			// Verbindet sich je nach TUITypeID
			switch (it->tuiType)
			{
			case 11:
				CONNECT(DigitalChangedEvent, it->objectName, it->portName, TUICsharp, this, &TUICsharp::SignalChanged);
				break;
			case 12:
				CONNECT(AnalogChangedEvent, it->objectName, it->portName, TUICsharp, this, &TUICsharp::SignalChanged);
				break;
			case 13:
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
		for (std::vector<listValues>::iterator it = list.begin(); it != list.end(); ++it)
		{
			// Verbindet sich je nach TUITypeID
			switch (it->tuiType)
			{
			case 11:
				DISCONNECT(DigitalChangedEvent, it->objectName, it->portName, TUICsharp, this, &TUICsharp::SignalChanged);
				break;
			case 12:
				DISCONNECT(AnalogChangedEvent, it->objectName, it->portName, TUICsharp, this, &TUICsharp::SignalChanged);
				break;
			case 13:
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

void TUICsharp::connecting(int TUIType, std::string TUIObjectName, std::string description, integerCallback call)
{
	listValues values;
	values.tuiType = TUIType;
	values.objectName = TUIObjectName;
	values.portName = description;
	values.description = description;
	values.intCall = call;

	// Fügt die Struktur der Liste hinzu.
	list.push_back(values);
}

void TUICsharp::connecting(int TUIType, std::string TUIObjectName, std::string description, floatCallback call)
{
	listValues values;
	values.tuiType = TUIType;
	values.objectName = TUIObjectName;
	values.portName = description;
	values.description = description;
	values.floatCall = call;

	// Fügt die Struktur der Liste hinzu.
	list.push_back(values);
}

void TUICsharp::connecting(int TUIType, std::string TUIObjectName, std::string description, boolCallback call)
{
	listValues values;
	values.tuiType = TUIType;
	values.objectName = TUIObjectName;
	values.portName = description;
	values.description = description;
	values.boolCall = call;

	// Fügt die Struktur der Liste hinzu.
	list.push_back(values);
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
		if (i == (e->getAddress().getPortNr() - 1))
		{
			// Ruft die Callback-Funktion auf
			list.at(i).boolCall(e->getPayload());
		}
	}
}

void TUICsharp::SignalChanged(const AnalogChangedEvent * e)
{
	std::ofstream fichier("debug.txt", ios::out | ios::trunc);
	fichier << "debug" << endl;
	for (int i = 0; i < list.size(); ++i)
	{
		fichier << "Event Adress " << e->getAddress().getPortNr() << endl << "PortAdress: " << list.at(i).portAdress << endl << list.at(i).objectName << " " << list.at(i).description << endl;
		if (list.at(i).portAdress == e->getAddress().getPortNr())
		{
			list.at(i).floatCall(list.at(i).objectName, list.at(i).description, e->getPayload());
		}
	}
	fichier.close();
}

void TUICsharp::connectAll(floatCallback call)
{
	std::vector<TUIObjectInstance> objectInstances = getAttachedObjects().getTUIObjectInstanceVector();
	std::vector<TUIObjectType> objectTypes = getAttachedObjects().getTUIObjectTypeVector();
	//std::ofstream fichier("debug.txt", ios::out | ios::trunc);
	int portAdress = 1;

	for (vector<TUIObjectInstance>::iterator it = objectInstances.begin(); it != objectInstances.end(); it++) {
		for (vector<TUIObjectType>::iterator typeIt = objectTypes.begin(); typeIt != objectTypes.end(); typeIt++) {
			if (typeIt->getName() == it->getTypeName()) {
				for (map<string, tuiframework::Port>::iterator typeMapIt2 = typeIt->getPortMap().begin(); typeMapIt2 != typeIt->getPortMap().end(); typeMapIt2++, portAdress++)
				{
					//fichier << "PortAdress: " << portAdress << endl << it->getName() << " " << typeMapIt2->second.getName() << " " << typeMapIt2->second.getDescription() << endl;
					if (typeMapIt2->second.getDataFlowDirection() == 2)
						continue;

					if (typeMapIt2->second.getTypeName().compare("AnalogChannel") == 0) {
						listValues values(it->getName(), typeMapIt2->second.getName(), typeMapIt2->second.getDescription(), ANALOG, portAdress, call);
						list.push_back(values);
					}
				}
			}
		}
	}
	//fichier.close();
	this->connect();
}

listValues::listValues()
{
}

listValues::~listValues()
{
}

listValues::listValues(std::string objectName, std::string portName, std::string description, int tuiType, int portAdress, floatCallback floatCall)
	:objectName(objectName), portName(portName), description(description), tuiType(tuiType), portAdress(portAdress), floatCall(floatCall)
{
}

listValues::listValues(std::string objectName, std::string portName, std::string description, int tuiType, int portAdress, integerCallback intCall)
	: objectName(objectName), portName(portName), description(description), tuiType(tuiType), portAdress(portAdress), intCall(intCall)
{
}

listValues::listValues(std::string objectName, std::string portName, std::string description, int tuiType, int portAdress, boolCallback boolCall)
	: objectName(objectName), portName(portName), description(description), tuiType(tuiType), portAdress(portAdress), boolCall(boolCall)
{
}
