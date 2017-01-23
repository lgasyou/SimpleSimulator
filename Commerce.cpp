#include "Commerce.h"

Commerce::Commerce(const QString &type) :
	BuildingBase("Commerce", type, nullptr)
{ }

Commerce::Commerce(const BuildingBase &rhs, const QString &type) :
	BuildingBase(rhs, type)
{ }

Commerce::~Commerce() { }

void Commerce::manage(const QString &cmd) {

}

void Commerce::update() {
	changeBaseValue();
}
