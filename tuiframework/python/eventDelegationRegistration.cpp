
#include "eventDelegationRegistration.h"
#include "EventDelegation.h"
#include "IEventDelegation.h"
#include "EventDelegationFactory.h"

#include <tuiframework/client/client.h>
#include <tuilibs/tuitypes/common/CommonTypeReg.h>



namespace tuiframework {
namespace python {

template <class T, int typeID>
IEventDelegation * createEventDelegationFunction(void * arg = 0) {
    return new EventDelegation<T, typeID>();
}


template<class T, int typeID>
void doRegistration() {
    EventDelegationFactory * factory = EventDelegationFactorySingleton::getInstance();
    factory->registerCreateFunction(EPEventMsg<T, typeID>().getEventTypeID(), createEventDelegationFunction<T, typeID>);
}


void eventDelegationRegistration() {
    doRegistration<bool, 11>();
    doRegistration<float, 12>();
    doRegistration<TrackerData, 14>();
    doRegistration<Matrix4Data, 15>();
    doRegistration<HapticAngle, 16>();
    doRegistration<Matrix4<double>, 25 >();
}


}
}