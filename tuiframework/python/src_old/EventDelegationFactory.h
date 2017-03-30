#ifndef _EventDelegationFactory_h_
#define _EventDelegationFactory_h_

#include "IEventDelegation.h"

#include <tuiframework/core/Factory.h>
#include <tuiframework/core/Singleton.h>

namespace tuiframework {
namespace python {
typedef tuiframework::Factory<int, tuiframework::python::IEventDelegation> EventDelegationFactory;
typedef tuiframework::Singleton<tuiframework::Factory<int, tuiframework::python::IEventDelegation> > EventDelegationFactorySingleton;
}
}


#endif