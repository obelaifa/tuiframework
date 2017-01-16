#include "EventConverter.h"

#include <tuiframework/client/TUIClientAppProvider.h>
#include <tuiframework/logging/Logger.h>

using namespace tuiframework;
using namespace std;


EventConverter::EventConverter() {
}


EventConverter::~EventConverter() {
}


NodeEventEmitterFactory & EventConverter::getNodeEventEmitterFactory() {
  return this->nodeEventEmitterFactory;
}


TFEventEmitter & EventConverter::getTFEventEmitter() {
  return this->tfEventEmitter;
}



void EventConverter::set(const tuiframework::AttachedObjects & attachedObjects) {
  {
    this->tuiObjectTypeMap.clear();
    const vector<TUIObjectType> & typeVector = attachedObjects.getTUIObjectTypeVector();
    std::vector<TUIObjectType>::const_iterator i = typeVector.begin();
    std::vector<TUIObjectType>::const_iterator e = typeVector.end();
    while (i != e) {
      this->tuiObjectTypeMap.insert(map<string, TUIObjectType>::value_type((*i).getName(), *i));
      ++i;
    }
  }
  {
    this->tuiObjectInstanceMap.clear();
    const vector<TUIObjectInstance> & instanceVector = attachedObjects.getTUIObjectInstanceVector();
    std::vector<TUIObjectInstance>::const_iterator i = instanceVector.begin();
    std::vector<TUIObjectInstance>::const_iterator e = instanceVector.end();
    while (i != e) {
      this->tuiObjectInstanceMap.insert(map<string, TUIObjectInstance>::value_type((*i).getName(), *i));
      ++i;
    }
  }
}


bool EventConverter::registerEventCallback(const string & instanceName, const string & portName,
    const CallbackParam & param) {

  this->deregisterEventCallback(instanceName, portName);

  map<string, TUIObjectInstance>::const_iterator instanceIter = this->tuiObjectInstanceMap.find(instanceName);
  if (instanceIter == this->tuiObjectInstanceMap.end()) {
    TFERROR("Requested TUIObjectInstance '" << instanceName << "' not found.")
    return false;
  }

  const string & typeName = (*instanceIter).second.getTypeName();
  TFINFO("Requested TUIOBjectInstance '" << instanceName << "'  has the type: '" << typeName << "'")

  map<string, TUIObjectType>::const_iterator typeIter = this->tuiObjectTypeMap.find(typeName);
  if (typeIter == this->tuiObjectTypeMap.end()) {
    TFERROR("Requested TUIObjectType '" << typeName << "' not found.")
    return false;
  }

  const map<string, Port> & portMap = (*typeIter).second.getPortMap();
  map<string, Port>::const_iterator portIter = portMap.find(portName);
  if (portIter == portMap.end()) {
    TFERROR("Requested Port '" << portName << "' of TUIOBjectType '" << typeName << "' not found")
    return false;
  }

  IEventChannel * sourceChannel = getSourceChannel(instanceName, portName);

  void * arg = reinterpret_cast<void *>(&const_cast<CallbackParam &>(param));
  NodeEventEmitter * emitter = this->nodeEventEmitterFactory.createInstance((*portIter).second.getTypeName(), arg);
  TFINFO("Factory -> port '" << portName << "' type: '" << (*portIter).second.getTypeName() << "'" << emitter)
  sourceChannel->addEventSink(emitter);
}


bool EventConverter::deregisterEventCallback(const string & instanceName, const string & portName) {

}


bool EventConverter::emitEvent(const std::string & instanceName, const std::string & portName, const v8::Local<v8::Value> & value) {
  map<string, TUIObjectInstance>::const_iterator instanceIter = this->tuiObjectInstanceMap.find(instanceName);
  if (instanceIter == this->tuiObjectInstanceMap.end()) {
    TFERROR("Requested TUIObjectInstance '" << instanceName << "' not found.")
    return false;
  }

  const string & typeName = (*instanceIter).second.getTypeName();
  TFINFO("Requested TUIOBjectInstance '" << instanceName << "'  has the type: '" << typeName << "'")

  map<string, TUIObjectType>::const_iterator typeIter = this->tuiObjectTypeMap.find(typeName);
  if (typeIter == this->tuiObjectTypeMap.end()) {
    TFERROR("Requested TUIObjectType '" << typeName << "' not found.")
    return false;
  }

  const map<string, Port> & portMap = (*typeIter).second.getPortMap();
  map<string, Port>::const_iterator portIter = portMap.find(portName);
  if (portIter == portMap.end()) {
    TFERROR("Requested Port '" << portName << "' of TUIOBjectType '" << typeName << "' not found")
    return false;
  }

  const std::string & portTypeName = (*portIter).second.getTypeName();
  return this->tfEventEmitter.emitEvent(portTypeName, instanceName, portName, value);
}
