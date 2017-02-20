/*
    Copyright (C) 2010, 2011, 2012 The Fraunhofer Institute for Production Systems and
    Design Technology IPK. All rights reserved.

    This file is part of the TUIFramework library.
    It includes a software framework which contains common code
    providing generic functionality for developing applications
    with a tangible user interface (TUI).
    designed for creating applications with a tangible user interface (TUI).
    
    The TUIFramework library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    The TUIFramework is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with the TUIFramework.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "SceneGraph.h"

using namespace tuiframework;
using namespace std;

SceneGraph::SceneGraph()
{
}


SceneGraph::~SceneGraph() 
{

}

/**
*	Connecting all ports automaticly depending on the defintions inside the TUI-Config
*/
void SceneGraph::connect() 
{
	objectInstances = getAttachedObjects().getTUIObjectInstanceVector();
	objectTypes = getAttachedObjects().getTUIObjectTypeVector();
	
	
	// Debug Comment
	cout << "############ Type Size"<< objectTypes.size() << endl;
	cout << "############ Instance Size" << objectInstances.size() << endl;

	// Iterate the instances
	for (vector<TUIObjectInstance>::iterator it = objectInstances.begin(); it != objectInstances.end(); it++)
	{	// Iterate the types to get the Channelnames
		// Debug Comment
		cout <<"Instances ID: " <<it->getID() << "Type: "<< it->getTypeName() <<  endl ;

		for (map<string, int>::iterator typeMapIt = it->getNameChannelNrMap().begin(); typeMapIt != it->getNameChannelNrMap().end(); typeMapIt++)
		{
			//cout << typeMapIt->first << "=>" << typeMapIt->second << endl;
		}
		for (vector<TUIObjectType>::iterator typeIt = objectTypes.begin(); typeIt != objectTypes.end(); typeIt++)
		{
			// Just for Debug
			for (map<string, tuiframework::Port>::iterator typeMapIt2 = typeIt->getPortMap().begin(); typeMapIt2 != typeIt->getPortMap().end(); typeMapIt2++)
			{
				cout << "name: " << typeMapIt2->second.getName() << " Description: "<< typeMapIt2->second.getDescription() << endl;
			}

			// Debug
			//cout << "Typename: " << typeIt->getName() << endl;

			// Check if Instance-Typename is the same like the used Type
			if (typeIt->getName() == it->getTypeName())
			{	// Iterate through the PortMap
				for (map<string, tuiframework::Port>::iterator typeMapIt = typeIt->getPortMap().begin(); typeMapIt != typeIt->getPortMap().end(); typeMapIt++)
				{	// Connect the Ports with a function
					// Check if the Value is Analog(Float) or Digital(Boolean)
					if (typeMapIt->second.getTypeName() == "AnalogChannel" && typeMapIt->second.getDataFlowDirection() == 1)
					{
						try
						{	// Like this, all Ports of the same type are only connectable with one Function, how do we get the Portname too?
							CONNECT(AnalogChangedEvent, it->getName(), typeMapIt->first, SceneGraph, this, &SceneGraph::analogValueChanged);
							// Just for Debug
							cout << "Connected " << typeMapIt->first << " of " << it->getName() << " from type " << typeMapIt->second.getTypeName() << endl;

						}
						catch (const Exception & e) 
						{
							cerr << "Exception" << endl;
							cerr << e.getFormattedString() << endl;
						}
					}
					else if (typeMapIt->second.getTypeName() == "DigitalChannel" && typeMapIt->second.getDataFlowDirection() == 1)
					{
						try
						{
							CONNECT(DigitalChangedEvent, it->getName(), typeMapIt->first, SceneGraph, this, &SceneGraph::digitalValueChanged);
							// Just for Debug
							cout << "Connected " << typeMapIt->first << " of " << it->getName() << " from type " << typeMapIt->second.getTypeName() << endl;

						}
						catch (const Exception & e) 
						{
							cerr << "Exception" << endl;
							cerr << e.getFormattedString() << endl;
						}
					}
				}
			}
		}

	}
       
}

/**
*	Not working yet
*/
void SceneGraph::disconnect() {
    try {
      //  DISCONNECT(SceneObjectEvent, "VREDSceneGraph", "objectIn",
		//	SceneGraph, this, &SceneGraph::sceneObjectChanged);
    } catch (const Exception & e) {
        cerr << "Exception" << endl;
        cerr << e.getFormattedString() << endl;
    }
}

void SceneGraph::analogValueChanged(const AnalogChangedEvent * e)
{
	AnalogChangedEvent* event = (AnalogChangedEvent*)e;
	
	int instanceId = e->getAddress().getEntityID()-1;
	int portId = e->getAddress().getPortNr();
	int typeId = e->getAddress().getAddressTypeID()-1;
	string functionGroupName = objectInstances.at(instanceId).getName();
	string portName = "";
	string description = "";
	float payload = e->getPayload();

	for (std::map<string, int>::iterator it = objectInstances.at(instanceId).getNameChannelNrMap().begin(); it != objectInstances.at(instanceId).getNameChannelNrMap().end(); ++it)
	{
		if (it->second == portId)
		{
			portName = it->first;
			break;
		}
	}

	description = objectTypes.at(typeId).getPortMap().at(portName).getDescription();
	

	/* If we use a console-output Memory-usage increase continuous*/
	//cout << "Analog Event: FunctionGroup=>" << functionGroupName 
	//	<< " Value=> " << payload << " at Port=> " << portName << " Description=> "<< description <<  endl;
	delete event;
	event = NULL;

}

void SceneGraph::digitalValueChanged(const DigitalChangedEvent * e)
{
	
	int instanceId = e->getAddress().getEntityID() - 1;
	int portId = e->getAddress().getPortNr();
	int typeId = e->getAddress().getAddressTypeID() - 1;
	string functionGroupName = objectInstances.at(instanceId).getName();
	string portName = "";
	string description = "";
	bool payload = e->getPayload();


	for (std::map<string, int>::iterator it = objectInstances.at(instanceId).getNameChannelNrMap().begin(); it != objectInstances.at(instanceId).getNameChannelNrMap().end(); ++it)
	{
		if (it->second == portId)
		{
			portName = it->first;
			break;
		}
	}
	
	description = objectTypes.at(typeId).getPortMap().at(portName).getDescription();
	
	/* If we use a console-output Memory-usage increase continuous*/
	//cout << typeId << endl;
	/*cout << "Digital Event: FunctionGroup=>" << functionGroupName
		<< " Value=> " << payload << " at Port=> " << portName << " Description=> " << description << endl;
	*/
	delete e;
	e = NULL;
}
