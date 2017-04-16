/*
 *	Copyright 2017 Li Zeqing
 *
 *	This file is part of World Simulator.
 *	
 *	World Simulator is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *	
 *	World Simulator is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "basebuilding.h"

#include "valuegenerator.h"
#include "gameconstants.h"

#include <QString>

BaseBuilding::BaseBuilding(const QString &name, const QString &type) :
	name_(name),
	type_(type) {
	initBasicValue();
}

BaseBuilding::~BaseBuilding() { }

void BaseBuilding::copyFrom(const BaseBuilding &rhs) {
	deltaValue_ = rhs.deltaValue();
	name_ = rhs.name();
	owner_ = rhs.owner();
	position_ = rhs.position();
	resource_ = rhs.resource();
	value_ = rhs.value();
}

void BaseBuilding::changeBaseValue() {
	double sigma = value_ * 0.1 / 3;
	double deltaValue = ValueGenerator::instance().normalDistribution(0, sigma);
	double finalValue = deltaValue + value_;
	this->deltaValue_ = deltaValue;
	this->value_ = finalValue;
}

void BaseBuilding::initBasicValue() {
	const double basicValue = GameConstants::defaultBaseValueOfBuilding;
	const double sigma = GameConstants::sigmaOfdefaultBaseValueOfBuilding;
	double value = 0.0;
	do {
		value = ValueGenerator::instance().normalDistribution(basicValue, sigma);
	} while (value <= GameConstants::minBaseValueOfBuilding);
	this->value_ = value;
}
