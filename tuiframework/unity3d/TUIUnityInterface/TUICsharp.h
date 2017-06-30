#pragma once

#include <tuiframework/client/client.h>
#include <tuitypes/common/CommonTypeReg.h>
#include <tuiframework/client/TUIObjectStub.h>

#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <fstream>

#include "TUIUObject.h"

#define DIGITAL 11
#define ANALOG 12
#define INTEGER 13

using namespace tuiframework;


/**
* Diese Klasse führt den Programmcode in TUI auf C++ Seite aus der von C# aus ausgelöst wurde.
*/
class TUICsharp
{
public:
	TUICsharp();
	~TUICsharp();

	/*
	* Verbindet die in der Liste enthaltenten Parameter mit dem TUI-Server
	*/
	void connect();

	/*
	* Beendet die Verbindung.
	*/
	void disconnect();

	/**
	* Funktion die ausgeführt wird sobald ein Event ausgelöst wird.
	* @param e integer Event
	*/
	void SignalChanged(const IntegerChangedEvent * e);

	/**
	* Funktion die ausgeführt wird sobald ein Event ausgelöst wird.
	* @param e Boolean Event
	*/
	void SignalChanged(const DigitalChangedEvent * e);

	/**
	* Funktion die ausgeführt wird sobald ein Event ausgelöst wird.
	* @param e Float Event
	*/
	void SignalChanged(const AnalogChangedEvent * e);

	/**
	* Fügt die Parameter zu einem Struct zusammen und speichert diese in einer Liste.
	* @param floatCallback Callback für Float-Werte.
	* @param boolCallback Callback für Boolean-Werte.
	*/
	void connectAll(floatCallback call, boolCallback callb);

	void sendEvent(const std::string & tuiObjectName, const std::string & portName, const std::string & serializedPayload);

private:

	/**
	* Vector der alle strukturen mit den Parametern enthält.
	*/
	std::vector<TUIUObject> list;
};

