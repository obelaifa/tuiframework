#include "TUIInit.h"



TUIInit::TUIInit()
{
}


TUIInit::~TUIInit()
{
}

void TUIInit::push(tuiframework::IEvent * event)
{
	if (event->getEventTypeID() == tuiframework::SystemMsg::EventTypeID()) {
		tuiframework::SystemMsg * msg = static_cast<tuiframework::SystemMsg *>(event);

		if (msg->getPayload() == CONNECTION_ESTABLISHED) {

		}
		else if(msg->getPayload() == REMOVE_CONNECTION)
		{
			this->tuiCSharp->disconnect();
		}
	}
}

void TUIInit::setTUICsharp(TUICsharp* tuicSharp)
{
	this->tuiCSharp = tuicSharp;
}