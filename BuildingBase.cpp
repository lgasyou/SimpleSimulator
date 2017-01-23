#include "BuildingBase.h"

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

void BuildingBase::update() { }
