#include "TUIClient.h"


using namespace std;
using namespace tuiframework;
using namespace python;

TUIClient::TUIClient() {
}


TUIClient::~TUIClient() {
}


void TUIClient::setSystemMsgCallback(PyObject * systemMsgCallback) {
    this->systemMsgCallback = systemMsgCallback;
}


void TUIClient::push(IEvent * event) {
    if (event->getEventTypeID() == SystemMsg::EventTypeID()) {
        SystemMsg * msg = static_cast<SystemMsg *>(event);
        if (msg->getPayload() == CONNECTION_ESTABLISHED) {
            cout << "CONNECTION ESTABLISHED" << endl;
            PyObject * arglist = Py_BuildValue("(i)", CONNECTION_ESTABLISHED);
            PyObject_CallObject(this->systemMsgCallback, arglist);
            Py_DECREF(arglist);
        }
    }
}


void TUIClient::setEventCallback(PyObject * callback) {

	std::vector<TUIObjectInstance> objectInstances = getAttachedObjects().getTUIObjectInstanceVector();
	std::vector<TUIObjectType> objectTypes = getAttachedObjects().getTUIObjectTypeVector();
	int instanceID = 0;

	for (vector<TUIObjectInstance>::iterator it = objectInstances.begin(); it != objectInstances.end(); it++) {
		for (vector<TUIObjectType>::iterator typeIt = objectTypes.begin(); typeIt != objectTypes.end(); typeIt++) {
			if (typeIt->getName() == it->getTypeName() && instanceID != it->getID()) {
				instanceID = it->getID();
				for (map<string, tuiframework::Port>::iterator typeMapIt2 = typeIt->getPortMap().begin(); typeMapIt2 != typeIt->getPortMap().end(); typeMapIt2++)
				{
					if (typeMapIt2->second.getDataFlowDirection() == 2)
						continue;

					std::string constraintMin = "empty";
					std::string constraintMax = "empty";
					std::string trafoType = "empty";
					std::string trafoNo = "empty";

					if (typeMapIt2->second.getTypeName().compare("AnalogChannel") == 0) {
						constraintMin = typeMapIt2->second.getParameterGroup().getParameterGroup("Constraint").getParameterMap().at("min");
						constraintMax = typeMapIt2->second.getParameterGroup().getParameterGroup("Constraint").getParameterMap().at("max");
						trafoType = typeMapIt2->second.getParameterGroup().getParameterGroup("Meta").getParameterMap().at("TrafoType");
						trafoNo = typeMapIt2->second.getParameterGroup().getParameterGroup("Meta").getParameterMap().at("TrafoNo");
					}

					TUIObjectStubContainer & tc = TUIClientAppProvider::getInstance()->getTUIObjectStubContainer();
					TUIObjectStub * t = tc.getStub(it->getName());

					IEventChannel * iec = t->getSourceChannel(typeMapIt2->second.getName());

					IEventDelegation * ied = EventDelegationFactorySingleton::getInstance()->createInstance(iec->getChannelTypeID());

					int tuiObjectNr = t->getID();
					int portNr = iec->getPortNr();

					this->eventDelegationMap.erase(pair<int, int>(tuiObjectNr, portNr));
					this->eventDelegationMap[pair<int, int>(tuiObjectNr, portNr)] = ied;

					ied->createConnection(it->getName(), typeMapIt2->second.getName(), callback, typeMapIt2->second.getDescription(), constraintMin, constraintMax, trafoType, trafoNo);
				}
			}
		}
	}
}


void TUIClient::removeEventCallback(const std::string & tuiObjectName, const std::string & portName) {
    TUIObjectStubContainer & tc = TUIClientAppProvider::getInstance()->getTUIObjectStubContainer();
    TUIObjectStub * t = tc.getStub(tuiObjectName);
    IEventChannel * iec = t->getSinkChannel(portName);
    int tuiObjectNr = t->getID();
    int portNr = iec->getPortNr();

    int res = this->eventDelegationMap.erase(pair<int, int>(tuiObjectNr, portNr));
    if (res == 0) {
        // failed
    }
}


void TUIClient::sendEvent(const std::string & tuiObjectName, const std::string & portName, const std::string & serializedPayload) {

    TUIObjectStubContainer & tc = TUIClientAppProvider::getInstance()->getTUIObjectStubContainer();
    TUIObjectStub * t = tc.getStub(tuiObjectName);
    IEventChannel * iec = t->getSinkChannel(portName);
   
    IEvent * event = TUIClientAppProvider::getInstance()->getEventFactory().createInstance(iec->getChannelTypeID());
    // IEvent * event = EventFactorySingleton::getInstance()->createInstance(iec->getChannelTypeID());
    if (event) {
        stringstream ss;
        ss << "-1 -1 " << serializedPayload;
        //ss.str(serializedPayload);
        ss >> event;
        //cout << "payload: " << serializedPayload << "Event: " <<  event << endl;
        iec->push(event);
    }
}


