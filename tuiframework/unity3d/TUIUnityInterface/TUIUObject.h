#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <fstream>

/**
* Integer Callback
* @param value Ganzzahl-Werte die an die TUI überwegeben werden sollen.
*/
typedef void(*integerCallback)(int value); // Callback for Integer Values

/**
* Float Callback
* @param value Gleitkomma-Werte die an die TUI überwegeben werden sollen.
*/
typedef void(*floatCallback)(const char* TUIObjectName, const char* portName, const char* description, float value, const char* trafoType, const char* trafoNo); // Callback for float Values

/**
* Boolean Callback
* @param value Boolean-Werte die an die TUI überwegeben werden sollen.
*/
typedef void(*boolCallback)(const char* TUIObjectName, const char* portName, const char* description, bool value); // Callback for boolean Values

/**
* Struktur zum Zusammenfassen der Parameter zum Verbinden mit dem TUI-Channel
*/
struct TUIUObject
{
	std::string objectName;
	std::string portName;
	std::string description;
	int tuiType;
	int entityID;
	int portAdress;
	integerCallback intCall;
	floatCallback floatCall;
	boolCallback boolCall;

	std::string constraintMin;
	std::string constraintMax;
	std::string trafoType;
	std::string trafoNo;

	TUIUObject();
	~TUIUObject();

	TUIUObject(std::string objectName, std::string portName, std::string description, int tuiType, int entityID, int portAdress, floatCallback floatCall);
	TUIUObject(std::string objectName, std::string portName, std::string description, int tuiType, int entityID, int portAdress, integerCallback intCall);
	TUIUObject(std::string objectName, std::string portName, std::string description, int tuiType, int entityID, int portAdress, boolCallback boolCall);

	void metaData(std::string constraintMin, std::string constraintMax, std::string trafoType, std::string trafoNo);
};