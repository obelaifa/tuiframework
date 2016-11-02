#ifndef _EventDelegationFactory_h_
#define _EventDelegationFactory_h_

#include "IEventDelegation.h"

#include <tuiframework/core/Factory.h>
#include <tuiframework/core/Singleton.h>

namespace tuiframework {
namespace python {
    
typedef Factory<int, IEventDelegation> EventDelegationFactory;
typedef Singleton<EventDelegationFactory> EventDelegationFactorySingleton;

}
}

#endif