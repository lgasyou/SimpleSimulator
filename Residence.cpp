#include "residence.h"

Residence::Residence(const QString &type) :
	BaseBuilding("World", type, nullptr)
{ }

void Residence::update() {
	changeBaseValue();
}
