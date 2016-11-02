#ifndef _NodeEventEmitter_h_
#define _NodeEventEmitter_h_

#include <tuiframework/core/IEventSink.h>
#include <nan.h>
#include <string>


class NodeEventEmitter : public tuiframework::IEventSink {
public:
  NodeEventEmitter(const v8::Local<v8::Function> & func);
  virtual ~NodeEventEmitter();

  void emit(const v8::Local<v8::Value> & localValue);

protected:
  Nan::Persistent<v8::Function> callback;
};


#endif
