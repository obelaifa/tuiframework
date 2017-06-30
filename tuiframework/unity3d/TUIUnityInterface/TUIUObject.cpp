#include "TUIUObject.h"

TUIUObject::TUIUObject()
{
}

TUIUObject::~TUIUObject()
{
}

TUIUObject::TUIUObject(std::string objectName, std::string portName, std::string description, int tuiType, int entityID, int portAdress, floatCallback floatCall)
	:objectName(objectName), portName(portName), description(description), tuiType(tuiType), entityID(entityID), portAdress(portAdress), floatCall(floatCall)
{
}

TUIUObject::TUIUObject(std::string objectName, std::string portName, std::string description, int tuiType, int entityID, int portAdress, integerCallback intCall)
	: objectName(objectName), portName(portName), description(description), tuiType(tuiType), entityID(entityID), portAdress(portAdress), intCall(intCall)
{
}

TUIUObject::TUIUObject(std::string objectName, std::string portName, std::string description, int tuiType, int entityID, int portAdress, boolCallback boolCall)
	: objectName(objectName), portName(portName), description(description), tuiType(tuiType), entityID(entityID), portAdress(portAdress), boolCall(boolCall)
{
}

void TUIUObject::metaData(std::string constraintMin, std::string constraintMax, std::string trafoType, std::string trafoNo)
{
	this->constraintMin = constraintMin;
	this->constraintMax = constraintMax;
	this->trafoType = trafoType;
	this->trafoNo = trafoNo;
}