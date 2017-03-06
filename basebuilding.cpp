#include "basebuilding.h"

#include "valuegenerator.h"
#include "gameconstants.h"

#include <QString>

BaseBuilding::BaseBuilding(const QString &name, const QString &type) :
	deltaValue_(0.0),
	name_(name),
	owner_(nullptr),
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
