#ifndef _NodeEventEmitterFactory_h_
#define _NodeEventEmitterFactory_h_

#include "NodeEventEmitter.h"

#include <tuiframework/core/Factory.h>

#include <nan.h>

#include <string>


//template <class T> NodeEventEmitter * nedCreateEventFunction(const v8::Local<v8::Function> & func) {
template <class T> NodeEventEmitter * nedCreateEventFunction(void * arg) {
  v8::Local<v8::Function> * func = static_cast<v8::Local<v8::Function> *>(arg);
  return new T(*func);
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

