#pragma once

#include <tuiframework/client/client.h>
#include <tuitypes/common/CommonTypeReg.h>
#include "TUIInit.h"

 // Define DLL Export API
#define TESTFUNCDLL_API __declspec(dllexport) 

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
typedef void(*floatCallback)(std::string TUIObjectName, std::string portName, std::string description, float value, std::string trafoType, std::string trafoNo); // Callback for float Values

/**
* Boolean Callback
* @param value Boolean-Werte die an die TUI überwegeben werden sollen.
*/
typedef void(*boolCallback)(std::string TUIObjectName, std::string portName, std::string description, bool value); // Callback for boolean Values

extern "C" 
{
	/**
	* Verbindet sich mit dem TUI-Server
	* @param recievePort ReceiverPort des Unity Clients
	* @param senderPort SenderPort des Unity Clients
	* @param serverIPPort String mit IP und port des Servers im Format serverIP:port
	* @param tuiInit Instance einer der Init-Klasse
	* @return true wenn Verbindung erfolgreich
	*/
	TESTFUNCDLL_API bool connectUnityWithTUIServer(int recievePort, int senderPort, const char* serverIPPort, void* tuiInit);
	
	/**
	* Beendet die Verbindung zum TUI-Server.
	*/
	TESTFUNCDLL_API void disconnectUnityWithTUIServer();

	/**
	* Erstellt eine Instanz der Init-Klasse
	* @return pointer zu der Init-Instanz
	*/
	TESTFUNCDLL_API void* createTUIInitInstance();

	/**
	* Erstellt eine Instanz der CSharp-Klasse
	* @return pointer zu der C# instanz
	*/
	TESTFUNCDLL_API void* createTUICsharpInstance();

	/**
	* Setzt die C# Instanz als Member der Init-Instanz
	* @param tuiInitInstance Die Init-Instanz
	* @param tuiCSharpInstance Die C#-Instanz
	*/
	TESTFUNCDLL_API void setTUIInitParameter(void* tuiInitInstance, void* tuiCSharpInstance);

	/**
	* Setzt die Parameter zum Verbinden mit dem TUI-Channel
	* @param instance Die C# Instanz
	* @param TUIType ID des TUI-Types
	* @param objectName Name des TUI-Object Types
	* @param channelName Name des Channels mit dem sich verbunden werden soll.
	* @param floatCallBack Funktions-Callback für Float-Werte und boolean-Werte.
	*/
	TESTFUNCDLL_API void connectingParametersAll(void* instance, floatCallback call, boolCallback callb);

	TESTFUNCDLL_API void sendUnityEvent(void* instance, const char* tuiObjectName, const char* portName, const char* serializedPayload);
}
