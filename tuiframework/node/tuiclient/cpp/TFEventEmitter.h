#ifndef _TFEventEmitter_h_
#define _TFEventEmitter_h_

#include "TFEventEmitter.h"

#include <tuiframework/core/Factory.h>

#include <nan.h>

#include <string>
#include <map>


class TFEventEmitter {
public:
    TFEventEmitter();
    virtual ~TFEventEmitter();
    
    bool emitEvent(const std::string & portTypeName, const std::string & tuiObjectName,
      const std::string & channelName, const v8::Local<v8::Value> & value) const;
    void registerEmitterFunction(const std::string & portName,
      bool ( * emitterFunc) (const std::string &, const std::string &, const v8::Local<v8::Value> &));
    
protected:
    std::map<std::string, bool ( * ) (const std::string &, const std::string &, const v8::Local<v8::Value> &)> registry;
};
    

#endif

