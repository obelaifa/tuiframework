#include "TFEventEmitter.h"

using namespace std;


TFEventEmitter::TFEventEmitter() {
}


TFEventEmitter::~TFEventEmitter() {
}


void TFEventEmitter::registerEmitterFunction(const std::string & portTypeName,
    bool ( * emitterFunc) (const std::string &, const std::string &, const v8::Local<v8::Value> &)) {
  this->registry[portTypeName] = emitterFunc;
}


bool TFEventEmitter::emitEvent(const std::string & portTypeName, const std::string & tuiObjectName,
    const std::string & channelName, const v8::Local<v8::Value> & value) const {

  std::map<std::string, bool ( * )(const std::string &, const std::string &,
    const v8::Local<v8::Value> &)>::const_iterator iter = this->registry.find(portTypeName);

  if (iter != this->registry.end()) {
      return (*iter).second(tuiObjectName, channelName, value);
  }
  return false;
}


