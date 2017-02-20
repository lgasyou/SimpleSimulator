#include "company.h"
#include "basebuilding.h"
#include "buildingmanager.h"
#include "government.h"

Company::Company(const QString &name) :
    name_(name),
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

bool Company::purchase(double cost) {
	if (cost > cash_)
		return false;

	cash_ -= cost;
	return true;
}

bool Company::sell(BaseBuilding *building) {
    cash_ += building->value();

	Government *gov = &Government::instance();
    building->setOwner(gov);
    return true;
}

void Company::update() {
    
}
