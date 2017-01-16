#include "AttachedObjectsWrap.h"

#include <tuiframework/logging/Logger.h>

using namespace tuiframework;
using namespace std;


AttachedObjectsWrap::AttachedObjectsWrap() {
}


AttachedObjectsWrap::~AttachedObjectsWrap() {
}


void AttachedObjectsWrap::set(const tuiframework::AttachedObjects & attachedObjects) {
  this->attachedObjects = attachedObjects;
}


v8::Local<v8::Object> AttachedObjectsWrap::getWrapped() const {

  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  // generate TUIObjectTypeWrap
  {
    const vector<TUIObjectType> & typeVector = this->attachedObjects.getTUIObjectTypeVector();
    std::vector<TUIObjectType>::const_iterator i = typeVector.begin(), e = typeVector.end();
    v8::Local<v8::Object> tuiObjectTypeMap = Nan::New<v8::Object>();
    while (i != e) {
      v8::Local<v8::Object> tuiObjectType = this->getWrappedTUIObjectType((*i));
      tuiObjectTypeMap->Set(Nan::New((*i).getName()).ToLocalChecked(), tuiObjectType);
      ++i;
    }
    obj->Set(Nan::New("tuiObjectTypeObjs").ToLocalChecked(), tuiObjectTypeMap);
  }

  {
    const std::vector<TUIObjectInstance> & instanceVector = this->attachedObjects.getTUIObjectInstanceVector();
    //v8::Local<v8::Object> tuiObjectInstanceMap ;
    std::vector<TUIObjectInstance>::const_iterator i = instanceVector.begin();
    std::vector<TUIObjectInstance>::const_iterator e = instanceVector.end();
    v8::Handle<v8::Array> tuiObjectInstanceArray = Nan::New<v8::Array>(instanceVector.size());
    int counter = 0;
    while (i != e) {
      TFINFO("TUIObject: '" << (*i).getName() << "'" << "  Type: '" << (*i).getTypeName() << "'")
      v8::Local<v8::Object> tuiObjectInstance = this->getWrappedTUIObjectInstance((*i));
      //tuiObjectInstanceMap->Set(Nan::New((*i).getName()).ToLocalChecked(), tuiObjectInstance);
      tuiObjectInstanceArray->Set(counter, tuiObjectInstance);
      ++counter;
      ++i;
    }
    //obj->Set(Nan::New("tuiObjectInstances").ToLocalChecked(), tuiObjectInstanceMap);
    obj->Set(Nan::New("tuiObjectInstanceArray").ToLocalChecked(), tuiObjectInstanceArray);
  }

  return obj;
}


v8::Local<v8::Object> AttachedObjectsWrap::getWrappedTUIObjectInstance(const TUIObjectInstance & instance) const {
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  obj->Set(Nan::New("name").ToLocalChecked(), Nan::New(instance.getName()).ToLocalChecked());
  obj->Set(Nan::New("type").ToLocalChecked(), Nan::New(instance.getTypeName()).ToLocalChecked());
  obj->Set(Nan::New("description").ToLocalChecked(), Nan::New(instance.getDescription()).ToLocalChecked());
  return obj;
}


v8::Local<v8::Object> AttachedObjectsWrap::getWrappedTUIObjectType(const TUIObjectType & type) const {
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  obj->Set(Nan::New("name").ToLocalChecked(), Nan::New(type.getName()).ToLocalChecked());

  const map<string, Port> & portMap = type.getPortMap();
  map<string, Port>::const_iterator i = portMap.begin();
  map<string, Port>::const_iterator e = portMap.end();
  v8::Local<v8::Object> wrappedPortMap = Nan::New<v8::Object>();
  while (i != e) {
    v8::Local<v8::Object> wrappedPort = this->getWrappedPort((*i).second);
    wrappedPortMap->Set(Nan::New((*i).second.getName()).ToLocalChecked(), wrappedPort);
    ++i;
  }
  obj->Set(Nan::New("ports").ToLocalChecked(), wrappedPortMap);
  obj->Set(Nan::New("description").ToLocalChecked(), Nan::New(type.getDescription()).ToLocalChecked());

  return obj;
}


v8::Local<v8::Object> AttachedObjectsWrap::getWrappedPort(const tuiframework::Port & port) const {
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  obj->Set(Nan::New("name").ToLocalChecked(), Nan::New(port.getName()).ToLocalChecked());
  obj->Set(Nan::New("type").ToLocalChecked(), Nan::New(port.getTypeName()).ToLocalChecked());
  Port::DataFlowDirection flowDirection = port.getDataFlowDirection();
  obj->Set(Nan::New("flowDirection").ToLocalChecked(), Nan::New(flowDirection));
  obj->Set(Nan::New("description").ToLocalChecked(), Nan::New(port.getDescription()).ToLocalChecked());
  return obj;
}
