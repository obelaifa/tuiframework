#ifndef _TFEventEmitterFunc_h_
#define _TFEventEmitterFunc_h_

#include <nan.h>
#include <string>

bool emitDigitalChangedEvent(const std::string & tuiObjectName, const std::string & channelName,
  const v8::Local<v8::Value> & v8Value);
bool emitAnalogChangedEvent(const std::string & tuiObjectName, const std::string & channelName,
  const v8::Local<v8::Value> & v8Value);
bool emitIntegerChangedEvent(const std::string & tuiObjectName, const std::string & channelName,
  const v8::Local<v8::Value> & v8Value);

#endif
