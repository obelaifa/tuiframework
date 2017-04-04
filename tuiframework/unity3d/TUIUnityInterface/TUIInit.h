#pragma once

#include <tuiframework/client/client.h>
#include "TUICsharp.h"

using namespace std;

class TUIInit : public tuiframework::IEventSink
{
public:
	TUIInit();
	~TUIInit();
	virtual void push(tuiframework::IEvent * e);

	void setTUICsharp(TUICsharp tuicSharp);

protected:
	TUICsharp tuiCSharp;
};

