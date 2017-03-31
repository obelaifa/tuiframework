#include "TUICsharp.h"

TUICsharp::TUICsharp()
{
}

TUICsharp::~TUICsharp()
{

}

void TUICsharp::connect()
{
	try
	{
		// Durchläuft den Vector mit gespeicherten Strukturen
		for(std::vector<listValues>::iterator it = list.begin(); it != list.end(); ++it)
		{
			// Verbindet sich je nach TUITypeID
			switch(it->tuiType)
			{
				case 11:
					CONNECT(DigitalChangedEvent, it->objectName, it->channelName, TUICsharp, this, &TUICsharp::SignalChanged);
					break;
				case 12:
					CONNECT(AnalogChangedEvent, it->objectName, it->channelName, TUICsharp, this, &TUICsharp::SignalChanged);
					break;
				case 13:
					CONNECT(IntegerChangedEvent, it->objectName, it->channelName, TUICsharp, this, &TUICsharp::SignalChanged);
					break;
				case 21:
					CONNECT(MouseEvent, it->objectName, it->channelName, TUICsharp, this, &TUICsharp::SignalChanged);
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
				DISCONNECT(DigitalChangedEvent, it->objectName, it->channelName, TUICsharp, this, &TUICsharp::SignalChanged);
				break;
			case 12:
				DISCONNECT(AnalogChangedEvent, it->objectName, it->channelName, TUICsharp, this, &TUICsharp::SignalChanged);
				break;
			case 13:
				DISCONNECT(IntegerChangedEvent, it->objectName, it->channelName, TUICsharp, this, &TUICsharp::SignalChanged);
				break;
			case 21:
				DISCONNECT(MouseEvent, it->objectName, it->channelName, TUICsharp, this, &TUICsharp::SignalChanged);
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

void TUICsharp::connecting(int TUIType, std::string TUIObjectName,std::string portName, integerCallback call)
{
	listValues values;
	values.tuiType = TUIType;
	values.objectName = TUIObjectName;
	values.channelName = portName;
	values.intCall = call;

	// Fügt die Struktur der Liste hinzu.
	list.push_back(values);
}

void TUICsharp::connecting(int TUIType, std::string TUIObjectName, std::string portName, floatCallback call)
{
	listValues values;
	values.tuiType = TUIType;
	values.objectName = TUIObjectName;
	values.channelName = portName;
	values.floatCall = call;

	// Fügt die Struktur der Liste hinzu.
	list.push_back(values);
}

void TUICsharp::connecting(int TUIType, std::string TUIObjectName, std::string portName, boolCallback call)
{
	listValues values;
	values.tuiType = TUIType;
	values.objectName = TUIObjectName;
	values.channelName = portName;
	values.boolCall = call;

	// Fügt die Struktur der Liste hinzu.
	list.push_back(values);
}

void TUICsharp::connecting(int TUIType, std::string TUIObjectName, std::string portName, mouseCallback call)
{
	listValues values;
	values.tuiType = TUIType;
	values.objectName = TUIObjectName;
	values.channelName = portName;
	values.mouseCall = call;

	// Fügt die Struktur der Liste hinzu.
	list.push_back(values);
}

void TUICsharp::SignalChanged(const IntegerChangedEvent * e)
{
	for (int i = 0; i < list.size();++i)
	{
		if(i == (e->getAddress().getPortNr()-1))
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
	for (int i = 0; i < list.size(); ++i)
	{
		if (i == (e->getAddress().getPortNr() - 1))
		{
			// Ruft die Callback-Funktion auf
			list.at(i).floatCall(e->getPayload());
		}
	}
}

void TUICsharp::SignalChanged(const MouseEvent * e)
{
	for (int i = 0; i < list.size(); ++i)
	{
		if (i == (e->getAddress().getPortNr() - 1))
		{
			// Ruft die Callback-Funktion auf
			list.at(i).mouseCall(e->getPayload());
		}
	}
}