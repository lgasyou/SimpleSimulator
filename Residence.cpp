#include "Residence.h"

Residence::Residence(double value) :
    BaseBuilding("World", value, "Residence", nullptr)
{ }

Residence::Residence(const BaseBuilding &rhs) :
    BaseBuilding(rhs.name(), rhs.value(), "Residence", rhs.owner(), rhs.deltaValue())
{ }

void Residence::manage(const QString &cmd) {

}
