#ifndef _TUIClient_h_
#define _TUIClient_h_

#include <tuiframework/client/client.h>

#include <Python.h>

#include <string>
#include <iostream>

namespace tuiframework {
namespace python {

class IEventDelegation;

class TUIClient : public tuiframework::IEventSink {
public:
    TUIClient();
    virtual ~TUIClient();

    virtual void push(tuiframework::IEvent * e);

    void setSystemMsgCallback(PyObject * systemMsgCallback);

    void setEventCallback(PyObject * callback);
    void removeEventCallback(const std::string & tuiObjectName, const std::string & portName);

    void sendEvent(const std::string & tuiObjectName, const std::string & portName, const std::string & serializedPayload);

protected:
    PyObject * systemMsgCallback;
    std::map<std::pair<int, int>, IEventDelegation *> eventDelegationMap;
};

}
}


#endif