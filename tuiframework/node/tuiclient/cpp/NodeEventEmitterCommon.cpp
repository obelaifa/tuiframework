#include "NodeEventEmitterCommon.h"

#include <tuiframework/core/Event.h>
#include <tuilibs/tuitypes/common/CommonTypeReg.h>
#include <tuiframework/logging/Logger.h>

using namespace tuiframework;


void AnalogNodeEventEmitter::push(IEvent * event) {
  AnalogChangedEvent * e = static_cast<AnalogChangedEvent *>(event);
  float value = e->getPayload();
  // TFINFO("AnalogNodeEventEmitter: " << *event)
  v8::Local<v8::Value> localValue = Nan::New(value);
  this->emit(localValue);
}


void DigitalNodeEventEmitter::push(IEvent * event) {
  AnalogChangedEvent * e = static_cast<AnalogChangedEvent *>(event);
  bool value = e->getPayload();
  // TFINFO("AnalogNodeEventEmitter: " << *event)
  v8::Local<v8::Value> localValue = Nan::New(value);
  this->emit(localValue);
}


void IntegerNodeEventEmitter::push(IEvent * event) {
  IntegerChangedEvent * e = static_cast<IntegerChangedEvent *>(event);
  bool value = e->getPayload();
  // TFINFO("AnalogNodeEventEmitter: " << *event)
  v8::Local<v8::Value> localValue = Nan::New(value);
  this->emit(localValue);
}
