#include "Commerce.h"


Commerce::Commerce(double value) :
	BuildingBase("Commerce", value, "Commerce", nullptr)
{ }

Commerce::Commerce(const BuildingBase &rhs, const QString &type) :
	BuildingBase(rhs.name(), rhs.value(), type, rhs.owner(), rhs.deltaValue())
{ }

Commerce::~Commerce() { }

void Commerce::manage(const QString &cmd) {

}

void Commerce::update() {
	changeBaseValue();
}
