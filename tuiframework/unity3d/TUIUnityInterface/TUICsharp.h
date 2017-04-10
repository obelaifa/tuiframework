#pragma once

#include <tuiframework/client/client.h>
#include <tuitypes/common/CommonTypeReg.h>
#include <tuiframework/client/TUIObjectStub.h>

#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <fstream>

#define BOOLEAN 11
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
typedef void(*floatCallback)(std::string TUIObjectName, std::string description, float value); // Callback for float Values

/**
* Boolean Callback
* @param value Boolean-Werte die an die TUI �berwegeben werden sollen.
*/
typedef void(*boolCallback)(bool value); // Callback for boolean Values


/**
* Struktur zum Zusammenfassen der Parameter zum Verbinden mit dem TUI-Channel
*/
struct listValues 
{
	std::string objectName;
	std::string portName;
	std::string description;
	int tuiType;
	int portAdress;
	integerCallback intCall;
	floatCallback floatCall;
	boolCallback boolCall;

	listValues();
	~listValues();
	listValues(std::string objectName, std::string portName, std::string description, int tuiType, int portAdress, floatCallback floatCall);
	listValues(std::string objectName, std::string portName, std::string description, int tuiType, int portAdress, integerCallback intCall);
	listValues(std::string objectName, std::string portName, std::string description, int tuiType, int portAdress, boolCallback boolCall);
};

/**
* Diese Klasse f�hrt den Programmcode in TUI auf C++ Seite aus der von C# aus ausgel�st wurde.
*/
class TUICsharp
{
public:
	TUICsharp();
	~TUICsharp();

	/**
	* F�gt die Parameter zu einem Struct zusammen und speichert diese in einer Liste.
	* @param TUIType ID des TUITypes
	* @param TUIObjectname TUI-Object-Type Name
	* @param channelName Name des TUI-Channels
	* @param integerCallBack Callback f�r Integer-Werte.
	*/
	void connecting(int TUIType, std::string TUIObjectName, std::string description, integerCallback call);

	/**
	* F�gt die Parameter zu einem Struct zusammen und speichert diese in einer Liste.
	* @param TUIType ID des TUITypes
	* @param TUIObjectname TUI-Object-Type Name
	* @param channelName Name des TUI-Channels
	* @param integerCallBack Callback f�r Float-Werte.
	*/
	void connecting(int TUIType, std::string TUIObjectName, std::string description, floatCallback call);

	/**
	* F�gt die Parameter zu einem Struct zusammen und speichert diese in einer Liste.
	* @param TUIType ID des TUITypes
	* @param TUIObjectname TUI-Object-Type Name
	* @param channelName Name des TUI-Channels
	* @param integerCallBack Callback f�r Boolean-Werte.
	*/
	void connecting(int TUIType, std::string TUIObjectName, std::string description, boolCallback call);

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

	void connectAll(floatCallback call);

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

