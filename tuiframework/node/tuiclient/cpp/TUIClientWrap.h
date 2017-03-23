#ifndef _TUIClientWrap_h_
#define _TUIClientWrap_h_

#include <tuiframework/client/client.h>

#include <nan.h>


class TUIClientWrap : public tuiframework::IEventSink {
public:
  TUIClientWrap();
  virtual ~TUIClientWrap();

  void setNodeCallback(const Nan::FunctionCallbackInfo<v8::Value> & info, int index);
  void setInitCallback(void(*callback)());

  virtual void push(tuiframework::IEvent * e);

protected:
  Nan::Persistent<v8::Function> callback;
  void(*initCallback)();
};

#endif
