#ifndef _IEventDelegation_H_
#define _IEventDelegation_H_

#include <Python.h>

#include <string>

namespace tuiframework {
namespace python {
    
class IEventDelegation {
public:
    virtual ~IEventDelegation() { }

    virtual void createConnection(const std::string & tuiObjectName, const std::string & portName, PyObject * callback, const std::string & description, const std::string & constraintMin, const std::string & constraintMax, const std::string & trafoType, const std::string & trafoNo) = 0;
};

}
}

#endif