#include "baseresidence.h"

BaseResidence::BaseResidence(const QString &type) :
	BaseBuilding("World", type)
{ }

void BaseResidence::update() {
	changeBaseValue();
}
