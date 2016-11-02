#ifndef _TUIAttachedObjectsWrap_h_
#define _TUIAttachedObjectsWrap_h_

#include <tuiframework/core/AttachedObjects.h>

#include <nan.h>

namespace tuiframework {

class TUIObjectInstance;
class TUIObjectType;
class Port;

}


class AttachedObjectsWrap {
public:
  AttachedObjectsWrap();
  virtual ~AttachedObjectsWrap();

  void set(const tuiframework::AttachedObjects & attachedObjects);

  v8::Local<v8::Object> getWrapped() const;

protected:
  v8::Local<v8::Object> getWrappedTUIObjectInstance(const tuiframework::TUIObjectInstance & instance) const;
  v8::Local<v8::Object> getWrappedTUIObjectType(const tuiframework::TUIObjectType & type) const;
  v8::Local<v8::Object> getWrappedPort(const tuiframework::Port & port) const;

protected:
  tuiframework::AttachedObjects attachedObjects;
};


#endif