#! /usr/bin/env python3.5
import sys
import tuiclient
import json
from time import sleep
import _thread
import socket

## Dictionary where we store all the values, and the meta datas.
JSONdict = dict()
## Dictionary used for the UDP connection, filled only with the values.
TUIdict = dict()

##
#  This function is called by the C++ code after a successfull connection with TUI.
#  This is assuring a correct time flow for the connection between the TUI Objects and the server.
#  @param msg Unused parameter.
def systemMsgSink(msg):
	print('CONNECTION ESTABLISHED')

	tuiclient.setEventCallback(dstmethod) # We call only one time this function, all the connections between the TUI objects and the server are done, based on the XML file, in the C++ code.

	print("EVENT CALLBACK SUCEEDED")
	print("PYTHON INTERFACE READY")

##
#  This function is called automatically each time a value changes.
#  As this function also handles the initialization of the dictionnary, 
#  it is called for each TUI objects before any connection to make sure they are all stored into the dictionary (and so into the JSON file).
#  @param name The TUIObject's name.
#  @param portname The port's name.
#  @param value The value of the port.
#  @param description The description of the port (node name for the 3D scene).
#  @param constraintMin The value of the minimum constraint.
#  @param constraintMax The value of the maximum constraint.
#  @param trafoType The type of transformation associated to the value (translation or rotation).
#  @param trafoNo The number of the transformation which correspond to an axis.
def dstmethod(name, portname, value, description, constraintMin, constraintMax, trafoType, trafoNo):
	global TUIdict
	initDict(name, portname, description, constraintMin, constraintMax, trafoType, trafoNo)

	TUIdict[name][portname]['Value'] = float(value) # We update the value of the corresponding port in the dictionary we use for the UDP connection.

	if description != "":
		PortName = portname
		#tuiclient.sendEvent(name, PortName, value)

	sleep(0.01)

##
#  Initialize the dictionary if it is not already done.
#  @param name The TUIObject's name.
#  @param portname The port's name.
#  @param value The value of the port.
#  @param description The description of the port (node name for the 3D scene).
#  @param constraintMin The value of the minimum constraint.
#  @param constraintMax The value of the maximum constraint.
#  @param trafoType The type of transformation associated to the value (translation or rotation).
#  @param trafoNo The number of the transformation which correspond to an axis.
def initDict(name, portname, description, constraintMin, constraintMax, trafoType, trafoNo):
	global JSONdict
	Port = dict()
	values = dict()

	if (name in JSONdict):
		Port = JSONdict[name]
		if (portname in JSONdict[name]):
			return
		
	values['ConstraintMax'] = constraintMax
	values['ConstraintMin'] = constraintMin
	values['TrafoType'] = trafoType
	values['TrafoNo'] = trafoNo
	values['Description'] = description
	values['Value'] = 0.0

	Port[portname] = values

	JSONdict[name] = Port

	# The JSON file is created and filled only in the beginning of the programm, it contains all the informations.
	try:
		with open('JSONdict.json', 'w') as outfile:
			json.dump(JSONdict, outfile, ensure_ascii=False, indent=4, separators=(',', ': '))
		print("TUI_Instance: " + name + ", port: " + portname + " added to JSON")
	except:
		print("JSON file occupied")

	initJSON()
	return

##
#  Initialize the dictionary useful for the UDP connection.
def initJSON():
	global JSONdict
	global TUIdict

	Port = dict()
	values = dict()

	for name in JSONdict.keys():
		for portName in JSONdict[name].keys():
			values['Value'] = JSONdict[name][portName]['Value']
			Port[portName] = values
			values = dict()

		TUIdict[name] = Port
		Port = dict()

##
#  UDP server.
#  @param tmp Temporary parameter.
def recv(tmp):
	global TUIdict
	UDP_IP = "127.0.0.1"
	UDP_PORT = 5005

	sock = socket.socket(socket.AF_INET, # Internet
						 socket.SOCK_DGRAM) # UDP
	print("UDP CONNECTION SUCCEEDED")

	while True:
		tuidict = json.dumps(TUIdict)
		sock.sendto(tuidict.encode('utf-8'), (UDP_IP, UDP_PORT))


tuiclient.init()
print('INITIALISATION FINISHED')

input()
th1 = _thread.start_new_thread(recv,("tmp",))

tuiclient.connectServer(8996, 8997, '127.0.0.1:7999', 1, systemMsgSink)
