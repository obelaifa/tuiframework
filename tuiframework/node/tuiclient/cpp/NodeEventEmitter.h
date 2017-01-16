#ifndef _NodeEventEmitter_h_
#define _NodeEventEmitter_h_

#include "CallbackParam.h"

#include <tuiframework/core/IEventSink.h>
#include <nan.h>
#include <string>


class NodeEventEmitter : public tuiframework::IEventSink {
public:
  NodeEventEmitter(const CallbackParam & param);
  virtual ~NodeEventEmitter();

  void emit(const v8::Local<v8::Value> & localValue);

protected:
  Nan::Persistent<v8::Function> callback;
  Nan::Global<v8::Object> self;
};


#endif
