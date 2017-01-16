#ifndef _NodeEventEmitterCommon_h_
#define _NodeEventEmitterCommon_h_

#include "NodeEventEmitter.h"

#include <nan.h>

namespace tuiframework {

class IEvent;

}

class AnalogNodeEventEmitter : public NodeEventEmitter {
public:
  AnalogNodeEventEmitter(const CallbackParam & param) : NodeEventEmitter(param) { }
  virtual ~AnalogNodeEventEmitter() { }

  virtual void push(tuiframework::IEvent * event);
};


class DigitalNodeEventEmitter : public NodeEventEmitter {
public:
  DigitalNodeEventEmitter(const CallbackParam & param) : NodeEventEmitter(param) { }
  virtual ~DigitalNodeEventEmitter() { }

  virtual void push(tuiframework::IEvent * event);
};


class IntegerNodeEventEmitter : public NodeEventEmitter {
public:
  IntegerNodeEventEmitter(const CallbackParam & param) : NodeEventEmitter(param) { }
  virtual ~IntegerNodeEventEmitter() { }

  virtual void push(tuiframework::IEvent * event);
};

#endif

