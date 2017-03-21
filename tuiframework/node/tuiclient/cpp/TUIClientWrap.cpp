#include "TUIClientWrap.h"

using namespace tuiframework;
using namespace std;


TUIClientWrap::TUIClientWrap() {
}


TUIClientWrap::~TUIClientWrap() {
}


void TUIClientWrap::setNodeCallback(const Nan::FunctionCallbackInfo<v8::Value> & info, int index) {
  this->callback.Reset(info[index].As<v8::Function>());
}


void TUIClientWrap::setInitCallback(void(*callback)()) {
  this->initCallback = callback;
}


void TUIClientWrap::push(IEvent * event) {
  if (event->getEventTypeID() == SystemMsg::EventTypeID()) {
    SystemMsg * msg = static_cast<SystemMsg *>(event);
    if (msg->getPayload() == CONNECTION_ESTABLISHED) {
      cout << "CONNECTION ESTABLISHED" << endl;
      cout << "==================>" << getAttachedObjects() << endl;
      this->initCallback();

      v8::Local<v8::Function> cb = Nan::New(this->callback);
      const unsigned argc = 1;
      v8::Local<v8::Value> argv[1] = { Nan::New("CONNECTION ESTABLISHED").ToLocalChecked() };
      Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);
    }
  }
}

