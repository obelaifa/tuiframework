#ifndef _EventConverter_h_
#define _EventConverter_h_

#include "NodeEventEmitterFactory.h"
#include "TFEventEmitter.h"
#include "CallbackParam.h"

#include <tuiframework/core/AttachedObjects.h>
#include <tuiframework/core/TUIObjectType.h>
#include <tuiframework/core/TUIObjectInstance.h>

#include <map>
#include <nan.h>


namespace tuiframework {

class IEventSink;

}


class EventConverter {
public:
  EventConverter();
  virtual ~EventConverter();

  void set(const tuiframework::AttachedObjects & attachedObjects);
  NodeEventEmitterFactory & getNodeEventEmitterFactory();
  TFEventEmitter & getTFEventEmitter();

  bool registerEventCallback(const std::string & instanceName, const std::string & portName, const CallbackParam & param);
  bool deregisterEventCallback(const std::string & instanceName, const std::string & portName);

  bool emitEvent(const std::string & instanceName, const std::string & portName, const v8::Local<v8::Value> & value);

protected:
  std::map<std::string, tuiframework::TUIObjectInstance> tuiObjectInstanceMap;
  std::map<std::string, tuiframework::TUIObjectType> tuiObjectTypeMap;
  std::map<std::pair<std::string, std::string>, tuiframework::IEventSink * > eventCallbackMap;

  NodeEventEmitterFactory nodeEventEmitterFactory;
  TFEventEmitter tfEventEmitter;
};


#endif

