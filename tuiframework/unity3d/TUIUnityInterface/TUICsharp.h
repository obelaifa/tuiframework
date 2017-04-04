#pragma once

#include <tuiframework/client/client.h>
#include <tuitypes/common/CommonTypeReg.h>

using namespace tuiframework;

/**
* Integer Callback
* @param value Ganzzahl-Werte die an die TUI überwegeben werden sollen.
*/
typedef void(*integerCallback)(int value); // Callback for Integer Values

/**
* Float Callback
* @param value Gleitkomma-Werte die an die TUI überwegeben werden sollen.
*/
typedef void(*floatCallback)(float value); // Callback for float Values

/**
* Boolean Callback
* @param value Boolean-Werte die an die TUI überwegeben werden sollen.
*/
typedef void(*boolCallback)(bool value); // Callback for boolean Values

//typedef void(*doubleCallback)(double value); // Callback for double Values

/**
* ### Experimentel ###
* Mouse Callback
* @param value Mouse-Werte die an die TUI überwegeben werden sollen.
*/
typedef void(*mouseCallback)(MouseData value); // Experimental Callback for MouseData

/**
* Struktur zum Zusammenfassen der Parameter zum Verbinden mit dem TUI-Channel
*/
struct listValues 
{
	int tuiType;
	std::string objectName;
	std::string channelName;
	integerCallback intCall;
	floatCallback floatCall;
	boolCallback boolCall;
	mouseCallback mouseCall;
};

/**
* Diese Klasse führt den Programmcode in TUI auf C++ Seite aus der von C# aus ausgelöst wurde.
*/
class TUICsharp
{
public:
	TUICsharp();
	~TUICsharp();

	/**
	* Fügt die Parameter zu einem Struct zusammen und speichert diese in einer Liste.
	* @param TUIType ID des TUITypes
	* @param TUIObjectname TUI-Object-Type Name
	* @param channelName Name des TUI-Channels
	* @param integerCallBack Callback für Integer-Werte.
	*/
	void connecting(int TUIType, std::string TUIObjectName, std::string channelName, integerCallback call);

	/**
	* Fügt die Parameter zu einem Struct zusammen und speichert diese in einer Liste.
	* @param TUIType ID des TUITypes
	* @param TUIObjectname TUI-Object-Type Name
	* @param channelName Name des TUI-Channels
	* @param integerCallBack Callback für Float-Werte.
	*/
	void connecting(int TUIType, std::string TUIObjectName, std::string channelName, floatCallback call);

	/**
	* Fügt die Parameter zu einem Struct zusammen und speichert diese in einer Liste.
	* @param TUIType ID des TUITypes
	* @param TUIObjectname TUI-Object-Type Name
	* @param channelName Name des TUI-Channels
	* @param integerCallBack Callback für Boolean-Werte.
	*/
	void connecting(int TUIType, std::string TUIObjectName, std::string channelName, boolCallback call);

	/**
	* ### Experimentel ###
	* Fügt die Parameter zu einem Struct zusammen und speichert diese in einer Liste.
	* @param TUIType ID des TUITypes
	* @param TUIObjectname TUI-Object-Type Name
	* @param channelName Name des TUI-Channels
	* @param integerCallBack Callback für MouseData.
	*/
	void connecting(int TUIType, std::string TUIObjectName, std::string channelName, mouseCallback call);

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
	* ### Experimentel ###
	* Funktion die ausgeführt wird sobald ein Event ausgelöst wird.
	* @param e Mouse Event
	*/
	void SignalChanged(const MouseEvent * e);

private:

	/**
	* Struktur die alle Parameter für das verbinden des Channels mit dem TUI-Server enthält.
	*/
//	listValues listVal;

	/**
	* Vector der alle strukturen mit den Parametern enthält.
	*/
	std::vector<listValues> list;

};

