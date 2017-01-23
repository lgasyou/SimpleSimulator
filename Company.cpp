#include "Company.h"
#include "BuildingBase.h"
#include "BuildingManager.h"

Company::Company() :
    name_("Xenon Inc."),
    cash_(1000),
    totalValue_(1000),
    liability_(0),
    properties_(new BuildingManager(0))
{ }

bool Company::buy(BuildingBase *building) {
    double buildingValue = building->value();
    if (buildingValue > this->cash_)
        return false;

    this->setCash(cash_ - buildingValue);
    properties_->addItem(building);
    building->setOwner(this);
    return true;
}

bool Company::sell(BuildingBase *building) {
    this->setCash(cash_ + building->value());
    properties_->removeItem(building);
    building->setOwner(nullptr);
    return true;
}

void Company::update() {
    totalValue_ += properties_->totalDeltaValue();
}
