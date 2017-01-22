#include "Factory.h"
#include "FactoryCargo.h"

Factory::Factory(double value) :
    BaseBuilding("Factory", value, "Factory", nullptr),
    cargo_(new FactoryCargo)
{ }

Factory::Factory(const BaseBuilding &rhs) :
    BaseBuilding(rhs.name(), rhs.value(), "Factory", rhs.owner(), rhs.deltaValue()),
    cargo_(new FactoryCargo)
{ }

void Factory::manage(const QString &cmd) {

}
