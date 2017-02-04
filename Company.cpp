#include "Company.h"
#include "buildingbase.h"
#include "BuildingManager.h"

Company::Company() :
    name_("Xenon Inc."),
    cash_(1000),
    totalValue_(1000),
    liability_(0)
{ }

bool Company::buy(BuildingBase *building) {
    double buildingValue = building->value();
    if (buildingValue > this->cash_)
        return false;

    cash_ -= buildingValue;
    building->setOwner(this);
    return true;
}

bool Company::sell(BuildingBase *building) {
    cash_ += building->value();
    building->setOwner(nullptr);
    return true;
}

void Company::update() {
    
}
