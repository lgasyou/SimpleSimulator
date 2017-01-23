#include "BuildingBase.h"
#include "ValueGenerator.h"
#include "GameConstant.h"

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

void BuildingBase::manage(const QString &cmd) {

}

void BuildingBase::update() { 
	changeBaseValue();
}

void BuildingBase::changeBaseValue() {
	double sigma = value_ * 0.1 / 3;
	double deltaValue = ValueGenerator::normalDistribution(0, sigma);
	double finalValue = deltaValue + value_;
	this->deltaValue_ = deltaValue;
	this->value_ = finalValue;
}

void BuildingBase::initBasicValue() {
	double basicValue = GameConstant::basicValueOfBuildings,
		sigma = GameConstant::sigmaOfBasicValueOfBuildings;
	double value = ValueGenerator::normalDistribution(basicValue, sigma);
	this->value_ = value;
}
