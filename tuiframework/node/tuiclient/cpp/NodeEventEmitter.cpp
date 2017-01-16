#include "NodeEventEmitter.h"



NodeEventEmitter::NodeEventEmitter(const CallbackParam & param) {
  this->callback.Reset(param.func);
  this->self.Reset(param.self);
}


NodeEventEmitter::~NodeEventEmitter() {
}


void NodeEventEmitter::emit(const v8::Local<v8::Value> & localValue) {
  v8::Local<v8::Function> cb = Nan::New(this->callback);
  v8::Local<v8::Object> s = Nan::New(this->self);
  const unsigned argc = 2;
  v8::Local<v8::Value> argv[2] = { localValue, s };
  Nan::MakeCallback(s, cb, argc, argv);
}
