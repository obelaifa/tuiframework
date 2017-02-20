/*
    Copyright (C) 2010, 2011, 2012 The Fraunhofer Institute for Production Systems and
    Design Technology IPK. All rights reserved.

    This file is part of the TUIFramework library.
    It includes a software framework which contains common code
    providing generic functionality for developing applications
    with a tangible user interface (TUI).
    
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




#include <tuiframework/core/TypeRegistration.h>

#include "CommonTypeReg.h"

using namespace tuiframework;

namespace CommonTypeReg {

/*
* Register the Types used in TUI-Framework. 
* If defining a new Type its importan to set an unique "ChannelName". 
* The "ChannelName" is used by the XML-ServerConfiguration to define the Datatypes being used by the TUI-Server.
*/
void registerTypes(IEventFactory * eventFactory, IEventChannelFactory * eventChannelFactory) {
    tuiframework::registerType<bool, 11>(eventFactory, eventChannelFactory, "DigitalChannel");
    tuiframework::registerType<float, 12>(eventFactory, eventChannelFactory, "AnalogChannel");
    tuiframework::registerType<int, 13>(eventFactory, eventChannelFactory, "IntegerChannel");
    tuiframework::registerType<TrackerData, 14>(eventFactory, eventChannelFactory, "TrackerChannel");
    tuiframework::registerType<Matrix4Data, 15>(eventFactory, eventChannelFactory, "Matrix4Channel");
    tuiframework::registerType<HapticAngle, 16>(eventFactory, eventChannelFactory, "HapticChannel");
    
    tuiframework::registerType<Gesture, 18>(eventFactory, eventChannelFactory, "GestureChannel");
    tuiframework::registerType<KinectJoint, 19>(eventFactory, eventChannelFactory, "KinectChannel");
    tuiframework::registerType<Vector3d, 20>(eventFactory, eventChannelFactory, "Vector3dChannel");
    tuiframework::registerType<MouseData, 21>(eventFactory, eventChannelFactory, "MouseChannel");
    tuiframework::registerType<VectorList3d, 22>(eventFactory, eventChannelFactory, "VectorList3dChannel");
    
    tuiframework::registerType<Vector4<double>, 23>(eventFactory, eventChannelFactory, "Vector4");
    tuiframework::registerType<PackedType<Vector4<double> >, 24>(eventFactory, eventChannelFactory, "PackedVector4");
    tuiframework::registerType<Matrix4<double>, 25>(eventFactory, eventChannelFactory, "Matrix4");
    tuiframework::registerType<PackedType<Matrix4<double> >, 26>(eventFactory, eventChannelFactory, "PackedMatrix4");

	// Not completly tested yet
	/*
	tuiframework::registerType<VectorList<unsigned char>, 27>(eventFactory, eventChannelFactory, "ByteChannel");
	tuiframework::registerType<VectorList<unsigned short>, 28>(eventFactory,eventChannelFactory, "WordVectorChannel");
	tuiframework::registerType<VectorList<unsigned long>, 29>(eventFactory,eventChannelFactory, "DWordVectorChannel");
	tuiframework::registerType<VectorList<float>, 30>(eventFactory,eventChannelFactory, "AnalogVectorChannel");
	tuiframework::registerType<VectorList<int>, 31>(eventFactory,eventChannelFactory, "IntegerVectorChannel");
	*/

	tuiframework::registerType<XControllerData, 32>(eventFactory,eventChannelFactory, "XControllerChannel");
	tuiframework::registerType<WinModData,33>(eventFactory,eventChannelFactory,"WinModChannel");

	// OPC
	/*
	tuiframework::registerType<OPCType<bool>, 34>(eventFactory, eventChannelFactory, "DigitalOPCChannel");
	tuiframework::registerType<OPCType<float>, 35>(eventFactory, eventChannelFactory, "AnalogOPCChannel");
	tuiframework::registerType<OPCType<int>, 36>(eventFactory, eventChannelFactory,  "IntegerOPCChannel");
	tuiframework::registerType<OPCType<string>, 37>(eventFactory, eventChannelFactory, "StringOPCChannel");

	// SceneGraph
	tuiframework::registerType<SceneObject, 38>(eventFactory, eventChannelFactory, "SceneChannel");
	*/

	// PackedTypes
	tuiframework::registerType<PackedType<float >, 101>(eventFactory, eventChannelFactory, "PackedAnalog");
	tuiframework::registerType<PackedType<int >, 102>(eventFactory, eventChannelFactory, "PackedInteger");
	tuiframework::registerType<PackedType<WORD >, 103>(eventFactory, eventChannelFactory, "PackedWORD");
	tuiframework::registerType<PackedType<DWORD >, 104>(eventFactory, eventChannelFactory, "PackedDWORD");

	tuiframework::registerType<WORD, 105>(eventFactory, eventChannelFactory, "WordChannel");
	tuiframework::registerType<DWORD, 106>(eventFactory, eventChannelFactory, "DWordChannel");


}

}
