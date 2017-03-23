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

#ifndef _CommonTypeReg_h_
#define _CommonTypeReg_h_

/**
* Define the Event- and Datatypes used in TUI-Framework.
* The Datatypes can be primitiv Datatypes like int,bool or char
* or even Class-Structures like Vector or Matrix. Every new Class-Structure needs to be included here.
*/

#ifdef _WIN32
#include "XControllerData.h"
#endif

#include "Gesture.h"
#include "HapticAngle.h"
#include "KinectJoint.h"
#include "Matrix4Data.h"

#include "TrackerData.h"
#include "VectorList3d.h"
#include "Vector3d.h"
#include "MouseData.h"

//#include "VectorList.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "PackedType.h"
#ifdef _WIN32
#include "WinModData.h"
#endif
//#include "OPCType.h"
//#include "SceneObject.h"

//#include "TUIPair.h"

#include "Text.h"
#include "TextVector.h"


#include <tuiframework/core/EPEventMsg.h>
#include <tuiframework/core/IEventFactory.h>
#include <tuiframework/core/IEventChannelFactory.h>

#include <string>

/** \brief Defines an alias representing boolean-Values as Event */
typedef tuiframework::EPEventMsg<bool, 11>                  DigitalChangedEvent;

/** \brief Defines an alias representing float-Values as Event */
typedef tuiframework::EPEventMsg<float, 12>                 AnalogChangedEvent;
/** \brief Defines an alias representing integer-Values as Event. */
typedef tuiframework::EPEventMsg<int, 13>                   IntegerChangedEvent;
/** \brief Defines an alias representing the tracker changed event. */
typedef tuiframework::EPEventMsg<TrackerData, 14>           TrackerChangedEvent;
/** \brief Defines an alias representing the matrix 4 changed event. */
typedef tuiframework::EPEventMsg<Matrix4Data, 15>           Matrix4ChangedEvent;
/** \brief Defines an alias representing the haptic changed event. */
typedef tuiframework::EPEventMsg<HapticAngle, 16>           HapticChangedEvent;

/** \brief Defines an alias representing the kinect event. */
typedef tuiframework::EPEventMsg<KinectJoint, 18>           KinectEvent;
/** \brief Defines an alias representing the gesture event. */
typedef tuiframework::EPEventMsg<Gesture, 19>               GestureEvent;
/** \brief Defines an alias representing the vector 3D event. */
typedef tuiframework::EPEventMsg<Vector3d, 20>              Vector3dEvent;
/** \brief Defines an alias representing the mouse event. */
typedef tuiframework::EPEventMsg<MouseData, 21>             MouseEvent;
/** \brief Defines an alias representing a a list of 3dimensional Vectors as event. */
typedef tuiframework::EPEventMsg<VectorList3d, 22>          VectorList3dEvent;

/** \brief Defines an alias representing a 4dimensional Vector as event */
typedef tuiframework::EPEventMsg<Vector4<double>, 23>                   Vector4Event;
/** \brief Defines an alias representing a packed  4dimensional vector as event. */
typedef tuiframework::EPEventMsg<PackedType<Vector4<double> >, 24>      PackedVector4Event;
/** \brief Defines an alias representing a  4x4 matrix as event. */
typedef tuiframework::EPEventMsg<Matrix4<double>, 25>                   Matrix4Event;
/** \brief Defines an alias representing a packed 4x4 matrix as event. */
typedef tuiframework::EPEventMsg<PackedType<Matrix4<double> >, 26>      PackedMatrix4Event;


/** \brief Defines an alias representing a vectorList of byte-Values as event. */
//typedef tuiframework::EPEventMsg<VectorList<unsigned char>,27>					ByteChangedEvent;
/** \brief Defines an alias representing a vectorLis of Word-Values as event. */
//typedef tuiframework::EPEventMsg<VectorList<WORD>,28>					WordVectorChangedEvent;
/** \brief Defines an alias representing a vectorList of Dword-Values as event. */
//typedef tuiframework::EPEventMsg<VectorList<DWORD>,29>					DWordVectorChangedEvent;
/** \brief Defines an alias representing a vectorList of float-Values as event. */
//typedef tuiframework::EPEventMsg<VectorList<float>,30>					AnalogVectorChangedEvent;
/** \brief Defines an alias representing a vectorList of integer-Values as event. */
//typedef tuiframework::EPEventMsg<VectorList<int>,31>					IntegerVectorChangedEvent;

/** \brief Defines an alias representing a XInput-controller event. */
#ifdef _WIN32
typedef tuiframework::EPEventMsg<XControllerData,32>					XControllerEvent;
/** \brief Defines an alias representing a WinMod event. */
typedef tuiframework::EPEventMsg<WinModData,33>							WinModEvent;
#endif
/** \brief Defines an alias representing OPC-boolean-Values as Event */
//typedef tuiframework::EPEventMsg<OPCType<bool>, 34>	DigitalChangedOPCEvent;
/** \brief Defines an alias representing OPC-boolean-Values as Event */
//typedef tuiframework::EPEventMsg<OPCType<float>, 35>	AnalogChangedOPCEvent;
/** \brief Defines an alias representing OPC-boolean-Values as Event */
//typedef tuiframework::EPEventMsg<OPCType<int>, 36>	IntegerChangedOPCEvent;
/** \brief Defines an alias representing OPC-boolean-Values as Event */
//typedef tuiframework::EPEventMsg<OPCType<string>, 37>	StringChangedOPCEvent;

/** \brief Defines an alias representing SceneObject */
//typedef tuiframework::EPEventMsg<SceneObject, 38 > SceneObjectEvent;

typedef tuiframework::EPEventMsg<PackedType<float>, 100> PackedAnalogEvent;
typedef tuiframework::EPEventMsg<PackedType<int>, 101> PackedIntegerEvent;

#ifdef _WIN32
typedef tuiframework::EPEventMsg<PackedType<WORD>, 102> PackedWORDEvent;
typedef tuiframework::EPEventMsg<PackedType<DWORD>, 103> PackedDWORDEvent;
#endif

#ifdef _WIN32
/** \brief Defines an alias representing a vectorLis of Word-Values as event. */
typedef tuiframework::EPEventMsg<WORD, 104>					WordChangedEvent;
/** \brief Defines an alias representing a vectorList of Dword-Values as event. */
typedef tuiframework::EPEventMsg<DWORD, 105>					DWordChangedEvent;
#endif

typedef tuiframework::EPEventMsg<Text, 110>           TextChangedEvent;
typedef tuiframework::EPEventMsg<TextVector, 111>     TextVectorChangedEvent;

namespace CommonTypeReg {

/**
 * \brief Registers the types.
 *
 * \author Sebastian Keppler
 * \date 04.02.2016
 *
 * \param [in,out] eventFactory		   If non-null, the event factory.
 * \param [in,out] eventChannelFactory If non-null, the event channel factory.
 */

void registerTypes(tuiframework::IEventFactory * eventFactory, tuiframework::IEventChannelFactory * eventChannelFactory);    

}

#endif
