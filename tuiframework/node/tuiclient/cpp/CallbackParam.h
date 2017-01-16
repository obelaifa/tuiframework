#ifndef _CallbackParam_h_
#define _CallbackParam_h_

#include <nan.h>

struct CallbackParam {
    CallbackParam(v8::Isolate & isolate, v8::Local<v8::Function> & func, v8::Local<v8::Object> & self) :
      isolate(isolate),
      func(func),
      self(self) {
      }

    v8::Isolate & isolate;
    v8::Local<v8::Function> & func;
    v8::Local<v8::Object> & self;
};


#endif