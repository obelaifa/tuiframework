#pragma once

#include <TUIFramework/client/client.h>
#include <tuilibs/tuitypes/common/CommonTypeReg.h>
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
	* @param integerCallBack Funktions-Callback für Integer-Werte.
	*/
	TESTFUNCDLL_API void connectingParameters(void* instance, int TUIType, const char* objectName, const char* channelName, integerCallback call);
	/**
	* Setzt die Parameter zum Verbinden mit dem TUI-Channel
	* @param instance Die C# Instanz
	* @param TUIType ID des TUI-Types
	* @param objectName Name des TUI-Object Types
	* @param channelName Name des Channels mit dem sich verbunden werden soll.
	* @param floatCallBack Funktions-Callback für Float-Werte.
	*/
	TESTFUNCDLL_API void connectingParametersfloat(void* instance, int TUIType, const char* objectName, const char* channelName, floatCallback call);

	/**
	* Setzt die Parameter zum Verbinden mit dem TUI-Channel
	* @param instance Die C# Instanz
	* @param TUIType ID des TUI-Types
	* @param objectName Name des TUI-Object Types
	* @param channelName Name des Channels mit dem sich verbunden werden soll.
	* @param integerCallBack Funktions-Callback für boolean-Werte.
	*/
	TESTFUNCDLL_API void connectingParametersbool(void* instance, int TUIType, const char* objectName, const char* channelName, boolCallback call);
	
	/**
	* ### Experimentelle Funktion ###
	* Setzt die Parameter zum Verbinden mit dem TUI-Channel
	* @param instance Die C# Instanz
	* @param TUIType ID des TUI-Types
	* @param objectName Name des TUI-Object Types
	* @param channelName Name des Channels mit dem sich verbunden werden soll.
	* @param integerCallBack Funktions-Callback für MouseData.
	*/
	TESTFUNCDLL_API void connectingParametersmouse(void* instance, int TUIType, const char* objectName, const char* channelName, mouseCallback call);


	//TESTFUNCDLL_API void getMouseData(void* instance,const char* value);
}
