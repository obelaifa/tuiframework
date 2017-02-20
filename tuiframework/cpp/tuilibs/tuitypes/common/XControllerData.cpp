#include "XControllerData.h"

#include <iostream>

XControllerData::XControllerData() :
	id(-1),
	lThumbdeltaX(0),
	lThumbdeltaY(0),

	rThumbdeltaX(0),
	rThumbdeltaY(0),

	lShoulderdeltaZ(0),
	rShoulderdeltaZ(0),
	buttonCode(0)  {
	
}


XControllerData::XControllerData(int id) :
	id(id),
	lThumbdeltaX(0),
	lThumbdeltaY(0),

	rThumbdeltaX(0),
	rThumbdeltaY(0),

	lShoulderdeltaZ(0),
	rShoulderdeltaZ(0),

	buttonCode(0) {

}


XControllerData::~XControllerData() {
}


void XControllerData::setId(int id) {
	this->id = id;
}


void XControllerData::setLThumbDeltaX(int deltaX) {
	//this->lThumbdeltaX = deltaX;

	_controllerState.Gamepad.sThumbLX = deltaX;
}


void XControllerData::setLThumbDeltaY(int deltaY) {
	//this->lThumbdeltaY = deltaY;
	_controllerState.Gamepad.sThumbLY = deltaY;
}

void XControllerData::setRThumbDeltaX(int deltaX) {
	this->rThumbdeltaX = deltaX;
	_controllerState.Gamepad.sThumbRX = deltaX;
}


void XControllerData::setRThumbDeltaY(int deltaY) {
	//this->rThumbdeltaY = deltaY;
	_controllerState.Gamepad.sThumbRY = deltaY;
}

void XControllerData::setLShoulderDeltaZ(int deltaZ) {
	this->lShoulderdeltaZ = deltaZ;
}


void XControllerData::setRShoulderDeltaZ(int deltaZ) {
	this->rShoulderdeltaZ = deltaZ;
}




void XControllerData::setButtonCode(unsigned int buttonCode) {
	this->buttonCode = buttonCode;
}


int XControllerData::getId() const {
	return this->id;
}


int XControllerData::getLThumbDeltaX() const {
	return _controllerState.Gamepad.sThumbLX;
}


int XControllerData::getLThumbDeltaY() const {
	return _controllerState.Gamepad.sThumbLY;
}

int XControllerData::getRThumbDeltaX() const {
	return _controllerState.Gamepad.sThumbRX;
}


int XControllerData::getRThumbDeltaY() const {
	return _controllerState.Gamepad.sThumbRY;
}

int XControllerData::getLShoulderDeltaZ() const {
	return _controllerState.Gamepad.bLeftTrigger;
}


int XControllerData::getRShoulderDeltaZ() const {
	return _controllerState.Gamepad.bRightTrigger;
}


bool XControllerData::getButtonStateChange(GamePadButton code) const {

	return _controllerState.Gamepad.wButtons & static_cast<unsigned int>(code) ? true : false;
}


bool XControllerData::hasChanged() const {

	return _controllerState.Gamepad.sThumbLX != 0 ||_controllerState.Gamepad.sThumbLY != 0 || _controllerState.Gamepad.sThumbRX != 0 || _controllerState.Gamepad.sThumbRY != 0 || 
		_controllerState.Gamepad.bLeftTrigger != 0 || _controllerState.Gamepad.bRightTrigger !=0  || 	_controllerState.Gamepad.wButtons != 0;
	
}


std::ostream & XControllerData::serialize(std::ostream & os) const {
	
	os  << " " << this->id << " " << _controllerState.Gamepad.sThumbLX << " " << _controllerState.Gamepad.sThumbLY << " " << _controllerState.Gamepad.sThumbRX << " "  << _controllerState.Gamepad.sThumbRY << " " <<
		_controllerState.Gamepad.bLeftTrigger <<	" " << _controllerState.Gamepad.bRightTrigger <<" " << _controllerState.Gamepad.wButtons;
	
	return os;
	
}


std::istream & XControllerData::deSerialize(std::istream & is) {
	
	int version;
	is >> version;
	is >> this->id >> _controllerState.Gamepad.sThumbLX >> _controllerState.Gamepad.sThumbLY >> _controllerState.Gamepad.sThumbRX >> _controllerState.Gamepad.sThumbRY >>
		_controllerState.Gamepad.bLeftTrigger >> _controllerState.Gamepad.bRightTrigger >> _controllerState.Gamepad.wButtons;

	return is;
	
}

bool XControllerData::is_connected()
{
	
     // clean the state
     memset(&_controllerState,0, sizeof(XINPUT_STATE));
 
     // Get the state
     DWORD Result = XInputGetState(0, &_controllerState);
 
     if(Result == 0L)	return true;
     else return false;
	 
	// return true;
}

void XControllerData::Vibrate()
{
    XINPUT_VIBRATION vibration; 

    //Invoke memset to zero out the XINPUT_VIBRATION. 
    memset(&vibration, 0, sizeof(XINPUT_VIBRATION)); 

    /*
       According to MSDN Documentation on this, 
       speed of the left or right motor. Valid values are 
       in the range 0 to 65,535. Zero signifies no motor 
       use; 65,535 signifies 100 percent motor use.
    */

    vibration.wLeftMotorSpeed = (int)(65535.0f); 
    vibration.wRightMotorSpeed = (int)(65535.0f); 

    //Vibrate the controller 
    XInputSetState(0, &vibration); 
}