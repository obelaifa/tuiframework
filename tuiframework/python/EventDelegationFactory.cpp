#include "EventDelegationFactory.h"

namespace tuiframework {

template<> python::EventDelegationFactory * python::EventDelegationFactorySingleton::instance = 0;

}