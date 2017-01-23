#include "BuildingBase.h"
#include "ValueGenerator.h"

BuildingBase::BuildingBase(double value) :
    BuildingBase("Hello", value, "Foundation", nullptr)
{ }

BuildingBase::BuildingBase(const QString &name, double value, const QString &type, Company *owner, double deltaValue) :
    name_(name),
    value_(value),
    type_(type),
    owner_(owner),
    deltaValue_(deltaValue)
{ }

BuildingBase::BuildingBase(const BuildingBase &rhs) :
    BuildingBase(rhs.name(), rhs.value(), "Foundation", rhs.owner(), rhs.deltaValue())
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
	setDeltaValue(deltaValue);
	setValue(finalValue);
}
