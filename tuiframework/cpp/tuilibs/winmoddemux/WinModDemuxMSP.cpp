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


#include <TUIPlugins/winmoddemux/WinModDemuxMSP.h>

using namespace std;

static const char * winModDataInTag = "w";
static const char * outLTXTag = "byteOut";
static const char * outLTYTag = "floatOut";
static const char * outRTXTag = "wordOut";
static const char * outRTYTag = "dWordOut";
//static const char * outMatrix1 = "valueMatrix1"; //test

#define OUT_LTX 0 // Left Thumbstick X
#define OUT_LTY 1 // Left ThumbStick Y
#define OUT_RTX 2 // Right ThumbStick X
#define OUT_RTY 3 // Right ThumbStick Y
#define OUT_MATRIX 4 // Right ThumbStick Y
//#define OUT_MATRIX1 5 // test


namespace tuiframework {

IMSP * WinModDemuxMSP::createFunction(void * arg) {
    MSPConfig * config = static_cast<MSPConfig *>(arg);
    return new WinModDemuxMSP(*config);
}

static std::string typeName = "WinModDemuxMSP";

const std::string & WinModDemuxMSP::getMSPTypeName() {
    return typeName;
}


WinModDemuxMSP::WinModDemuxMSP(const MSPConfig & config) :
    config(config) {
    for (int i = 0; i < 5; ++i) {
        this->out[i] = 0;
    }
    this->winModEventDelegate.setReceiver(this, &WinModDemuxMSP::handleWinModEvent);
	this->nameToIdMap[outLTXTag] = OUT_LTX;
    this->nameToIdMap[outLTYTag] = OUT_LTY;
	this->nameToIdMap[outRTXTag] = OUT_RTX;
    this->nameToIdMap[outRTYTag] = OUT_RTY;
	//this->nameToIdMap[outMatrix] = OUT_MATRIX;
}


WinModDemuxMSP::~WinModDemuxMSP() {
}


const std::string & WinModDemuxMSP::getTypeName() const {
    return getMSPTypeName();
}


IEventSink * WinModDemuxMSP::getEventSink(const std::string & name) {
    if (name.compare(winModDataInTag) == 0) {
        return &winModEventDelegate;
    }
    return 0;
}


void WinModDemuxMSP::registerEventSink(const std::string & name, IEventSink * eventSink) {
    map<string, int>::iterator iter = this->nameToIdMap.find(name);
    if (iter == this->nameToIdMap.end()) {
        return;
    }
    this->out[(*iter).second] = eventSink;
}


const MSPType & WinModDemuxMSP::getMSPType() const {
    return this->type;
}

void WinModDemuxMSP::handleWinModEvent(WinModEvent * e) {
    const WinModData & wd = e->getPayload();
	//const WinModData & wd1 = e->getPayload();

	if(this->out[OUT_LTY])
	{
		PackedAnalogEvent* event = new PackedAnalogEvent(-1, -1, wd.getFloatList());
		//AnalogVectorChangedEvent* event2 = new AnalogVectorChangedEvent(-1,-1,wd.getFloats());
		//cout <<"MSPOut: Floats: "  << event2->getPayload().getData()[0] << endl;
		   //for(int i=0;i<wd.getFloats().size();i++)
			 //cout <<"MSPOut: Floats: "  << event2->getPayload().at(i)<< endl;
		
		this->out[OUT_LTY]->push(event);
	}

	if(this->out[OUT_LTX])
	{
		PackedIntegerEvent* event = new PackedIntegerEvent(-1,-1,wd.getByteList());
		//for(int i=0;i<wd.getBytes().size();i++)
			//cout <<"MSPOut: Bytes: "  << event->getPayload().at(i)<< endl;
		this->out[OUT_LTX]->push(event);
	}


	if(this->out[OUT_RTX])
	{
		PackedWORDEvent* event = new PackedWORDEvent(-1,-1,wd.getWordList());
		//for(int i=0;i<wd.getWords().size();i++)
		//	cout <<"MSPOut: Words: "  << event3->getPayload().at(i)<< endl;
		this->out[OUT_RTX]->push(event);
	}

	if(this->out[OUT_RTY])
	{
		PackedDWORDEvent* event = new PackedDWORDEvent(-1,-1,wd.getDWordList());
		//for(int i=0;i<wd.getDWords().size();i++)
		//	cout <<"MSPOut: DWords: "  << event4->getPayload().at(i)<< endl;
		
		this->out[OUT_RTY]->push(event);
	}
}



}