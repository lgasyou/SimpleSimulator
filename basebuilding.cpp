#include "basebuilding.h"

#include "valuegenerator.h"
#include "gameconstants.h"

#include <QString>

BaseBuilding::BaseBuilding(const QString &name, const QString &type) :
	name_(name),
	type_(type),
	deltaValue_(0.0),
	owner_(nullptr)
{
	initBasicValue();
}

void BaseBuilding::copyFrom(const BaseBuilding &rhs) {
	name_ = rhs.name();
	value_ = rhs.value();
	deltaValue_ = rhs.deltaValue();
	owner_ = rhs.owner();
	position_ = rhs.position();
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

void BaseBuilding::changeBaseValue() {
	double sigma = value_ * 0.1 / 3;
	double deltaValue = ValueGenerator::instance().normalDistribution(0, sigma);
	double finalValue = deltaValue + value_;
	this->deltaValue_ = deltaValue;
	this->value_ = finalValue;
}
