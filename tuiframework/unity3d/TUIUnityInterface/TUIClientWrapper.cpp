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

	void connectingParametersAll(void* instance, floatCallback call, boolCallback callb)
	{
		TUICsharp* tuiUnity = (TUICsharp*)instance;
		tuiUnity->connectAll(call, callb);
	}

	void sendUnityEvent(void* instance, const char* tuiObjectName, const char* portName, const char* serializedPayload)
	{
		TUICsharp* tuiUnity = (TUICsharp*)instance;
		tuiUnity->sendEvent(tuiObjectName, portName, serializedPayload);
	}
}


