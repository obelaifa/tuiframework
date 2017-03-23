
#include "AttachedObjectsWrap.h"
#include "TUIClientWrap.h"
#include "EventConverter.h"
#include "NodeEventEmitterCommon.h"
#include "TFEventEmitterFunc.h"

#include <tuiframework/client/client.h>
#include <tuilibs/tuitypes/common/CommonTypeReg.h>

#include <iostream>
#include <string>

#include <map>
#include <vector>

#include <stdlib.h>
#include <cstdio>
#include <nan.h>

using namespace tuiframework;
using namespace std;

TUIClientWrap tuiClientWrap;
EventConverter eventConverter;

namespace tfnode {

static std::string convertString(const v8::Local<v8::String> & str) {
  v8::String::Utf8Value param1(str);
  return std::string(*param1);
}


void connected() {
  //cout << "===> connected called" << endl;
  //cout.flush();

  const AttachedObjects & attachedObjects = getAttachedObjects();
  eventConverter.set(attachedObjects);

  NodeEventEmitterFactory & nodeEventEmitterFactory = eventConverter.getNodeEventEmitterFactory();
  nodeEventEmitterFactory.registerCreateFunction("AnalogChannel", &nedCreateEventFunction<AnalogNodeEventEmitter>);
  nodeEventEmitterFactory.registerCreateFunction("DigitalChannel", &nedCreateEventFunction<DigitalNodeEventEmitter>);

  TFEventEmitter & tfEventEmitter = eventConverter.getTFEventEmitter();
  tfEventEmitter.registerEmitterFunction("AnalogChannel", &emitAnalogChangedEvent);
  tfEventEmitter.registerEmitterFunction("DigitalChannel", &emitDigitalChangedEvent);
}


void connect(const Nan::FunctionCallbackInfo<v8::Value> & info) {
  int senderPort = info[0]->ToInteger()->Value();
  int receiverPort = info[1]->ToInteger()->Value();
  string ipAddressAndPort = convertString(info[2]->ToString());

  cout << "==> senderPort: " << senderPort << endl;
  cout << "==> receiverPort: " << receiverPort << endl;
  cout << "==> ipAddressAndPort: " << ipAddressAndPort << endl;

  initTypeRegistration(getEventFactory());
  CommonTypeReg::registerTypes(&getEventFactory(), &getEventChannelFactory());
  tuiClientWrap.setInitCallback(&connected);

  tuiClientWrap.setNodeCallback(info, 3);
  //connectWithTUIServer(8998, 8999, "127.0.0.1:7999", &tuiClientWrap, false);
  connectWithTUIServer(senderPort, receiverPort, ipAddressAndPort, &tuiClientWrap, false);
  info.GetReturnValue().Set(Nan::New("world").ToLocalChecked());
}


void disconnect(const Nan::FunctionCallbackInfo<v8::Value> & info) {
  disconnectFromTUIServer();
}


void processEvents(const Nan::FunctionCallbackInfo<v8::Value> & info) {
  //cout << "===> before processEvents" << endl;
  //cout.flush();
  tuiframework::processEvents();
  //cout << "===> after processEvents" << endl;
  //cout.flush();
}


void getAttachedObjects(const Nan::FunctionCallbackInfo<v8::Value> & info) {
  AttachedObjectsWrap attachedObjectsWrap;
  attachedObjectsWrap.set(tuiframework::getAttachedObjects());

  v8::Local<v8::Object> wrappedObj = attachedObjectsWrap.getWrapped();
  info.GetReturnValue().Set(wrappedObj);
}


void registerEventCallback(const Nan::FunctionCallbackInfo<v8::Value> & info) {
  string instanceName = convertString(info[0]->ToString());
  string portName = convertString(info[1]->ToString());
  cout << "registerEventCallback - " << instanceName << "  " << portName << "  "<< endl;
  v8::Isolate * isolate = info.GetIsolate();
  v8::Local<v8::Function> func = info[2].As<v8::Function>();
  v8::Local<v8::Object> self = info[3]->ToObject();
  CallbackParam param = CallbackParam(*isolate, func, self);
  eventConverter.registerEventCallback(instanceName, portName, param);
}


void deregisterEventCallback(const Nan::FunctionCallbackInfo<v8::Value> & info) {
  string instanceName = convertString(info[0]->ToString());
  string portName = convertString(info[1]->ToString());
  eventConverter.deregisterEventCallback(instanceName, portName);
}


void emitEvent(const Nan::FunctionCallbackInfo<v8::Value> & info) {
  string instanceName = convertString(info[0]->ToString());
  string portName = convertString(info[1]->ToString());
  v8::Local<v8::Value> value = info[2];
  cout << "emitEvent: " << instanceName << "  " << portName << endl;
  eventConverter.emitEvent(instanceName, portName, value);
}


} // namespace tfnode



void InitFunc(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
  exports->Set(Nan::New("connect").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(tfnode::connect)->GetFunction());
  exports->Set(Nan::New("disconnect").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(tfnode::disconnect)->GetFunction());
  exports->Set(Nan::New("processEvents").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(tfnode::processEvents)->GetFunction());
  exports->Set(Nan::New("getAttachedObjects").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(tfnode::getAttachedObjects)->GetFunction());
  exports->Set(Nan::New("registerEventCallback").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(tfnode::registerEventCallback)->GetFunction());
  exports->Set(Nan::New("deregisterEventCallback").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(tfnode::deregisterEventCallback)->GetFunction());
  exports->Set(Nan::New("emitEvent").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(tfnode::emitEvent)->GetFunction());
}


NODE_MODULE(tuiclient, InitFunc)
