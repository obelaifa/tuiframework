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


#include <TUIPlugins/xcontrollerdemux/XControllerDemuxMSP.h>

// Mapping the sink-port names
static const char * xControllerDataInTag = "x";
static const char * outLTXTag = "leftThumb DeltaX";
static const char * outLTYTag = "leftThumb DeltaY";
static const char * outRTXTag = "rightThumb DeltaX";
static const char * outRTYTag = "rightThumb DeltaY";
static const char * outLSZTag = "leftShoulder Delta";
static const char * outRSZTag = "rightShoulder Delta";
static const char * outBtATag = "b1-a";
static const char * outBtBTag = "b2-b";
static const char * outBtXTag = "b3-x";
static const char * outBtYTag = "b4-y";
static const char * outBtSTag = "b5-start";
static const char * outBtBaTag = "b6-back";
static const char * outBtLSTag = "b7-leftShoulder";
static const char * outBtRSTag = "b8-rightShoulder";
static const char * outBtLTTag = "b9-leftThumb";
static const char * outBtRTTag = "b10-rightThumb";
static const char * outBtDUTag = "b11-dPadUp";
static const char * outBtDDTag = "b12-dPadDown";
static const char * outBtDLTag = "b13-dPadLeft";
static const char * outBtDRTag = "b14-dPadRight";

#define OUT_LTX 0 // Left Thumbstick X
#define OUT_LTY 1 // Left ThumbStick Y
#define OUT_RTX 2 // Right ThumbStick X
#define OUT_RTY 3 // Right ThumbStick Y
#define OUT_LSZ 4 // Left Shoulder Z
#define OUT_RSZ 5 // Right Shoulder Z
#define OUT_BTA 6 // A-Button 
#define OUT_BTB 7 // B-button 
#define OUT_BTX 8 // X-Button 
#define OUT_BTY 9 // Y-Button 
#define OUT_BTS 10 // Start-Button 
#define OUT_BTBa 11 // Back-Button 
#define OUT_BTLT 12 // LeftThumb-Button 
#define OUT_BTRT 13 // RightThumb-Button 
#define OUT_BTLS 14 // LeftShoulder-Button 
#define OUT_BTRS 15 // RightShoulder-Button 
#define OUT_BTDU 16 // DPad-Up-Button 
#define OUT_BTDD 17 // DPad-Down-Button 
#define OUT_BTDL 18 //  DPad-Left-Button 
#define OUT_BTDR 19 //  DPad-Right-Button 

using namespace std;

