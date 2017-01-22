#include "BaseBuilding.h"

BaseBuilding::BaseBuilding(double value) :
    BaseBuilding("Hello", value, "Foundation", nullptr)
{ }

BaseBuilding::BaseBuilding(const QString &name, double value, const QString &type, Company *owner, double deltaValue) :
    name_(name),
    value_(value),
    type_(type),
    owner_(owner),
    deltaValue_(deltaValue)
{ }

BaseBuilding::BaseBuilding(const BaseBuilding &rhs) :
    BaseBuilding(rhs.name(), rhs.value(), "Foundation", rhs.owner(), rhs.deltaValue())
{ }

void BaseBuilding::manage(const QString &cmd) {

}

void BaseBuilding::update() { }
