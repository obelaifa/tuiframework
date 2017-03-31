#include "TUIClientWrapper.h"

extern "C"
{

	bool connectUnityWithTUIServer(int recievePort,int senderPort, const char* serverIPPort, void* tuiInit)
	{
		
		TUIInit init = *(TUIInit*)tuiInit;
		initTypeRegistration(getEventFactory());
		CommonTypeReg::registerTypes(&getEventFactory(), &getEventChannelFactory());

		getchar();

		connectWithTUIServer(recievePort, senderPort,std::string(serverIPPort),&init,true);
		return true;
	}

	void disconnectUnityWithTUIServer()
	{
		disconnectFromTUIServer();
	}

	void* createTUICsharpInstance()
	{
		return new TUICsharp();
	}

	void* createTUIInitInstance()
	{
		return new TUIInit();
	}

	void setTUIInitParameter(void* tuiInitInstance, void* tuiCSharpInstance)
	{
		TUIInit* tuiInit = (TUIInit*)tuiInitInstance;
		tuiInit->setTUICsharp(*(TUICsharp*)tuiCSharpInstance);
	}

	void connectingParameters(void* instance, int TUIType, const char* objectName, const char* channelName, integerCallback call)
	{
		TUICsharp* tuiUnity = (TUICsharp*)instance;
		tuiUnity->connecting(TUIType, std::string(objectName), std::string(channelName), call);
	}

	void connectingParametersfloat(void* instance, int TUIType, const char* objectName, const char* channelName, floatCallback call)
	{
		TUICsharp* tuiUnity = (TUICsharp*)instance;
		tuiUnity->connecting(TUIType, std::string(objectName), std::string(channelName), call);
	}

	void connectingParametersbool(void* instance, int TUIType, const char* objectName, const char* channelName, boolCallback call)
	{
		TUICsharp* tuiUnity = (TUICsharp*)instance;
		tuiUnity->connecting(TUIType, std::string(objectName), std::string(channelName), call);
	}

	void connectingParametersmouse(void* instance, int TUIType, const char* objectName, const char* channelName, mouseCallback call)
	{
		TUICsharp* tuiUnity = (TUICsharp*)instance;
		tuiUnity->connecting(TUIType, std::string(objectName), std::string(channelName), call);
	}

	void getMouseData(void* instance,const char* value)
	{
		//ToDo 
		//Muss noch bearbeitet werden.
		MouseData* mouseData = (MouseData*)instance;
		stringstream ss;
		ss << mouseData;
		value = ss.str().c_str();
	}
}


