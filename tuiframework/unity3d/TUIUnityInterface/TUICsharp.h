#pragma once

#include <tuiframework/client/client.h>
#include <tuitypes/common/CommonTypeReg.h>
#include <tuiframework/client/TUIObjectStub.h>

#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <fstream>

#define DIGITAL 11
#define ANALOG 12
#define INTEGER 13

using namespace tuiframework;

/**
* Integer Callback
* @param value Ganzzahl-Werte die an die TUI �berwegeben werden sollen.
*/
typedef void(*integerCallback)(int value); // Callback for Integer Values

/**
* Float Callback
* @param value Gleitkomma-Werte die an die TUI �berwegeben werden sollen.
*/
typedef void(*floatCallback)(const char* TUIObjectName, const char* portName, const char* description, float value, const char* trafoType, const char* trafoNo); // Callback for float Values

/**
* Boolean Callback
* @param value Boolean-Werte die an die TUI �berwegeben werden sollen.
*/
typedef void(*boolCallback)(const char* TUIObjectName, const char* portName, const char* description, bool value); // Callback for boolean Values


/**
* Struktur zum Zusammenfassen der Parameter zum Verbinden mit dem TUI-Channel
*/
struct listValues 
{
	std::string objectName;
	std::string portName;
	std::string description;
	int tuiType;
	int entityID;
	int portAdress;
	integerCallback intCall;
	floatCallback floatCall;
	boolCallback boolCall;

	std::string constraintMin;
	std::string constraintMax;
	std::string trafoType;
	std::string trafoNo;

	listValues();
	~listValues();
	listValues(std::string objectName, std::string portName, std::string description, int tuiType, int entityID, int portAdress, floatCallback floatCall);
	listValues(std::string objectName, std::string portName, std::string description, int tuiType, int entityID, int portAdress, integerCallback intCall);
	listValues(std::string objectName, std::string portName, std::string description, int tuiType, int entityID, int portAdress, boolCallback boolCall);

	void metaData(std::string constraintMin, std::string constraintMax, std::string trafoType, std::string trafoNo);
};

/**
* Diese Klasse f�hrt den Programmcode in TUI auf C++ Seite aus der von C# aus ausgel�st wurde.
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
	* Funktion die ausgef�hrt wird sobald ein Event ausgel�st wird.
	* @param e integer Event
	*/
	void SignalChanged(const IntegerChangedEvent * e);

	/**
	* Funktion die ausgef�hrt wird sobald ein Event ausgel�st wird.
	* @param e Boolean Event
	*/
	void SignalChanged(const DigitalChangedEvent * e);

	/**
	* Funktion die ausgef�hrt wird sobald ein Event ausgel�st wird.
	* @param e Float Event
	*/
	void SignalChanged(const AnalogChangedEvent * e);

	/**
	* F�gt die Parameter zu einem Struct zusammen und speichert diese in einer Liste.
	* @param TUIType ID des TUITypes
	* @param TUIObjectname TUI-Object-Type Name
	* @param channelName Name des TUI-Channels
	* @param integerCallBack Callback f�r Boolean-Werte und Float-Werte.
	*/
	void connectAll(floatCallback call, boolCallback callb);

	void sendEvent(const std::string & tuiObjectName, const std::string & portName, const std::string & serializedPayload);

private:

	/**
	* Struktur die alle Parameter f�r das verbinden des Channels mit dem TUI-Server enth�lt.
	*/
//	listValues listVal;

	/**
	* Vector der alle strukturen mit den Parametern enth�lt.
	*/

	std::vector<listValues> list;

};

