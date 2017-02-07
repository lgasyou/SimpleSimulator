#include "company.h"
#include "basebuilding.h"
#include "buildingmanager.h"

Company::Company() :
    name_("Xenon Inc."),
    cash_(1000),
    totalValue_(1000),
    liability_(0)
{ }

Company::~Company() { }

bool Company::buy(BaseBuilding *building) {
    double buildingValue = building->value();
    if (buildingValue > this->cash_)
        return false;

    cash_ -= buildingValue;
    building->setOwner(this);
    return true;
}

bool Company::sell(BaseBuilding *building) {
    cash_ += building->value();
    building->setOwner(nullptr);
    return true;
}

void Company::update() {
    
}
