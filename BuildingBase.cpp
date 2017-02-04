#include "buildingbase.h"
#include "ValueGenerator.h"
#include "GameConstants.h"

BuildingBase::BuildingBase(const QString &name, const QString &type, Company *owner, double deltaValue) :
	name_(name),
	type_(type),
	owner_(owner),
	deltaValue_(deltaValue)
{
	initBasicValue();
}

BuildingBase::BuildingBase(const BuildingBase &rhs, const QString &type) :
	name_(rhs.name()),
	value_(rhs.value()),
	type_(type),
	owner_(rhs.owner()),
	deltaValue_(rhs.deltaValue())
{ }

void BuildingBase::initBasicValue() {
	const double basicValue = GameConstants::defaultBaseValueOfBuilding;
	const double sigma = GameConstants::sigmaOfdefaultBaseValueOfBuilding;
	double value = 0.0;
	do {
		value = ValueGenerator::instance().normalDistribution(basicValue, sigma);
	} while (value <= GameConstants::minBaseValueOfBuilding);
	this->value_ = value;
}

void BuildingBase::manage(const QString &cmd) {

}

void BuildingBase::update() { 
	changeBaseValue();
}

void BuildingBase::changeBaseValue() {
	double sigma = value_ * 0.1 / 3;
	double deltaValue = ValueGenerator::instance().normalDistribution(0, sigma);
	double finalValue = deltaValue + value_;
	this->deltaValue_ = deltaValue;
	this->value_ = finalValue;
}
