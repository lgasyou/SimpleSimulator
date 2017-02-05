#include "basebuilding.h"
#include "valuegenerator.h"
#include "gameconstants.h"

BaseBuilding::BaseBuilding(const QString &name, const QString &type, Company *owner, double deltaValue) :
	name_(name),
	type_(type),
	owner_(owner),
	deltaValue_(deltaValue)
{
	initBasicValue();
}

void BaseBuilding::copyInit(const BaseBuilding &rhs) {
	name_ = rhs.name();
	value_ = rhs.value();
	owner_ = rhs.owner();
	deltaValue_ = rhs.deltaValue();
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

void BaseBuilding::update() { 
	changeBaseValue();
}

void BaseBuilding::changeBaseValue() {
	double sigma = value_ * 0.1 / 3;
	double deltaValue = ValueGenerator::instance().normalDistribution(0, sigma);
	double finalValue = deltaValue + value_;
	this->deltaValue_ = deltaValue;
	this->value_ = finalValue;
}
