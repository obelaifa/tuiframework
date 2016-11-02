#include "TUIClient.h"
#include "eventDelegationRegistration.h"

#include <Python.h>
#include <iostream>

using namespace std;
using namespace tuiframework;
using namespace python;

static PyObject * tuiclient_init(PyObject * self, PyObject * args);
static PyObject * tuiclient_connectServer(PyObject * self, PyObject * args);
static PyObject * tuiclient_disconnectServer(PyObject * self, PyObject * args);
static PyObject * tuiclient_setEventCallback(PyObject * self, PyObject * args);
static PyObject * tuiclient_removeEventCallback(PyObject * self, PyObject * args);
static PyObject * tuiclient_processEvents(PyObject * self, PyObject * args);
static PyObject * tuiclient_sendEvent(PyObject * self, PyObject * args);

static PyMethodDef TuiClientMethods[] = {
    {"init",  tuiclient_init, METH_VARARGS, "Initialization of the TUI-client"},
    {"connectServer",  tuiclient_connectServer, METH_VARARGS, "Connect a TUI-server"},
    {"disconnectServer",  tuiclient_disconnectServer, METH_VARARGS, "Disconnect the TUI-server"},
    {"setEventCallback",  tuiclient_setEventCallback, METH_VARARGS, "Set a event callback for a specific port of a tui object"},
    {"removeEventCallback",  tuiclient_removeEventCallback, METH_VARARGS, "Remove the event callback"},
    {"processEvents",  tuiclient_processEvents, METH_VARARGS, "process Events"},
    {"sendEvent",  tuiclient_sendEvent, METH_VARARGS, "Send an event through a specific port of a tui object"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};


static struct PyModuleDef tuiclientmodule = {
   PyModuleDef_HEAD_INIT,
   "tuiclient",   /* name of module */
   NULL, /* module documentation, may be NULL */
   -1,       /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
   TuiClientMethods
};


PyMODINIT_FUNC PyInit_tuiclient(void) {
    return PyModule_Create(&tuiclientmodule);
}

//--------------------------------------------------------------------------------------------

static TUIClient tuiClient;

static PyObject * tuiclient_init(PyObject * self, PyObject * args) {
    initTypeRegistration();
    eventDelegationRegistration();

    Py_INCREF(Py_None);
    return Py_None;    
}


static PyObject * tuiclient_connectServer(PyObject * self, PyObject * args) {
    int mySendPortNr;
    int myReceivePortNr;
    char * serverAddress;
    int ownerShip;
    PyObject * callback;
    if ( ! PyArg_ParseTuple(args, "iisiO:connectServer", &mySendPortNr, &myReceivePortNr, &serverAddress, &ownerShip, &callback)) {
        return NULL;
    }

    if ( ! PyCallable_Check(callback)) {
        PyErr_SetString(PyExc_TypeError, "Parameter must be callable");
        return NULL;
    }

    tuiClient.setSystemMsgCallback(callback);
    connectWithTUIServer(mySendPortNr, myReceivePortNr, serverAddress, &tuiClient, ownerShip != 0);
    
    Py_INCREF(Py_None);
    return Py_None;
}


static PyObject * tuiclient_disconnectServer(PyObject * self, PyObject * args) {
    TUIClientAppSingleton::getInstance()->disconnectFromTUIServer();

    Py_INCREF(Py_None);
    return Py_None;
}


static PyObject * tuiclient_setEventCallback(PyObject * self, PyObject * args) {
    PyObject * result = NULL;
    PyObject * eventCallback;
    const char * tuiObjectName;
    const char * portName;

    if (PyArg_ParseTuple(args, "ssO:setEventCallback", &tuiObjectName, &portName, &eventCallback)) {

        if (!PyCallable_Check(eventCallback)) {
            PyErr_SetString(PyExc_TypeError, "parameter must be callable");
            return NULL;
        }

        Py_XINCREF(eventCallback);

        tuiClient.setEventCallback(tuiObjectName, portName, eventCallback);

        Py_INCREF(Py_None);
        result = Py_None;
    }
    return result;
}


static PyObject * tuiclient_removeEventCallback(PyObject * self, PyObject * args) {
    PyObject * result = NULL;
    const char * tuiObjectName;
    const char * portName;

    if (PyArg_ParseTuple(args, "ss:removeEventCallback", &tuiObjectName, &portName)) {
        tuiClient.removeEventCallback(tuiObjectName, portName);

        Py_INCREF(Py_None);
        result = Py_None;
    }
    return result;
}


static PyObject * tuiclient_processEvents(PyObject * self, PyObject * args) {
    TUIClientAppSingleton::getInstance()->processEvents();

    Py_INCREF(Py_None);
    return Py_None;    
}


static PyObject * tuiclient_sendEvent(PyObject * self, PyObject * args) {
    PyObject * result = NULL;
    const char * tuiObjectName;
    const char * portName;
    const char * serializedPayload;

    if (PyArg_ParseTuple(args, "sss:sendEvent", &tuiObjectName, &portName, &serializedPayload)) {

        tuiClient.sendEvent(tuiObjectName, portName, serializedPayload);

        Py_INCREF(Py_None);
        result = Py_None;
    }

    Py_INCREF(Py_None);
    return Py_None;    
}

