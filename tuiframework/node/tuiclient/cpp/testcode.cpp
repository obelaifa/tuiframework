#include "Init.h"

#include <tuiframework/client/client.h>
#include <tuilibs/tuitypes/common/CommonTypeReg.h>
//#include <tuiframework/core/AttachedObjects.h>

#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <nan.h>

using namespace tuiframework;
using namespace std;

Init init;

void Method(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  initTypeRegistration(getEventFactory());
  CommonTypeReg::registerTypes(&getEventFactory(), &getEventChannelFactory());
  connectWithTUIServer(8998, 8999, "127.0.0.1:7999", &init, false);
  info.GetReturnValue().Set(Nan::New("world").ToLocalChecked());
}


void Method2(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  cout << "===> before processEvents" << endl;
  cout.flush();
  processEvents();
  cout << "===> after processEvents" << endl;
  cout.flush();
  processEvents();
  info.GetReturnValue().Set(Nan::New("world2").ToLocalChecked());
}


void RunCallback(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Function> cb = info[0].As<v8::Function>();

  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  obj->Set(Nan::New("msg").ToLocalChecked(), Nan::New("Huhu").ToLocalChecked());

  v8::Local<v8::Object> obj2 = Nan::New<v8::Object>();
  obj2->Set(Nan::New("text").ToLocalChecked(), Nan::New("Haha").ToLocalChecked());
  obj->Set(Nan::New("value").ToLocalChecked(), obj2);

  v8::Handle<v8::Array> arr = Nan::New<v8::Array>(3);

  arr->Set(0, Nan::New("Val-1").ToLocalChecked());
  arr->Set(1, Nan::New("Val-2").ToLocalChecked());
  arr->Set(2, Nan::New("Val-3").ToLocalChecked());
  obj->Set(Nan::New("arr").ToLocalChecked(), arr);

  const unsigned argc = 2;
  v8::Local<v8::Value> argv[2] = { Nan::New("hello world").ToLocalChecked(), obj };
  Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);
}


void Add(const Nan::FunctionCallbackInfo<v8::Value>& info) {

  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }

  double arg0 = info[0]->NumberValue();
  double arg1 = info[1]->NumberValue();
  v8::Local<v8::Number> num = Nan::New(arg0 + arg1);

  info.GetReturnValue().Set(num);
}


void TestFunc(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> obj = info[0]->ToObject();
  v8::Local<v8::Value> val = obj->Get(Nan::New("myValue").ToLocalChecked());
  if (val->IsString()) {
    v8::Local<v8::String> str = val->ToString();
    cout << val->IsString() << endl;
    cout << str->Length() << endl;
    v8::String::Utf8Value param1(str);
    std::string str2 = std::string(*param1);
    cout << "String: " << str2 << endl;
  }
  if (val->IsNumber()) {
    cout << "Number: " << val->NumberValue() << endl;
    cout << "Integer: " << val->IntegerValue() << endl;
  }
  if (val->IsBoolean()) {
    cout << "Boolean: " << val->BooleanValue() << endl;
  }
  if (val->IsArray()) {
    cout << "Array" << endl;
    v8::Local<v8::Array> arr = v8::Local<v8::Array>::Cast(val);
    int length = arr->Length();
    for (int i = 0; i < length; ++i) {
      v8::Local<v8::Value> arrVal = arr->Get(i);
      if (arrVal->IsNumber()) {
        cout << "Number: [" << i << "]: " << arrVal->NumberValue() << endl;
      }
    }
    cout << "Length: " << arr->Length() << endl;
  }
}


void funcGetAttachedObjects(const Nan::FunctionCallbackInfo<v8::Value> & info) {
  cout << "==================>" << getAttachedObjects() << endl;
}


void InitFunc(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
  exports->Set(Nan::New("tuiclient").ToLocalChecked(),
                Nan::New<v8::FunctionTemplate>(Method)->GetFunction());
  exports->Set(Nan::New("processEvents").ToLocalChecked(),
                Nan::New<v8::FunctionTemplate>(Method2)->GetFunction());

  exports->Set(Nan::New("runCallback").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(RunCallback)->GetFunction());

  exports->Set(Nan::New("add").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(Add)->GetFunction());

  exports->Set(Nan::New("testFunc").ToLocalChecked(),
                  Nan::New<v8::FunctionTemplate>(TestFunc)->GetFunction());

  exports->Set(Nan::New("getAttachedObjects").ToLocalChecked(),
                    Nan::New<v8::FunctionTemplate>(funcGetAttachedObjects)->GetFunction());
}

NODE_MODULE(tuiclient, InitFunc)