namespace tuiframework {

IMSP * XControllerDemuxMSP::createFunction(void * arg) {
    MSPConfig * config = static_cast<MSPConfig *>(arg);
    return new XControllerDemuxMSP(*config);
}

static std::string typeName = "XControllerDemuxMSP";

const std::string & XControllerDemuxMSP::getMSPTypeName() {
    return typeName;
}


XControllerDemuxMSP::XControllerDemuxMSP(const MSPConfig & config) :
    config(config) {
    for (int i = 0; i < 20; ++i) {
        this->out[i] = 0;
    }
    this->xControllerEventDelegate.setReceiver(this, &XControllerDemuxMSP::handleXControllerEvent);
    this->nameToIdMap[outLTXTag] = OUT_LTX;
    this->nameToIdMap[outLTYTag] = OUT_LTY;
	this->nameToIdMap[outRTXTag] = OUT_RTX;
    this->nameToIdMap[outRTYTag] = OUT_RTY;
	this->nameToIdMap[outLSZTag] = OUT_LSZ;
    this->nameToIdMap[outRSZTag] = OUT_RSZ;
    this->nameToIdMap[outBtATag] = OUT_BTA;
    this->nameToIdMap[outBtBTag] = OUT_BTB;
    this->nameToIdMap[outBtXTag] = OUT_BTX;
    this->nameToIdMap[outBtYTag] = OUT_BTY;
    this->nameToIdMap[outBtSTag] = OUT_BTS;
	this->nameToIdMap[outBtBaTag] = OUT_BTBa;
    this->nameToIdMap[outBtLTTag] = OUT_BTLT;
    this->nameToIdMap[outBtRTTag] = OUT_BTRT;
    this->nameToIdMap[outBtLSTag] = OUT_BTLS;
    this->nameToIdMap[outBtRSTag] = OUT_BTRS;
	this->nameToIdMap[outBtDUTag] = OUT_BTDU;
    this->nameToIdMap[outBtDDTag] = OUT_BTDD;
    this->nameToIdMap[outBtDLTag] = OUT_BTDL;
    this->nameToIdMap[outBtDRTag] = OUT_BTDR;
}


XControllerDemuxMSP::~XControllerDemuxMSP() {
}


const std::string & XControllerDemuxMSP::getTypeName() const {
    return getMSPTypeName();
}


IEventSink * XControllerDemuxMSP::getEventSink(const std::string & name) {
    if (name.compare(xControllerDataInTag) == 0) {
        return &xControllerEventDelegate;
    }
    return 0;
}


void XControllerDemuxMSP::registerEventSink(const std::string & name, IEventSink * eventSink) {
    map<string, int>::iterator iter = this->nameToIdMap.find(name);
    if (iter == this->nameToIdMap.end()) {
        return;
    }
    this->out[(*iter).second] = eventSink;
}


const MSPType & XControllerDemuxMSP::getMSPType() const {
    return this->type;
}

void XControllerDemuxMSP::handleXControllerEvent(XControllerEvent * e) {
    const XControllerData & xd = e->getPayload();

	
	if( (xd.getLThumbDeltaX() < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			xd.getLThumbDeltaX() > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
			(xd.getLThumbDeltaY() < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			xd.getLThumbDeltaY() > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) )
	{    
		//xd.setLThumbDeltaX(0);
		//xd.setLThumbDeltaY(0);;
	}

	// Left Thumbstick X-Y
    if (this->out[OUT_LTX]) 
	{
		if(xd.getLThumbDeltaX() > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||xd.getLThumbDeltaX() < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			if (xd.getLThumbDeltaX()) 
			{
				//cout << "LThumb DeltaX: "<<xd.getLThumbDeltaX() << endl;
				this->out[OUT_LTX]->push(new IntegerChangedEvent(-1, -1, xd.getLThumbDeltaX()));
			}
		}
    }
    if (this->out[OUT_LTY]) 
	{
		if (xd.getLThumbDeltaY() > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || xd.getLThumbDeltaY() < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			if (xd.getLThumbDeltaY())
			{
				//cout << "LThumb DeltaY: "<<xd.getLThumbDeltaY() << endl;
				this->out[OUT_LTY]->push(new IntegerChangedEvent(-1, -1, xd.getLThumbDeltaY()));
			}
		}
    }

	// Right ThumbStick X-Y
	if (this->out[OUT_RTX]) {
		if (xd.getRThumbDeltaX() > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE || xd.getRThumbDeltaX() < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			if (xd.getRThumbDeltaX() && XINPUT_GAMEPAD_RIGHT_THUMB) {
				this->out[OUT_RTX]->push(new IntegerChangedEvent(-1, -1, xd.getRThumbDeltaX()));
			}
		}
    }
    if (this->out[OUT_RTY]) {
		if (xd.getRThumbDeltaY() > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE || xd.getRThumbDeltaY() < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			if (xd.getRThumbDeltaY() && XINPUT_GAMEPAD_RIGHT_THUMB) {
				this->out[OUT_RTY]->push(new IntegerChangedEvent(-1, -1, xd.getRThumbDeltaY()));
			}
		}
    }

	// Left/Right Shoulder Z
	if (this->out[OUT_LSZ]) {
		if (xd.getLShoulderDeltaZ()) {
			//cout << "LShoulder Delta: "<<xd.getLShoulderDeltaZ() << endl;
            this->out[OUT_LSZ]->push(new IntegerChangedEvent(-1, -1, xd.getLShoulderDeltaZ()));
        }
    }
    if (this->out[OUT_RSZ]) {
		if (xd.getRShoulderDeltaZ()) 
		{
			//cout  << "RShoulder Delta: "<< xd.getRShoulderDeltaZ() << endl;
            this->out[OUT_RSZ]->push(new IntegerChangedEvent(-1, -1, xd.getRShoulderDeltaZ()));
        }
    }

	// Buttons
    if (this->out[OUT_BTA]) {
        if (xd.getButtonStateChange(XControllerData::GamePad_Button_A) && XINPUT_GAMEPAD_A) 
		{
            this->out[OUT_BTA]->push(new DigitalChangedEvent(-1, -1, true));
        }
//		else {
//            this->out[OUT_BTA]->push(new DigitalChangedEvent(-1, -1, false));
//        }
    }

    if (this->out[OUT_BTB]) 
	{
        if (xd.getButtonStateChange(XControllerData::GamePad_Button_B)) 
		{
            this->out[OUT_BTB]->push(new DigitalChangedEvent(-1, -1, true));
        }
        //else 
		//{
        //    this->out[OUT_BTB]->push(new DigitalChangedEvent(-1, -1, false));
        //}
    }

    if (this->out[OUT_BTX]) {
        if (xd.getButtonStateChange(XControllerData::GamePad_Button_X)) 
		{
            this->out[OUT_BTX]->push(new DigitalChangedEvent(-1, -1, true));
        }
  //      else 
  //		{
  //          this->out[OUT_BTX]->push(new DigitalChangedEvent(-1, -1, false));
  //      }
    }

    if (this->out[OUT_BTY]) 
	{
        if (xd.getButtonStateChange(XControllerData::GamePad_Button_Y)) 
		{
            this->out[OUT_BTY]->push(new DigitalChangedEvent(-1, -1, true));
        }
		//else 
		//{
  //          this->out[OUT_BTY]->push(new DigitalChangedEvent(-1, -1, false));
  //      }
    }

    if (this->out[OUT_BTS]) 
	{
        if (xd.getButtonStateChange(XControllerData::GamePad_Button_START)) 
		{
            this->out[OUT_BTS]->push(new DigitalChangedEvent(-1, -1, true));
        }
		//else 
		//{
  //          this->out[OUT_BTS]->push(new DigitalChangedEvent(-1, -1, false));
  //      }
    }

	if (this->out[OUT_BTBa]) 
	{
		if (xd.getButtonStateChange(XControllerData::GamePad_Button_BACK)) 
		{
            this->out[OUT_BTBa]->push(new DigitalChangedEvent(-1, -1, true));
        }
		//else 
		//{
  //          this->out[OUT_BTBa]->push(new DigitalChangedEvent(-1, -1, false));
  //      }
    }

	if (this->out[OUT_BTLT]) 
	{
        if (xd.getButtonStateChange(XControllerData::GamePad_Button_LEFT_THUMB)) 
		{
            this->out[OUT_BTLT]->push(new DigitalChangedEvent(-1, -1, true));
        }
		//else 
		//{
  //          this->out[OUT_BTLT]->push(new DigitalChangedEvent(-1, -1, false));
  //      }
    }

	if (this->out[OUT_BTRT]) 
	{
		if (xd.getButtonStateChange(XControllerData::GamePad_Button_RIGHT_THUMB)) 
		{
            this->out[OUT_BTRT]->push(new DigitalChangedEvent(-1, -1, true));
        }
		//else 
		//{
  //          this->out[OUT_BTRT]->push(new DigitalChangedEvent(-1, -1, false));
  //      }
    }

	if (this->out[OUT_BTLS]) 
	{
        if (xd.getButtonStateChange(XControllerData::GamePad_Button_LEFT_SHOULDER)) 
		{
            this->out[OUT_BTLS]->push(new DigitalChangedEvent(-1, -1, true));
        }
		//else 
		//{
  //          this->out[OUT_BTLS]->push(new DigitalChangedEvent(-1, -1, false));
  //      }
    }

	if (this->out[OUT_BTRS]) 
	{
		if (xd.getButtonStateChange(XControllerData::GamePad_Button_RIGHT_SHOULDER)) 
		{
            this->out[OUT_BTRS]->push(new DigitalChangedEvent(-1, -1, true));
        }
		//else 
		//{
  //          this->out[OUT_BTRS]->push(new DigitalChangedEvent(-1, -1, false));
  //      }
    }

	if (this->out[OUT_BTDU]) 
	{
        if (xd.getButtonStateChange(XControllerData::GamePad_Button_DPAD_UP)) 
		{
            this->out[OUT_BTDU]->push(new DigitalChangedEvent(-1, -1, true));
        }
		//else
		//{
  //          this->out[OUT_BTDU]->push(new DigitalChangedEvent(-1, -1, false));
  //      }
    }

	if (this->out[OUT_BTDD]) 
	{
        if (xd.getButtonStateChange(XControllerData::GamePad_Button_DPAD_DOWN)) 
		{
            this->out[OUT_BTDD]->push(new DigitalChangedEvent(-1, -1, true));
        }
		//else
		//{
  //          this->out[OUT_BTDD]->push(new DigitalChangedEvent(-1, -1, false));
  //      }
    }
	if (this->out[OUT_BTDL]) 
	{
        if (xd.getButtonStateChange(XControllerData::GamePad_Button_DPAD_RIGHT)) 
		{
            this->out[OUT_BTDL]->push(new DigitalChangedEvent(-1, -1, true));
        }
		//else
		//{
  //          this->out[OUT_BTDL]->push(new DigitalChangedEvent(-1, -1, false));
  //      }
    }

	if (this->out[OUT_BTDR]) 
	{
        if (xd.getButtonStateChange(XControllerData::GamePad_Button_DPAD_LEFT)) 
		{
            this->out[OUT_BTDR]->push(new DigitalChangedEvent(-1, -1, true));
        }
		//else 
		//{
  //          this->out[OUT_BTDR]->push(new DigitalChangedEvent(-1, -1, false));
  //      }
    }

    delete e;
}



}