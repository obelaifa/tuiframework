#! /usr/bin/env python3.5

import sys
import tuiclient

def systemMsgSink(msg) :
    if msg == 1 :
        print('CONNECTION ESTABLISHED')
        #tuiclient.setEventCallback('MyTUIObjectInstance', 'Transf', dstmethod)

def dstmethod(name, portname, value) :
    print(name + ' ' + portname + ' ' + value)
    tuiclient.sendEvent('MyTUIObjectInstance', 'LED', '1');
    tuiclient.sendEvent('MyTUIObjectInstance', 'LED', '0');

tuiclient.init()
input()
tuiclient.connectServer(8998, 8999, '127.0.0.1:7999', 0, systemMsgSink)


input()
tuiclient.processEvents()
input()
tuiclient.processEvents()
input()
