#include "NodeEventEmitter.h"



NodeEventEmitter::NodeEventEmitter(const v8::Local<v8::Function> & func) {
  this->callback.Reset(func);
}


NodeEventEmitter::~NodeEventEmitter() {
}


void NodeEventEmitter::emit(const v8::Local<v8::Value> & localValue) {
  v8::Local<v8::Function> cb = Nan::New(this->callback);
  const unsigned argc = 1;
  v8::Local<v8::Value> argv[1] = { localValue };
  Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);
}
