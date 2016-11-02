#include "EventDelegationFactory.h"

namespace tuiframework {
namespace python {

template<> EventDelegationFactory * EventDelegationFactorySingleton::instance = 0;

}
}