#include "company.h"
#include "basebuilding.h"
#include "buildingmanager.h"
#include "government.h"

Company::Company(const QString &name) :
    name_(name)
{ }

Company::~Company() { }

bool Company::phrchase(BaseBuilding *building) {
    double buildingValue = building->value();
    if (buildingValue > this->cash_)
        return false;

	Company *seller = building->owner();
	seller->setCash(buildingValue + seller->cash());
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
	Government *buyer = &Government::instance();
	buyer->setCash(buyer->cash() - building->value());
    cash_ += building->value();
    building->setOwner(buyer);
    return true;
}

void Company::update() {
	double deltaValue = BuildingManager::instance().deltaValueOfCompanyProperties(this);
	setTotalValue(totalValue() + deltaValue);
}
