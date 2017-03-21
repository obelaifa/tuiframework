#ifndef _EventDelegation_H_
#define _EventDelegation_H_

#include "IEventDelegation.h"

#include <tuiframework/client/client.h>

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

    virtual void createConnection(const std::string & tuiObjectName, const std::string & portName, PyObject * callback, const std::string & description, const std::string & constraintMin, const std::string & constraintMax, const std::string & trafoType, const std::string & trafoNo) {
		this->callback = callback;
        this->tuiObjectName = tuiObjectName;
        this->portName = portName;
		this->description = description;
		this->constraintMin = constraintMin;
		this->constraintMax = constraintMax;
		this->trafoType = trafoType;
		this->trafoNo = trafoNo;
		std::string value = "0.0";
		
		//Permits to initialize the dictionnary in the Python Interface
		{
			PyObject * arglist = Py_BuildValue("ssssssss", this->tuiObjectName.c_str(), this->portName.c_str(), value.c_str(), this->description.c_str(), this->constraintMin.c_str(), this->constraintMax.c_str(), this->trafoType.c_str(), this->trafoNo.c_str());
			PyObject_CallObject(this->callback, arglist);
		}

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
        const T & payload = e->getPayload();
        this->ss.str("");
        this->ss << payload;
        PyObject * arglist = Py_BuildValue("ssssssss", this->tuiObjectName.c_str(), this->portName.c_str(), this->ss.str().c_str(), this->description.c_str(), this->constraintMin.c_str(), this->constraintMax.c_str(), this->trafoType.c_str(), this->trafoNo.c_str());
        PyObject_CallObject(this->callback, arglist);
        Py_DECREF(arglist);
    }
    
protected:
    PyObject * callback;
    std::stringstream ss;

    std::string tuiObjectName;
    std::string portName;
	std::string description;
	std::string constraintMin;
	std::string constraintMax;
	std::string trafoType;
	std::string trafoNo;
};

}
}

#endif