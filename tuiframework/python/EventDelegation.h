#ifndef _EventDelegation_H_
#define _EventDelegation_H_

#include "IEventDelegation.h"

#include <tuiframework/client/client.h>

#include <Python.h>
#include <string>
#include <sstream>
#include <stdio.h>

namespace tuiframework {
namespace python {

template <class T, int typeID>
class EventDelegation : public IEventDelegation {
public:

    typedef tuiframework::EPEventMsg<T, typeID> E;
    typedef EventDelegation<T, typeID> C;

    EventDelegation() : callback(0) {
        std::cout << ">>>>>>>>>> EventDelegation()" << std::endl;
    }

    virtual ~EventDelegation() {
        Py_DECREF(this->callback);
    }

    virtual void createConnection(const std::string & tuiObjectName, const std::string & portName, PyObject * callback) {
        this->callback = callback;
        this->tuiObjectName = tuiObjectName;
        this->portName = portName;
        try {
            CONNECT(E, tuiObjectName.c_str(), portName.c_str(), C, this, &C::changed);
            std::cout << ">>>>>>>>>> CONNECT()" << std::endl;
        } catch (const Exception & e) {
            std::cerr << "Exception" << std::endl;
            std::cerr << e.getFormattedString() << std::endl;
        }
    }


    void removeConnection() {
         DISCONNECT(E, this->tuiObjectName.c_str(), this->portName.c_str(), C, this, E::changed);
    }
    

    void changed(const tuiframework::EPEventMsg<T, typeID> * e) {
        std::cout << *e << std::endl;
        const T & payload = e->getPayload();
        this->ss.str("");
        this->ss << payload;
        PyObject * arglist = Py_BuildValue("sss", this->tuiObjectName.c_str(), this->portName.c_str(), this->ss.str().c_str());
        PyObject_CallObject(this->callback, arglist);
        Py_DECREF(arglist);
    }
    
protected:
    PyObject * callback;
    std::stringstream ss;
    std::string tuiObjectName;
    std::string portName;
};

}
}

#endif