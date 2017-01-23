#include "Residence.h"

Residence::Residence(const QString &type) :
	BuildingBase("World", type, nullptr)
{ }

Residence::Residence(const BuildingBase &rhs, const QString &type) :
	BuildingBase(rhs, type)
{ }

void Residence::manage(const QString &cmd) {

}

void Residence::update() {
	changeBaseValue();
}
