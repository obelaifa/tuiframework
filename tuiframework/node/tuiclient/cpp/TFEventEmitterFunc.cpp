#define USE_TFDEBUG

#include "TFEventEmitterFunc.h"

#include <tuilibs/tuitypes/common/CommonTypeReg.h>
#include <tuiframework/client/client.h>
#include <tuiframework/core/IEventSink.h>

#include <tuiframework/logging/Logger.h>

#include <iostream>

using namespace std;
using namespace tuiframework;

bool emitDigitalChangedEvent(const std::string & tuiObjectName, const std::string & channelName, const v8::Local<v8::Value> & v8Value) {
  bool value = v8Value->BooleanValue();
  TFDEBUG("emitDigitalChangedEvent - " << "tuiObjectName: " << tuiObjectName << "  channelName: " << channelName << "  value: " << value)

  IEventSink * sink = getSinkChannel(tuiObjectName, channelName);
  if ( ! sink) {
    return false;
  }
  sink->push(new DigitalChangedEvent(-1, -1, value));
  return true;
}


bool emitAnalogChangedEvent(const std::string & tuiObjectName, const std::string & channelName, const v8::Local<v8::Value> & v8Value) {
  double value = v8Value->NumberValue();
  TFDEBUG("emitAnalogChangedEvent - " << "tuiObjectName: " << tuiObjectName << "  channelName: " << channelName << "  value: " << value)

  IEventSink * sink = getSinkChannel(tuiObjectName, channelName);
  if ( ! sink) {
    return false;
  }
  sink->push(new AnalogChangedEvent(-1, -1, value));
  return true;
}


bool emitIntegerChangedEvent(const std::string & tuiObjectName, const std::string & channelName, const v8::Local<v8::Value> & v8Value) {
  int value = v8Value->IntegerValue();
  TFDEBUG("emitIntegerChangedEvent - " << "tuiObjectName: " << tuiObjectName << "  channelName: " << channelName << "  value: " << value)

  IEventSink * sink = getSinkChannel(tuiObjectName, channelName);
  if ( ! sink) {
    return false;
  }
  sink->push(new IntegerChangedEvent(-1, -1, value));
  return true;
}




/*
typedef tuiframework::EPEventMsg<bool, 11>                  DigitalChangedEvent;
typedef tuiframework::EPEventMsg<float, 12>                 AnalogChangedEvent;
typedef tuiframework::EPEventMsg<int, 13>                   IntegerChangedEvent;
typedef tuiframework::EPEventMsg<TrackerData, 14>           TrackerChangedEvent;
typedef tuiframework::EPEventMsg<Matrix4Data, 15>           Matrix4ChangedEvent;
typedef tuiframework::EPEventMsg<HapticAngle, 16>           HapticChangedEvent;

typedef tuiframework::EPEventMsg<KinectJoint, 18>           KinectEvent;
typedef tuiframework::EPEventMsg<Gesture, 19>               GestureEvent;
typedef tuiframework::EPEventMsg<Vector3d, 20>              Vector3dEvent;
typedef tuiframework::EPEventMsg<MouseData, 21>             MouseEvent;
typedef tuiframework::EPEventMsg<VectorList3d, 22>          VectorList3dEvent;

typedef tuiframework::EPEventMsg<Vector4<double>, 23>                   Vector4Event;
typedef tuiframework::EPEventMsg<PackedType<Vector4<double> >, 24>      PackedVector4Event;
typedef tuiframework::EPEventMsg<Matrix4<double>, 25>                   Matrix4Event;
typedef tuiframework::EPEventMsg<PackedType<Matrix4<double> >, 26>      PackedMatrix4Event;
*/


// NumberValue