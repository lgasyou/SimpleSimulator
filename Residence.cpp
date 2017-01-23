#include "Residence.h"

Residence::Residence(double value) :
	BuildingBase("World", value, "Residence", nullptr)
{ }

Residence::Residence(const BuildingBase &rhs) :
	BuildingBase(rhs.name(), rhs.value(), "Residence", rhs.owner(), rhs.deltaValue())
{ }

void Residence::manage(const QString &cmd) {

}

void Residence::update() { }
