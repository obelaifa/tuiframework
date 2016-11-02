#ifndef _NodeEventEmitterCommon_h_
#define _NodeEventEmitterCommon_h_

#include "NodeEventEmitter.h"

#include <nan.h>

namespace tuiframework {

class IEvent;

}

class AnalogNodeEventEmitter : public NodeEventEmitter {
public:
  AnalogNodeEventEmitter(const v8::Local<v8::Function> & func) : NodeEventEmitter(func) { }
  virtual ~AnalogNodeEventEmitter() { }

  virtual void push(tuiframework::IEvent * event);
};


class DigitalNodeEventEmitter : public NodeEventEmitter {
public:
  DigitalNodeEventEmitter(const v8::Local<v8::Function> & func) : NodeEventEmitter(func) { }
  virtual ~DigitalNodeEventEmitter() { }

  virtual void push(tuiframework::IEvent * event);
};


class IntegerNodeEventEmitter : public NodeEventEmitter {
public:
  IntegerNodeEventEmitter(const v8::Local<v8::Function> & func) : NodeEventEmitter(func) { }
  virtual ~IntegerNodeEventEmitter() { }

  virtual void push(tuiframework::IEvent * event);
};

#endif

