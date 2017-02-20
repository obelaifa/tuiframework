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


#include "Port.h"

#include <iostream>
#include <ios>
namespace tuiframework {


Port::Port()
	:name(""), typeName(""), description(""), dataFlowDirection(-1), constraintMin(""), constraintMax(""), trafotype("")
{

}

Port::Port(const std::string & name, const std::string & typeName, DataFlowDirection dataFlowDirection, 
	const std::string & description, const std::string & constraintMin, const std::string & constraintMax, const std::string & trafotype)
	:name(name), typeName(typeName), description(description), dataFlowDirection(dataFlowDirection), constraintMin(constraintMin), constraintMax(constraintMax), trafotype(trafotype)
{

}


Port::~Port() {
}


const std::string & Port::getName() const {
    return this->name;
}


void Port::setName(const std::string & name) {
    this->name = name;
}


const std::string & Port::getDescription() const {
    return this->description;
}


void Port::setDescription(const std::string & description) {
    this->description = description;
}


const std::string & Port::getTypeName() const {
    return this->typeName;
}


void Port::setTypeName(const std::string & typeName) {
    this->typeName = typeName;
}

const std::string & Port::getConstraintMin() const {
	return this->constraintMin;
}

void Port::setConstraintMin(const std::string & constraintMin) {
	this->constraintMin = constraintMin;
}

const std::string & Port::getConstraintMax() const {
	return this->constraintMax;
}

void Port::setConstraintMax(const std::string & constraintMax) {
	this->constraintMax = constraintMax;
}

const std::string & Port::getTransfoType() const {
	return this->trafotype;
}

void Port::setTransfoType(const std::string & trafoType) {
	this->trafotype = trafoType;
}

Port::DataFlowDirection Port::getDataFlowDirection() const {
    return static_cast<Port::DataFlowDirection>(this->dataFlowDirection);
}


void Port::setDataFlowDirection(Port::DataFlowDirection dataFlowDirection) {
    this->dataFlowDirection = static_cast<int>(dataFlowDirection);
}


std::ostream & Port::serialize(std::ostream & os) const 
{
	std::cout << description << std::endl;
	os << this->name << " " << this->typeName << " " << this->description << " ";

    os << this->dataFlowDirection ;
	os << " " << this->constraintMin << " " << this->constraintMax << " " << this->trafotype;
    return os;
}


std::istream & Port::deSerialize(std::istream & is) {
	std::cout << description << std::endl;
	is >> this->name >> this->typeName >> this->description;

    is >> this->dataFlowDirection;
	is >> this->constraintMin >> this->constraintMax >> this->trafotype;
    return is;
}


} // namespace tuiframework




