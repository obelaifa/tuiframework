#include "NodeEventEmitterFactory.h"

using namespace std;


NodeEventEmitterFactory::NodeEventEmitterFactory() {
}


NodeEventEmitterFactory::~NodeEventEmitterFactory() {

}


NodeEventEmitter * NodeEventEmitterFactory::createInstance(const string & key, void * arg) {
  return this->factory.createInstance(key, arg);
}


void NodeEventEmitterFactory::registerCreateFunction(const string & key, NodeEventEmitter * ( * createFunction) (void *)) {
  this->factory.registerCreateFunction(key, createFunction);
}

