#ifndef _NodeEventEmitterFactory_h_
#define _NodeEventEmitterFactory_h_

#include "NodeEventEmitter.h"

#include <tuiframework/core/Factory.h>

#include <nan.h>

#include <string>


//template <class T> NodeEventEmitter * nedCreateEventFunction(const v8::Local<v8::Function> & func) {
template <class T> NodeEventEmitter * nedCreateEventFunction(void * arg) {
  CallbackParam * param = static_cast<CallbackParam *>(arg);
  return new T(*param);
}


class NodeEventEmitterFactory {
public:
    NodeEventEmitterFactory();
    virtual ~NodeEventEmitterFactory();
    
    virtual NodeEventEmitter * createInstance(const std::string & key, void * arg);
    virtual void registerCreateFunction(const std::string & key, NodeEventEmitter * ( * createFunction) (void *));
    
protected:
    tuiframework::Factory<std::string, NodeEventEmitter> factory;
};
    

#endif

