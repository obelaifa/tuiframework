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

	void connectingParameters(void* instance, int TUIType, const char* objectName, const char* description, integerCallback call)
	{
		TUICsharp* tuiUnity = (TUICsharp*)instance;
		tuiUnity->connecting(TUIType, std::string(objectName), std::string(description), call);
	}

	void connectingParametersfloat(void* instance, int TUIType, const char* objectName, const char* description, floatCallback call)
	{
		TUICsharp* tuiUnity = (TUICsharp*)instance;
		tuiUnity->connecting(TUIType, std::string(objectName), std::string(description), call);
	}

	void connectingParametersbool(void* instance, int TUIType, const char* objectName, const char* description, boolCallback call)
	{
		TUICsharp* tuiUnity = (TUICsharp*)instance;
		tuiUnity->connecting(TUIType, std::string(objectName), std::string(description), call);
	}

	void connectingParametersAll(void* instance, floatCallback call)
	{
		TUICsharp* tuiUnity = (TUICsharp*)instance;
		tuiUnity->connectAll(call);
	}
}


