
#include "eventDelegationRegistration.h"
#include "EventDelegation.h"
#include "IEventDelegation.h"
#include "EventDelegationFactory.h"


#include <tuiframework/client/client.h>

namespace tuiframework {
namespace python {

template <class T>
IEventDelegation * createEventDelegationFunction(void * arg = 0) {
    return new EventDelegation<T>();
}

template<class T>
void doRegistration() {
    EventDelegationFactory * factory = EventDelegationFactorySingleton::getInstance();
    factory->registerCreateFunction(EPEventMsg<T>().getEventTypeID(), createEventDelegationFunction<T>);
}

void eventDelegationRegistration() {
    doRegistration<bool>();
    doRegistration<float>();
    doRegistration<TrackerData>();
    doRegistration<Matrix4Data>();
    doRegistration<HapticAngle>();
    doRegistration<Matrix4x4<double> >();
}


}
}